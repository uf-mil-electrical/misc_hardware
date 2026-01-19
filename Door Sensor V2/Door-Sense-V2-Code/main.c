/*
  __  __ _____ _                                             
 |  \/  |_   _| |                                            
 | \  / | | | | |                                            
 | |\/| | | | | |                                            
 | |  | |_| |_| |____                                        
 |_|__|_|_____|______|                                  
  _____                      _____
 |  __ \                    / ____|                          
 | |  | | ___   ___  _ __  | (___   ___ _ __  ___  ___  _ __ 
 | |  | |/ _ \ / _ \| '__|  \___ \ / _ \ '_ \/ __|/ _ \| '__|
 | |__| | (_) | (_) | |     ____) |  __/ | | \__ \ (_) | |   
 |_____/ \___/ \___/|_|    |_____/ \___|_| |_|___/\___/|_|   
 __		 __ __
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
// Core libraries
#include <stdio.h>
#include "pico/stdlib.h"

// BLE Stack
#include "btstack.h"
#include "pico/cyw43_arch.h"
#include "pico/btstack_cyw43.h"
#include "door_sense.h"

// Peripheral includes
#include "pico/time.h"

#include "hardware/irq.h"
#include "hardware/spi.h"
#include "hardware/uart.h"
#include "hardware/i2c.h"


// Program files to include
#include "setup.h"
#include "peripherals/doorsense_gpio.h"
#include "peripherals/doorsense_i2c.h"
#include "peripherals/doorsense_spi.h"
#include "peripherals/doorsense_uart.h"

#include "tof_lib/tof_core.h"

#include "operation/door_state.h"

//*****************</Includes>*****************//


#define TOF_CHECK_INTERVAL_MS		100		// how often to check ToF sensor for data ready (in ms)
#define BLE_POLL_INTERVAL_MS		100		// how often to poll the BLE stack (in ms)
#define COUNTDOWN_CHECK_INTERVAL_MS 500		// how often to check countdown timer (in ms)

volatile uint32_t times_isr_fired;	// keeps track of how many times the timer ISR has been called (once every 500ms)
volatile uint32_t countdown_time;	// time (in 500ms increments) until lab state change occurs


uint16_t lab_open_ble = 0;				// 0=closed, 1=open
bool lab_state = false;				// true=lab is open, false=lab is closed
bool change_state = false;			// true=lab state will change after countdown, false=no change

bool data_ready = false;			// stores if data is ready to be read from ToF sensor

bool door_state = false;			// current door state
bool candidate_state = false;		// candidate door state (state being considered during countdown)

volatile bool run_countdown = false;			// true=currently running countdown to change door state

//*****************</Temp>*****************//





#define HEARTBEAT_PERIOD_MS 500
#define APP_AD_FLAGS 0x06

static uint8_t adv_data[] = {
    // Flags general discoverable
    0x02, BLUETOOTH_DATA_TYPE_FLAGS, APP_AD_FLAGS,
    // Name
    0x14, BLUETOOTH_DATA_TYPE_COMPLETE_LOCAL_NAME, 'M', 'I', 'L', ' ', 'D', 'o', 'o', 'r', ' ', 'S', 'e', 'n', 's', 'o', 'r', ' ', 'V', '2',
    0x03, BLUETOOTH_DATA_TYPE_COMPLETE_LIST_OF_16_BIT_SERVICE_CLASS_UUIDS, 0x1a, 0x18,
};
static const uint8_t adv_data_len = sizeof(adv_data);

int le_notification_enabled;
hci_con_handle_t con_handle;
static btstack_timer_source_t heartbeat;
static btstack_packet_callback_registration_t hci_event_callback_registration;

extern uint8_t const profile_data[];

static void packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size) {
    UNUSED(size);
    UNUSED(channel);
    bd_addr_t local_addr;
    if (packet_type != HCI_EVENT_PACKET) return;

    uint8_t event_type = hci_event_packet_get_type(packet);
    switch(event_type){
        case BTSTACK_EVENT_STATE:
            if (btstack_event_state_get_state(packet) != HCI_STATE_WORKING) return;
            gap_local_bd_addr(local_addr);
            printf("BTstack up and running on %s.\n", bd_addr_to_str(local_addr));

            // setup advertisements
            uint16_t adv_int_min = 800;
            uint16_t adv_int_max = 800;
            uint8_t adv_type = 0;
            bd_addr_t null_addr;
            memset(null_addr, 0, 6);
            gap_advertisements_set_params(adv_int_min, adv_int_max, adv_type, 0, null_addr, 0x07, 0x00);
            assert(adv_data_len <= 31); // ble limitation
            gap_advertisements_set_data(adv_data_len, (uint8_t*) adv_data);
            gap_advertisements_enable(1);

            break;
        case HCI_EVENT_DISCONNECTION_COMPLETE:
            le_notification_enabled = 0;
            break;
        case ATT_EVENT_CAN_SEND_NOW:
            att_server_notify(con_handle, ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_TEMPERATURE_01_VALUE_HANDLE, (uint8_t*)&lab_open_ble, sizeof(lab_open_ble));
            break;
        default:
            break;
    }
}

static uint16_t att_read_callback(hci_con_handle_t connection_handle, uint16_t att_handle, uint16_t offset, uint8_t * buffer, uint16_t buffer_size) {
    UNUSED(connection_handle);

    if (att_handle == ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_TEMPERATURE_01_VALUE_HANDLE){
        return att_read_callback_handle_blob((const uint8_t *)&lab_open_ble, sizeof(lab_open_ble), offset, buffer, buffer_size);
    }
    return 0;
}

static int att_write_callback(hci_con_handle_t connection_handle, uint16_t att_handle, uint16_t transaction_mode, uint16_t offset, uint8_t *buffer, uint16_t buffer_size) {
    UNUSED(transaction_mode);
    UNUSED(offset);
    UNUSED(buffer_size);

    if (att_handle != ATT_CHARACTERISTIC_ORG_BLUETOOTH_CHARACTERISTIC_TEMPERATURE_01_CLIENT_CONFIGURATION_HANDLE) return 0;
    le_notification_enabled = little_endian_read_16(buffer, 0) == GATT_CLIENT_CHARACTERISTICS_CONFIGURATION_NOTIFICATION;
    con_handle = connection_handle;
    if (le_notification_enabled) {
        att_server_request_can_send_now_event(con_handle);
    }
    return 0;
}


static void heartbeat_handler(struct btstack_timer_source *ts) {
    
	times_isr_fired += 1;

	// Update broadcast value once per second
    if (times_isr_fired >= 2) {
		times_isr_fired = 0;
        if (le_notification_enabled) {
            att_server_request_can_send_now_event(con_handle);
        }
    }

    // Invert the led
    static int led_on = true;
    led_on = !led_on;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);


    // Restart timer
    btstack_run_loop_set_timer(ts, HEARTBEAT_PERIOD_MS);
    btstack_run_loop_add_timer(ts);
}


int main() {
    stdio_init_all();

	sleep_ms(2000);


	// Initialize basic peripherals
		init_doorsense_leds();
		init_i2c(TOF_I2C_PORT, TOF_I2C_BAUDRATE, TOF_SDA, TOF_SCL);
		printf("Initialized peripherals\n");


	// Initialize ToF sensor
		sleep_ms(200);
		tof_init();
		printf("Initialized ToF\n");

	// Initialize BLE / WiFi architecture
		if (cyw43_arch_init()) {
			printf("failed to initialise cyw43_arch\n");
			return -1;
		}


	// Initialize BLE stack

		l2cap_init();
		sm_init();
		att_server_init(profile_data, att_read_callback, att_write_callback);

		// inform about BTstack state
		hci_event_callback_registration.callback = &packet_handler;
		hci_add_event_handler(&hci_event_callback_registration);

		// register for ATT event
		att_server_register_packet_handler(packet_handler);

		// set one-shot btstack timer
		heartbeat.process = &heartbeat_handler;
		btstack_run_loop_set_timer(&heartbeat, HEARTBEAT_PERIOD_MS);
		btstack_run_loop_add_timer(&heartbeat);

		// turn on bluetooth!
		hci_power_control(HCI_POWER_ON);

	// Preparation for main program loop

		// main loop timing control
		uint32_t last_tof_check_time = 0;
		uint32_t last_ble_poll_time = 0;
		uint32_t last_countdown_check_time = 0;


    while(true) {

		// Get current time
			uint32_t current_time = to_ms_since_boot(get_absolute_time());

		// Poll BLE stack at regular intervals
			if (current_time - last_ble_poll_time >= BLE_POLL_INTERVAL_MS){
				// i: reset last poll time
					last_ble_poll_time = current_time;

				// ii: run BLE task
					cyw43_arch_poll();
			}

		// Check ToF sensor at regular intervals
			if (current_time - last_tof_check_time >= TOF_CHECK_INTERVAL_MS){
				// i: reset last check time
					last_tof_check_time = current_time;

				// ii: check if ToF data is ready
					if (tof_check_data_ready() == 0){data_ready = false;}
					else {data_ready = true;}

				// iii: if data ready...
					if (data_ready == true){
						door_state = is_door_open();  //read distance, determine door state
						data_ready = false;			  // reset data ready status

						// Check if door state is different from lab state AND countdown not started
							if ((door_state != lab_state) && (run_countdown == false)){
								printf("Door state change detected!\n");
								candidate_state = door_state;		// set candidate state
								countdown_time = 0;					// reset variable
								run_countdown = true;				// start countdown
							}

						// Cancel countdown if door state changes during countdown
							if ( (run_countdown == true) && (candidate_state != door_state) ){
								printf("Cancelled state change\n");
								run_countdown = false;
								countdown_time = 0;	

								if (lab_state == true){set_led('g', true);}
								else {set_led('g', false);}
							}
					}
			}

		// Run countdown with non-blocking timing (as needed)
			if (run_countdown == true && (current_time - last_countdown_check_time >= COUNTDOWN_CHECK_INTERVAL_MS)) {
				// i: reset last check time
					last_countdown_check_time = current_time;

				// ii: increment countdown timer
					countdown_time += 1;

				// iii: blink LED (change state once every 500ms)
					if (countdown_time % 2 == 0){set_led('g', true);}
					else {set_led('g', false);}

				// iv: check to see if timer has counted to 10 seconds
					if (countdown_time >= 20){			// 500ms * 20 = 10 seconds
						run_countdown = false;
						change_state = true;			// change lab state
						countdown_time = 0;
						printf("New lab state\n");
					}
			}

		// Update lab state variable as needed
			if (change_state == true){
				change_state = false;
				lab_state = candidate_state;

				if (lab_state == true){
					printf("Lab is now OPEN\n");
					set_led('g', true);
					lab_open_ble = 1;
				}
				else if (lab_state == false){
					printf("Lab is now CLOSED\n");
					set_led('g', false);
					lab_open_ble = 0;
				}
			}
    }
	
	return 0;   
}