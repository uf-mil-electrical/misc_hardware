#ifndef MIL_ELECTRICAL_MESSAGE_SYSTEM_H_
#define MIL_ELECTRICAL_MESSAGE_SYSTEM_H_

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include <string.h>
/* #include <stdbool.h> */

#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"
#include "hardware/irq.h"

#include "MIL_USB2CAN.h"

/* -------------------------------------------------------------------------- */
/*                                   MACROS                                   */
/* -------------------------------------------------------------------------- */
/* ------------------------------- USB VALUES ------------------------------- */
#define SYNC_VALUE 0x3701
#define SYNC_HI (uint8_t) (SYNC_VALUE >> 8)
#define SYNC_LO (uint8_t) (SYNC_VALUE & 0xFF)

#define MAX_PAYLOAD_SIZE 256  // Adjust this value as needed
#define MIN_MSG_SIZE 4


/* -------------------------------------------------------------------------- */
/*                                   STRUCTS                                  */
/* -------------------------------------------------------------------------- */

/**
 * @struct  usb_message_t
 * @brief Represents a USB message structure used for communication over UART.
 * 
 * @param sync (uint16_t) sync byte of the message, should be 0x3701
 * @param class_id (uint8_t) class id of the message based on the device
 * @param subclass_id (uint8_t) subclass id of the message based on the device's action
 * @param payloadlength (uinion) union variable that can either be a word (uint16_t) or byte struct (uint8_t struct)
 * @param payloadlength.value (uint16_t) the payload length as a word
 * @param payloadlength.byte.low (uint8_t) low byte of the payload length
 * @param payloadlength.byte.high (uint8_t) high byte of the payload length
 * @param payload (uint8_t []) array that stores the payload
 * @param checksum (union) union variable that can either be a word or byte struct
 * @param checksum.value (uint16_t) checksum as a uint16_t word
 * @param checksum.bytes.sum1 (uint8_t) sum1 of the checksum
 * @param checksum.bytes.sum2 (uint8_t) sum2 of the checksum
 */
typedef struct usb_message {
    uint16_t sync;

    uint8_t class_id;
    uint8_t subclass_id;

    // to make it easier to write and read length, I am storing it as a union
    // so we can mess with the bytes when reading the UART bus or calculating
    // checksum, then use the word when needing it for a for loop and such
    union {
        struct {
            uint8_t low;
            uint8_t high;
        } bytes;
        uint16_t value;
    } payload_length;

    uint8_t payload[MAX_PAYLOAD_SIZE];

    // similar reason as the lenght to make into a union
    union {
        struct {
            uint8_t sum1;
            uint8_t sum2;
        } bytes;
        uint16_t value;
    } checksum;

} usb_message_t;

typedef enum usb_error_code {
    SUCCESS = 0,
    FAILURE = -1,
    //add more if needed
    WRONG_SYNC = 1,
    WRONG_CLASS = 2,
    WRONG_SUBCLASS = 3,
    PAYLOAD_EXCEEDS_MAX = 4,
    CHECKSUM_WRONG = 5,
    TIMEOUT = 10
} usb_errcode_t;


/* -------------------------------------------------------------------------- */
/*                                 PROTOTYPES                                 */
/* -------------------------------------------------------------------------- */

/**
 * @brief Stolen from wikipedia, modified fletcher sum function that takes in our custom
 *        struct and reads it in a "safe" 🦀🤢 way. Returns 16 bit Fletcher Checksum value.
 *
 * @param msg
 * @return uint16_t
 */
uint16_t Fletcher16_msg(const usb_message_t* msg );

/**
 * @brief function to parse and validates usb packets
 * 
 * @param msg (usb_message_t*) message that is received
 * @return usb_errcode_t status code
 */
usb_errcode_t parse_message(usb_message_t *msg);

/**
 *  @brief function that sends the raw values of the message
 *
 *  @param msg (usb_message_t*) message to send
 *  @return usb_errcode_t status code
 */
usb_errcode_t send_message(const usb_message_t *msg);

/**
 * @brief Sends a ACK msg to computer 
 */
void send_ACK(void);

/**
 * @brief Sends a NAK msg to computer 
 */
void send_NAK(void);

#endif // MIL_ELECTRICAL_MESSAGE_SYSTEM_H_
