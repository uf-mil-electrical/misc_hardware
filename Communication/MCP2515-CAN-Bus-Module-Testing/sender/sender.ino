#include <SPI.h>
#include <ACAN2515.h>

static const byte CS_PIN = 26;
static const byte INT_PIN = 27;

ACAN2515 can (CS_PIN, SPI, INT_PIN);

void setup () {
  Serial.begin(115200);

  SPI.begin(18, 19, 23); // SCK, MISO, MOSI

ACAN2515Settings settings(
    8000000,   // 8 MHz crystal
    500000     // CAN bitrate
);

  uint16_t errorCode = can.begin(settings, [] { can.isr(); });

  if (errorCode != 0) {
    Serial.print("CAN init failed: 0x");
    Serial.println(errorCode, HEX);
    while (1);
  }

  Serial.println("SENDER READY");
}

void loop () {
  CANMessage frame;

  frame.id = 0x123;
  frame.len = 5;

  frame.data[0] = 'H';
  frame.data[1] = 'E';
  frame.data[2] = 'L';
  frame.data[3] = 'L';
  frame.data[4] = 'O';

  if (can.tryToSend(frame)) {
    Serial.println("Sent: HELLO");
  } else {
    Serial.println("Send failed");
  }

  delay(1000);
}