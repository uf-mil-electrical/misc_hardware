#include "MIL_electrical_message_system.h"

/* -------------------------------------------------------------------------- */
/*                                 DEFINITIONS                                */
/* -------------------------------------------------------------------------- */

/* ------------------------------ MSG FUNCTIONS ----------------------------- */

uint16_t Fletcher16_msg(const usb_message_t* msg ) {
    uint16_t sum1 = 0;
    uint16_t sum2 = 0;
    int index;

    sum1 = (sum1 + msg->class_id) % 255;
    sum2 = (sum2 + sum1 ) % 255;

    sum1 = (sum1 + msg->subclass_id) % 255;
    sum2 = (sum2 + sum1) % 255;

    sum1 = (sum1 + msg->payload_length.bytes.low) % 255;
    sum2 = (sum2 + sum1) % 255;

    sum1 = (sum1 + msg->payload_length.bytes.high) % 255;
    sum2 = (sum2 + sum1) % 255;

    for ( index = 0; index < msg->payload_length.value; ++index )
    {
        sum1 = (sum1 + msg->payload[index]) % 255;
        sum2 = (sum2 + sum1) % 255;
    }

    return (sum2 << 8) | sum1;
}

usb_errcode_t parse_message(usb_message_t* msg) {

        uint8_t* ptr;

        if (getchar_timeout_us(0) != SYNC_HI)
            return WRONG_SYNC;

        if (getchar_timeout_us(1) != SYNC_LO)
            return WRONG_SYNC;

        msg->sync = SYNC_VALUE;

        // Read and store ids
        msg->class_id = getchar_timeout_us(1);
        msg->subclass_id = getchar_timeout_us(1);

        // Store next 2 bytes in length array
        msg->payload_length.bytes.low = getchar_timeout_us(1);
        msg->payload_length.bytes.high = getchar_timeout_us(1);

        // incase of overflow
        if (msg->payload_length.value > MAX_PAYLOAD_SIZE) {
            // Payload is too large
            return PAYLOAD_EXCEEDS_MAX;
        }

        // Store payload
        for (int i = 0; i < msg->payload_length.value; i++) {
            msg->payload[i] = getchar_timeout_us(1);
        }

        // Read next 2 bytes and store as 16bit int
        msg->checksum.bytes.sum1 = getchar_timeout_us(1);
        msg->checksum.bytes.sum2 = getchar_timeout_us(1);

        uint16_t result = Fletcher16_msg(msg);

        // Split the 16-bit result into two 8-bit values for comparison
        uint8_t sum2 = (result >> 8) & 0xFF;
        uint8_t sum1 = result & 0xFF;

        // Check if no errors occurred
        if (sum1 != msg->checksum.bytes.sum1 || sum2 != msg->checksum.bytes.sum2) {
            // return FAILURE; // Checksum mismatch
            return CHECKSUM_WRONG;
        } 

        return SUCCESS;
}


usb_errcode_t send_message(const usb_message_t *msg) {
    if (msg == NULL)
        return FAILURE;

    putchar_raw(SYNC_HI);
    putchar_raw(SYNC_LO);

    putchar_raw(msg->class_id);
    putchar_raw(msg->subclass_id);

    putchar_raw(msg->payload_length.bytes.low);
    putchar_raw(msg->payload_length.bytes.high);

    for (int i = 0; i < msg->payload_length.value; i++)
        putchar_raw(msg->payload[i]);

    putchar_raw(msg->checksum.bytes.sum1);
    putchar_raw(msg->checksum.bytes.sum2);

    return SUCCESS;
}

void send_ACK(void){
    usb_message_t msg;

    msg.class_id = META_CLASSID;
    msg.subclass_id = META_SUBID_ACKPACK;

    msg.payload_length.value = 0;

    uint16_t result = Fletcher16_msg(&msg);

    // Split the 16-bit result into two 8-bit values for comparison
    uint8_t sum2 = (result >> 8) & 0xFF;
    uint8_t sum1 = result & 0xFF;
        
    msg.checksum.bytes.sum1 = sum1;
    msg.checksum.bytes.sum2 = sum2;

    send_message(&msg);
}

void send_NAK(void) {
    usb_message_t msg;

    msg.class_id = META_CLASSID;
    msg.subclass_id = META_SUBID_NAKPACK;

    msg.payload_length.value = 0;

    uint16_t result = Fletcher16_msg(&msg);

    // Split the 16-bit result into two 8-bit values for comparison
    uint8_t sum2 = (result >> 8) & 0xFF;
    uint8_t sum1 = result & 0xFF;
        
    msg.checksum.bytes.sum1 = sum1;
    msg.checksum.bytes.sum2 = sum2;

    send_message(&msg);
}

