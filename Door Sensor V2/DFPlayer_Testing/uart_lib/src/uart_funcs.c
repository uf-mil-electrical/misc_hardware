
/******************<Dependencies>*****************/
#include "uart_lib/uart_funcs.h"
/******************</Dependencies>*****************/



/******************<Defines>*****************/
// Dictionary equivalent for sources
#define SOURCE_SDCARD 0x02
#define SOURCE_USB 0x01
#define SOURCE_AUX 0x04
#define SOURCE_SLEEP 0x05
#define SOURCE_FLASH 0x03
/******************</Defines>*****************/



/******************<Global Variables>*****************/
uart_inst_t *dfplayer_uart;
uint32_t dfplayer_sleep_time_ms;
bool dfplayer_debug;
bool dfplayer_paused;
char *dfplayer_source;
/******************</Global Variables>*****************/




/******************<UART Helpers>*****************/

/*******uart_send*******
 * Description
        > sends a byte string via UART
 * Arguments
        > uart_inst_t* uart - UART instance to use
		> uint8_t *data - pointer to data to send
		> size_t length - length of data to send
 * Returns
        > N/A
*/
void uart_send(uart_inst_t* uart, uint8_t *data, size_t length) {
	uart_write_blocking(uart, data, length);
}

/*******uart_receive*******
 * Description
        > receives a byte string via UART
 * Arguments
        > uart_inst_t* uart - UART instance to use
		> uint8_t *data - pointer to data to receive
		> size_t length - length of data to receive
 * Returns
        > N/A
*/
void uart_receive(uart_inst_t* uart, uint8_t *data, size_t length) {
	uart_read_blocking(uart, data, length);
}

/******************</UART Helpers>*****************/


/******************<Public Functions>*****************/
/*******dfplayer_init*******
 * Description
        > initializes DFPlayer global variables
 * Arguments
        > uart_inst_t* uart - UART instance to use
        > uint32_t sleep_time_ms - sleep time in ms
        > bool debug - enable debug output
 * Returns
        > N/A
*/
void dfplayer_init(uart_inst_t *uart, uint32_t sleep_time_ms, bool debug) {
    dfplayer_uart = uart;
    dfplayer_sleep_time_ms = sleep_time_ms;
    dfplayer_debug = debug;
    dfplayer_paused = false;
    dfplayer_source = NULL;
}


/*******send_bytes*******
 * Description
        > sends a byte string via UART and returns response
 * Arguments
        > uint8_t *byte_string - pointer to data to send
        > size_t length - length of data to send
        > uint8_t *response - buffer to store response
 * Returns
        > bool - true if response received, false otherwise
*/
bool send_bytes(uint8_t *byte_string, size_t length, uint8_t *response) {
    uart_send(dfplayer_uart, byte_string, length);
    sleep_ms(dfplayer_sleep_time_ms);
    return read_reply(response);
}

/*******read_reply*******
 * Description
        > reads reply from UART
 * Arguments
        > uint8_t *response - buffer to store response
 * Returns
        > bool - true if response received, false otherwise
*/
bool read_reply(uint8_t *response) {
    // Try to read 10 bytes (standard DFPlayer response size)
    uint8_t read_buffer[10];
    
    // Get available bytes
    int bytes_available = uart_is_readable_within_us(dfplayer_uart, 100000); // 100ms timeout
    
    if (bytes_available == 0) {
        if (dfplayer_debug) {
            printf("None received\n");
        }
        return false;
    }
    
    uart_receive(dfplayer_uart, read_buffer, 10);
    
    // Copy to response buffer
    memcpy(response, read_buffer, 10);
    
    if (dfplayer_debug) {
        printf("Received ");
        for (int i = 0; i < 10; i++) {
            printf("\\x%02x", response[i]);
        }
        printf("\n");
    }
    
    return true;
}

/*******calc_checksum*******
 * Description
        > calculates checksum for DFPlayer command
 * Arguments
        > uint8_t *data - pointer to data
        > size_t length - length of data
 * Returns
        > uint16_t - calculated checksum
*/
uint16_t calc_checksum(uint8_t *data, size_t length) {
    uint16_t sum = 0;
    for (size_t i = 0; i < length; i++) {
        sum += data[i];
    }
    // Convert to twos complement
    uint16_t twos = (0xFFFF + 1 - sum);
    return twos;
}

/*******send_command*******
 * Description
        > sends command to DFPlayer
 * Arguments
        > uint8_t command - command byte
        > uint16_t value - parameter value
        > uint8_t feedback - feedback flag
        > uint8_t *response - buffer to store response
 * Returns
        > bool - true if command sent and response received
*/
bool send_command(uint8_t command, uint16_t value, uint8_t feedback, uint8_t *response) {
    uint8_t data[6];
    data[0] = 0xFF;  // Version
    data[1] = 0x06;  // Len
    data[2] = command;
    data[3] = feedback;
    data[4] = (value >> 8) & 0xFF;  // High byte
    data[5] = value & 0xFF;        // Low byte
    
    // Calculate checksum
    uint16_t checksum = calc_checksum(data, 6);
    
    // Create complete data string
    uint8_t data_string[10];
    data_string[0] = 0x7E;  // Start
    memcpy(&data_string[1], data, 6);
    data_string[7] = (checksum >> 8) & 0xFF;  // High byte
    data_string[8] = checksum & 0xFF;         // Low byte
    data_string[9] = 0xEF;  // End
    
    if (dfplayer_debug) {
        printf("Sending: ");
        for (int i = 0; i < 10; i++) {
            printf("\\x%02x", data_string[i]);
        }
        printf("\n");
    }
    
    return send_bytes(data_string, 10, response);
}

/*******reset*******
 * Description
        > resets DFPlayer
 * Arguments
        > None
 * Returns
        > bool - true if reset successful
*/
bool reset(void) {
    uint8_t response[10];
    dfplayer_paused = false;
    
    if (!send_command(0x0C, 0, 1, response)) {
        return false;
    }
    
    // Reset wait 2 x sleep as sometimes needs to stabilize first
    sleep_ms(dfplayer_sleep_time_ms * 2);
    
    // Next value should be x3f with 0,0,<response>
    if (!read_reply(response)) {
        return false;
    }
    
    // Now check for a valid return value
    if (response[3] != 0x3f) {
        return false;
    }
    
    // 2 = CardInserted, 4 = CardOnline, 7 = USBInserted, 9 = USBOnline, 10 = CardUSBOnline
    return (response[6] == 0x02 || 
            response[6] == 0x04 || 
            response[6] == 0x07 || 
            response[6] == 0x09 || 
            response[6] == 0x10);
}

/*******query_num_files*******
 * Description
        > queries number of files on media
 * Arguments
        > char *source - source to query ("sdcard", "usb", "flash")
 * Returns
        > int - number of files or -1 if error
*/
int query_num_files(const char *source) {
    uint8_t response[10];
    uint8_t query_code = 0;
    
    // If no source set use current, otherwise return false
    const char *src_to_use = source;
    if (src_to_use == NULL) {
        if (dfplayer_source == NULL) {
            return -1;
        }
        src_to_use = dfplayer_source;
    }
    
    // Now source is set from parameter or using default
    // Different from datasheet which says x47 - TF card, x48 = U-disk
    if (strcmp(src_to_use, "sdcard") == 0 || strcmp(src_to_use, "sd") == 0) {
        query_code = 0x48;
    } else if (strcmp(src_to_use, "usb") == 0) {
        query_code = 0x47;
    } else if (strcmp(src_to_use, "flash") == 0) {
        query_code = 0x49;
    } else {
        return -1;
    }
    
    if (!send_command(query_code, 0, 1, response)) {
        return -1;
    }
    
    sleep_ms(dfplayer_sleep_time_ms);
    
    // Now check for a valid return value
    if (!read_reply(response)) {
        return -1;
    }
    
    if (response[3] != query_code) {
        return -1;
    }
    
    // Return value of lower byte + upper byte x (FF+1)
    int eval_value = (response[5] * 256) + response[6];
    if (dfplayer_debug) {
        printf("Eval %d\n", eval_value);
    }
    return eval_value;
}

/*******get_volume*******
 * Description
        > gets current volume
 * Arguments
        > None
 * Returns
        > int - current volume or -1 if error
*/
int get_volume(void) {
    uint8_t response[10];
    
    if (!send_command(0x43, 0, 1, response)) {
        return -1;
    }
    
    sleep_ms(dfplayer_sleep_time_ms);
    
    // Retrieve actual value
    if (!read_reply(response)) {
        return -1;
    }
    
    if (response[3] != 0x43) {
        return -1;
    }
    
    return response[6];
}

/*******set_volume*******
 * Description
        > sets volume
 * Arguments
        > uint8_t volume - volume level (0-30)
 * Returns
        > bool - true if successful
*/
bool set_volume(uint8_t volume) {
    uint8_t response[10];
    return send_command(0x06, volume, 1, response);
}

/*******volume_up*******
 * Description
        > increases volume
 * Arguments
        > None
 * Returns
        > bool - true if successful
*/
bool volume_up(void) {
    uint8_t response[10];
    return send_command(0x04, 0, 1, response);
}

/*******volume_down*******
 * Description
        > decreases volume
 * Arguments
        > None
 * Returns
        > bool - true if successful
*/
bool volume_down(void) {
    uint8_t response[10];
    return send_command(0x05, 0, 1, response);
}

/*******select_source*******
 * Description
        > selects audio source
 * Arguments
        > const char *source - source name ("sdcard", "usb", "aux", "sleep", "flash")
 * Returns
        > bool - true if successful
*/
bool select_source(const char *source) {
    uint8_t response[10];
    uint16_t source_value = 0;
    
    dfplayer_paused = false;
    
    if (strcmp(source, "sdcard") == 0) {
        source_value = SOURCE_SDCARD;
    } else if (strcmp(source, "usb") == 0) {
        source_value = SOURCE_USB;
    } else if (strcmp(source, "aux") == 0) {
        source_value = SOURCE_AUX;
    } else if (strcmp(source, "sleep") == 0) {
        source_value = SOURCE_SLEEP;
    } else if (strcmp(source, "flash") == 0) {
        source_value = SOURCE_FLASH;
    } else {
        return false;
    }
    
    if (!send_command(0x09, source_value, 1, response)) {
        return false;
    }
    
    dfplayer_source = (char*)source;
    return true;
}

/*******stop*******
 * Description
        > stops playback
 * Arguments
        > None
 * Returns
        > bool - true if successful
*/
bool stop(void) {
    uint8_t response[10];
    dfplayer_paused = false;
    return send_command(0x16, 0, 1, response);
}

/*******play*******
 * Description
        > plays specific track
 * Arguments
        > uint16_t track_num - track number
 * Returns
        > bool - true if successful
*/
bool play(uint16_t track_num) {
    uint8_t response[10];
    dfplayer_paused = false;
    return send_command(0x03, track_num, 1, response);
}

/*******play_next*******
 * Description
        > plays next track
 * Arguments
        > None
 * Returns
        > bool - true if successful
*/
bool play_next(void) {
    uint8_t response[10];
    dfplayer_paused = false;
    return send_command(0x01, 0, 1, response);
}

/*******play_previous*******
 * Description
        > plays previous track
 * Arguments
        > None
 * Returns
        > bool - true if successful
*/
bool play_previous(void) {
    uint8_t response[10];
    dfplayer_paused = false;
    return send_command(0x02, 0, 1, response);
}

/*******play_loop*******
 * Description
        > plays track in loop mode
 * Arguments
        > uint16_t track_num - track number
 * Returns
        > bool - true if successful
*/
bool play_loop(uint16_t track_num) {
    uint8_t response[10];
    dfplayer_paused = false;
    return send_command(0x08, track_num, 1, response);
}

/*******pause*******
 * Description
        > pauses playback
 * Arguments
        > None
 * Returns
        > bool - true if successful
*/
bool pause(void) {
    uint8_t response[10];
    dfplayer_paused = true;
    return send_command(0x0E, 0, 1, response);
}

/*******start*******
 * Description
        > starts or resumes playback
 * Arguments
        > None
 * Returns
        > bool - true if successful
*/
bool start(void) {
    uint8_t response[10];
    dfplayer_paused = false;
    return send_command(0x0D, 0, 1, response);
}

/*******get_status*******
 * Description
        > gets current player status
 * Arguments
        > None
 * Returns
        > int - status code (-1=error, 0=stopped, 1=playing, 2=paused)
*/
int get_status(void) {
    uint8_t response[10];
    
    if (!send_command(0x42, 0, 1, response)) {
        // First retry:
        if (!read_reply(response)) {
            return -1;
        }
    }
    
    sleep_ms(dfplayer_sleep_time_ms);
    
    // Retrieve actual value
    if (!read_reply(response)) {
        return -1;
    }
    
    // If get a generic reply - then likely missed previously, so check again for the value reply
    if (response[3] == 0x41) {
        sleep_ms(dfplayer_sleep_time_ms);
        if (!read_reply(response)) {
            return -1;
        }
    }
    
    if (response[3] != 0x42) {
        return -1;
    }
    
    return response[6];
}
/******************</Public Functions>*****************/