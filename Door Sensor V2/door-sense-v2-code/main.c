/*
  __  __ _____ _                                             
 |  \/  |_   _| |                                            
 | \  / | | | | |                                            
 | |\/| | | | | |                                            
 | |  | |_| |_| |____                                        
 |_|  |_|_____|______|                           
  _____                      _____
 |  __ \                    / ____|                          
 | |  | | ___   ___  _ __  | (___   ___ _ __  ___  ___  _ __ 
 | |  | |/ _ \ / _ \| '__|  \___ \ / _ \ '_ \/ __|/ _ \| '__|
 | |__| | (_) | (_) | |     ____) |  __/ | | \__ \ (_) | |   
 |_____/ \___/ \___/|_|    |_____/ \___|_| |_|___/\___/|_|   
 __      __ __
 \ \    / /__ \                                              
  \ \  / /   ) |                                             
   \ \/ /   / /                                              
    \  /   / /_                                              
     \/   |____|                                             
                                                             
    Door Sensor Board V2
    Pico 2 W
    Written by Russell MacGregor 
*/


//*****************<Includes>*****************//
// Core system dependencies
#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"

// BLE Dependencies
#include "btstack.h"
#include "pico/cyw43_arch.h"
#include "pico/btstack_cyw43.h"

// Misc system dependencies
#include <string.h>
#include <assert.h>

// My code to include


//*****************</Includes>*****************//


#define DOOR_GPIO 2   // change to your pin
#define DOOR_OPEN_LEVEL 1  // 1 if GPIO reads high when open; else 0

#define APP_AD_FLAGS 0x06
#define HEARTBEAT_PERIOD_MS 250

static uint8_t adv_data[] = {

    // Flags general discoverable
    0x02, BLUETOOTH_DATA_TYPE_FLAGS, APP_AD_FLAGS,

    // Complete local name
    0x0F, BLUETOOTH_DATA_TYPE_COMPLETE_LOCAL_NAME, 'D', 'o', 'o', 'r', ' ', 'S', 'e', 'n', 's', 'o', 'r', ' ', 'V', '2',

	// Manufacturer Specific Data: company=0xFFFF, door_state=0/1
    0x04, BLUETOOTH_DATA_TYPE_MANUFACTURER_SPECIFIC_DATA, 0xFF, 0xFF, 0x00,	// last byte is door_state (placeholder)
};

static const uint8_t adv_data_len = sizeof(adv_data);


// Index of door_state byte inside adv_data[]
#define ADV_DATA_DOOR_STATE_INDEX  (sizeof(adv_data) - 1)

static btstack_timer_source_t heartbeat;
static btstack_packet_callback_registration_t hci_event_callback_registration;

static volatile uint8_t door_state = 0; // 0=closed, 1=open


static void start_advertising(void) {
    // interval units are 0.625ms
    // 800 => 500ms
    uint16_t adv_int_min = 800;
    uint16_t adv_int_max = 800;

    uint8_t adv_type = 0; // connectable undirected in BTstack examples
    bd_addr_t null_addr;
    memset(null_addr, 0, 6);

    gap_advertisements_set_params(adv_int_min, adv_int_max, adv_type, 0, null_addr, 0x07, 0x00);

    // Safety: legacy ADV payload limit is 31 bytes
    assert(adv_data_len <= 31);

    gap_advertisements_set_data(adv_data_len, adv_data);
    gap_advertisements_enable(1);
}


static void packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size) {
    UNUSED(channel);
    UNUSED(size);

    if (packet_type != HCI_EVENT_PACKET) return;

    switch (hci_event_packet_get_type(packet)) {
        case BTSTACK_EVENT_STATE:
            if (btstack_event_state_get_state(packet) != HCI_STATE_WORKING) return;
            printf("BTstack is up, starting advertising\n");
            start_advertising();
            break;

        default:
            break;
    }
}



uint8_t read_door_state(void) {
    int level = 5;		// placeholder
    //return (level == DOOR_OPEN_LEVEL) ? 1 : 0;

	return level;
}

static void update_advertisement_door_state(uint8_t new_state) {
    adv_data[ADV_DATA_DOOR_STATE_INDEX] = new_state;
    gap_advertisements_set_data(adv_data_len, adv_data);
}

static void heartbeat_handler(struct btstack_timer_source *ts) {
    static uint8_t last = 0xFF;

    uint8_t now = read_door_state();
    if (now != last) {
        last = now;
        door_state = now;
        printf("Door state = %u\n", now);
        update_advertisement_door_state(now);
    }

    btstack_run_loop_set_timer(ts, HEARTBEAT_PERIOD_MS);
    btstack_run_loop_add_timer(ts);
}


int main() {
    stdio_init_all();
    sleep_ms(2000);
    printf("Door advertiser starting...\n");

    // Door GPIO init
    //gpio_init(DOOR_GPIO);
    ///gpio_set_dir(DOOR_GPIO, GPIO_IN);
    // enable pull if needed:
    // gpio_pull_up(DOOR_GPIO);  // or gpio_pull_down

    // initial door state in adv data before starting
    door_state = read_door_state();
    adv_data[ADV_DATA_DOOR_STATE_INDEX] = door_state;

    if (cyw43_arch_init()) {
        printf("failed to initialise cyw43_arch\n");
        return -1;
    }

    l2cap_init();
    // sm_init(); // optional for advertising-only; safe to omit

    // register for HCI events
    hci_event_callback_registration.callback = &packet_handler;
    hci_add_event_handler(&hci_event_callback_registration);

    // heartbeat timer (poll door + update advertising)
    heartbeat.process = &heartbeat_handler;
    btstack_run_loop_set_timer(&heartbeat, HEARTBEAT_PERIOD_MS);
    btstack_run_loop_add_timer(&heartbeat);

    // power on BT
    hci_power_control(HCI_POWER_ON);

    while (true) {
        async_context_poll(cyw43_arch_async_context());
        async_context_wait_for_work_until(cyw43_arch_async_context(), at_the_end_of_time);
    }
}