#include <stdio.h>
#include <string.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/i2c.h"
#include "hardware/uart.h"

#ifndef pgm_read_byte
#define pgm_read_byte(addr) (*(const uint8_t *)(addr))
#endif 

#include "Adafruit_NeoPixel.h"

#define NEOPIXEL_GPIO 26
#define NEOPIXEL_COUNT 16
#define NEOPIXEL_MAX_BRIGHTNESS 255
#define NEOPIXEL_MIN_BRIGHTNESS 0

#define I2C_PORT i2c0
#define TLV493D_ADDR 0x5E
#define LSB_TO_MT 0.098f // 1 LSB = 0.098 mT for TLV493D-A1B6

#define MAG_AXIS_NUM 3
#define MAG_THRESHOLD 1.5f //mT
#define MAG_HOLD_REPAIR_TIME_MS 2000
#define MAG_HOLD_CODE_TIME_MS 1000
#define MAG_HOLD_SHUTDOWN_TIME_MS 1000

#define UART_ID uart1
#define BAUD_RATE 9600
#define UART_TX_PIN 4
#define UART_RX_PIN 5
#define RS485_DIR_PIN 6   // <-- single GPIO driving DE and RE_N together
#define COLOR_RGB(r, g, b) ((r << 16) | (g << 8) | b)

typedef enum tier {
    CORE = 0,
    ADVANCED = 1, 
    DISRUPTIVE = 2
} tier_t; 

typedef enum magneto_pos {
    X_P = 0, 
    X_N = 1,
    Y_P = 2,
    Y_N = 3,
    Z_P = 4,
    Z_N = 5
} magneto_pos_t;

// so you can see the ring on start once you've configured a color
int16_t ring_brightness = 50; 

magneto_pos_t mag_max_prev = X_P;
//magneto_pos_t current_mag_max = X_P;
bool mag_pos_changed = false; 

magneto_pos_t current_alarm_mag_hold = X_P;
alarm_id_t alarm_id_mag_hold = -1; 
bool alarm_mag_hold_flag = false; 

static void rs485_set_direction(bool transmit) {
    // High = DE asserted (drive bus) and RE_N deasserted (receiver off)
    // Low  = DE deasserted, RE_N asserted (receiver on) — normal idle state
    gpio_put(RS485_DIR_PIN, transmit ? 1 : 0);
}

int64_t mag_hold_alarm_callback(alarm_id_t id, void* user_data)
{
    alarm_mag_hold_flag = true; 
    return 0;
}

void rs485_output_test(void) {
    const char *test_msg = "RS485_PROBE_TEST\n";
    size_t len = strlen(test_msg);

    rs485_set_direction(true);
    sleep_us(10); // let the driver actually enable before clocking data out
    uart_write_blocking(UART_ID, (const uint8_t *)test_msg, len);
    uart_tx_wait_blocking(UART_ID); // block until shift register empties, not just the FIFO
    rs485_set_direction(false);

    printf("Sent %zu bytes - probe A/B now.\n", len);
}

int16_t clamp_brightness(int16_t bright)
{
    if(bright < NEOPIXEL_MIN_BRIGHTNESS)
    {
        return uint16_t(NEOPIXEL_MIN_BRIGHTNESS); 
    }
    if(bright > NEOPIXEL_MAX_BRIGHTNESS)
    {
        return uint16_t(NEOPIXEL_MAX_BRIGHTNESS);
    }
    return bright;
}

Adafruit_NeoPixel ring(NEOPIXEL_COUNT, NEOPIXEL_GPIO, NEO_GRB + NEO_KHZ800);

magneto_pos_t magneto_max_axis(float* mag_axes)
{
    float max = mag_axes[1];
    int index = 0;
    for(int i = 0; i < MAG_AXIS_NUM; i++)
    {
        if(std::fabs(mag_axes[i]) > std::fabs(max))
        {
            max = mag_axes[i];
            index = i; 
        }
    }
    if(max < 0)
    {
        return (magneto_pos_t(2 * index + 1));
    }
    return(magneto_pos_t(2 * index)); 
}

void magneto_act_on_max_axis(magneto_pos_t signed_axis)
{
    if(signed_axis != mag_max_prev)
    {
        mag_max_prev = signed_axis; 
        return; 
    }
    switch(signed_axis)
    {
        // increment brightness
        case X_P:
            // prevent immediate increments and decrements with a sleep
            sleep_ms(200);
            ring_brightness++;
            ring_brightness = clamp_brightness(ring_brightness);
            ring.setBrightness(uint8_t(ring_brightness));
            ring.show(); 
            break;
        // decrement brightness
        case X_N:
            sleep_ms(200);
            ring_brightness--;
            ring_brightness = clamp_brightness(ring_brightness); 
            ring.setBrightness(uint8_t(ring_brightness));
            ring.show();
            break;
        // coding light node green 
        case Y_P:
            // cancel existing timers if any 
            if(current_alarm_mag_hold != Y_P)
            {
                cancel_alarm(alarm_id_mag_hold); 
            }
            // start new timer and save ID 
            alarm_id_mag_hold = add_alarm_in_ms(MAG_HOLD_CODE_TIME_MS, mag_hold_alarm_callback, NULL, false);
            current_alarm_mag_hold = Y_P;
            // if timer flag has fired, turn led green 
            if(alarm_mag_hold_flag)
            {
                alarm_mag_hold_flag = false; 
                ring.fill((uint32_t)COLOR_RGB(0, 255, 0), 0, NEOPIXEL_COUNT);
                ring.show();
            }
            break;
        // coding light node red
        case Y_N:
            // cancel existing timers if any 
            if(current_alarm_mag_hold != Y_N)
            {
                cancel_alarm(alarm_id_mag_hold); 
            }
            // start new timer and save ID 
            alarm_id_mag_hold = add_alarm_in_ms(MAG_HOLD_CODE_TIME_MS, mag_hold_alarm_callback, NULL, false);
            current_alarm_mag_hold = Y_N;
            // if timer flag has fired, turn led red
            if(alarm_mag_hold_flag)
            {
                alarm_mag_hold_flag = false; 
                ring.fill((uint32_t)COLOR_RGB(255, 0, 0), 0, NEOPIXEL_COUNT);
                ring.show();
            }
            break; 
        // repair light node 
        case Z_P:
            // cancel existing timers if any 
            if(current_alarm_mag_hold != Z_P)
            {
                cancel_alarm(alarm_id_mag_hold); 
            }
            // start new timer and save ID 
            alarm_id_mag_hold = add_alarm_in_ms(MAG_HOLD_REPAIR_TIME_MS, mag_hold_alarm_callback, NULL, false);
            current_alarm_mag_hold = Z_P;
            // if timer flag has fired, turn led green
            if(alarm_mag_hold_flag)
            {
                alarm_mag_hold_flag = false; 
                ring.fill((uint32_t)COLOR_RGB(255, 0, 0), 0, NEOPIXEL_COUNT);
                ring.show();
            }

            break;
        // disable light node
        case Z_N:
            // cancel existing timers if any 
            if(current_alarm_mag_hold != Z_N)
            {
                cancel_alarm(alarm_id_mag_hold); 
            }
            // start new timer and save ID 
            alarm_id_mag_hold = add_alarm_in_ms(MAG_HOLD_SHUTDOWN_TIME_MS, mag_hold_alarm_callback, NULL, false);
            current_alarm_mag_hold = Z_N;
            // if timer flag has fired, turn led green
            if(alarm_mag_hold_flag)
            {
                alarm_mag_hold_flag = false; 
                ring.clear();
                ring.show();
            }
            break;
    }
}

// Reset via I2C general-call address. Required so the sensor's internal
// byte pointer is known to be at 0 before any read/write stream.
static void tlv493d_reset(void) {
    uint8_t reset_byte = 0x00; // 0x00 = sensor should use address 0x5E (default)
    i2c_write_blocking(I2C_PORT, 0x00, &reset_byte, 1, false);
    sleep_us(200); // give it time to complete the reset
}

// Initialize the sensor into Master Controlled Mode.
// NOTE: TLV493D has no addressable registers - reads/writes are a plain
// byte stream starting at a fixed offset. There is no "register address"
// byte on this bus, ever.
bool tlv493d_init(void) {
    //tlv493d_reset();

    // Read the 10 factory/config registers (0-9). Registers 7,8,9 hold
    // factory calibration bits that MUST be echoed back on every write,
    // or the sensor's behavior becomes undefined.
    uint8_t rx_buf[10];
    int ret = i2c_read_blocking(I2C_PORT, TLV493D_ADDR, rx_buf, 10, false);
    if (ret == PICO_ERROR_GENERIC) {
        return false;
    }

    // Build the 4-byte write frame (no register address prefix - just data).
    uint8_t write_regs[4];
    write_regs[0] = 0x00;                       // always reserved, write 0
    write_regs[1] = (rx_buf[7] & 0x18) | 0x03;   // reserved bits from reg7 | MOD[1:0]=11 (Master Controlled)
    write_regs[2] = rx_buf[8];                   // reserved, copy reg8 verbatim
    write_regs[3] = (rx_buf[9] & 0x1F);           // reserved bits from reg9, LP_PERIOD bit=0 (unused in MCM)

    ret = i2c_write_blocking(I2C_PORT, TLV493D_ADDR, write_regs, 4, false);
    if (ret == PICO_ERROR_GENERIC) {
        return false;
    }
    return true;
}

// Read raw data and parse into milliTesla (mT)
bool tlv493d_read_data(float *x, float *y, float *z) {
    uint8_t reg_data[7]; // First 7 registers contain X, Y, Z, and Temp data
    int ret = i2c_read_blocking(I2C_PORT, TLV493D_ADDR, reg_data, 7, false);
    if (ret == PICO_ERROR_GENERIC) {
        return false;
    }

    // combine bits 12...4 and 3...0 as they are read from separate registers
    int16_t raw_x = (reg_data[0] << 4) | ((reg_data[4] >> 4) & 0x0F);
    int16_t raw_y = (reg_data[1] << 4) | (reg_data[4] & 0x0F);
    int16_t raw_z = (reg_data[2] << 4) | (reg_data[5] & 0x0F);

    // sign extension to 16-bits 
    if (raw_x & 0x0800) raw_x |= 0xF000;
    if (raw_y & 0x0800) raw_y |= 0xF000;
    if (raw_z & 0x0800) raw_z |= 0xF000;

    *x = (float)raw_x * LSB_TO_MT;
    *y = (float)raw_y * LSB_TO_MT;
    *z = (float)raw_z * LSB_TO_MT;

    return true;
}

int main() {
    stdio_init_all();

    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(16, GPIO_FUNC_I2C);
    gpio_set_function(17, GPIO_FUNC_I2C);

    sleep_ms(1000);
    printf("Initializing TLV493D-A1B6...\n");

    if (!tlv493d_init()) {
        printf("Failed to find or initialize the TLV493D sensor.\n");
        while (1) tight_loop_contents();
    }
    printf("Sensor initialized successfully.\n");

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    uart_set_hw_flow(UART_ID, false, false);
    uart_set_format(UART_ID, 8, 1, UART_PARITY_NONE);
    uart_set_fifo_enabled(UART_ID, true);

    gpio_init(RS485_DIR_PIN);
    gpio_set_dir(RS485_DIR_PIN, GPIO_OUT);
    rs485_set_direction(false);

    float x, y, z;
    
    while (1) {
        if (tlv493d_read_data(&x, &y, &z)) {
            
            printf("X: %.2f mT | Y: %.2f mT | Z: %.2f mT\n", x, y, z);
            float mag_data[MAG_AXIS_NUM] = {x, y, z};
            float magnitude = sqrt(x * x + y * y + z * z); 
            
            if(magnitude > MAG_THRESHOLD)
            {
                // determine main contributing axis 
                magneto_pos_t mag_max = magneto_max_axis(mag_data);
                magneto_act_on_max_axis(mag_max);
            }
        } else {
            printf("Error reading sensor data.\n");
        }
        sleep_ms(200);
        //rs485_output_test();
    }
}