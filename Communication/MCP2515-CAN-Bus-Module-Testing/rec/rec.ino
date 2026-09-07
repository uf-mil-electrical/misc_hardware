#include <SPI.h>
#include <ACAN2515.h>

static const byte CS_PIN = 26;
static const byte INT_PIN = 27;

ACAN2515 can(CS_PIN, SPI, INT_PIN);

void setup() {
  Serial.begin(115200);

  SPI.begin(18, 19, 23); // SCK, MISO, MOSI

  // IMPORTANT: 8 MHz crystal version (matches your sender)
  ACAN2515Settings settings(8000000, 500000);

  uint16_t errorCode = can.begin(settings, [] { can.isr(); });

  if (errorCode != 0) {
    Serial.print("CAN init failed: 0x");
    Serial.println(errorCode, HEX);
    while (1);
  }

  Serial.println("RECEIVER READY");
}

void loop() {
  CANMessage frame;

  if (can.receive(frame)) {

  Serial.print("Received ID: 0x");
  Serial.print(frame.id, HEX);

  Serial.print(" | LEN: ");
  Serial.print(frame.len);

  Serial.print(" | Data: ");

  for (uint8_t i = 0; i < frame.len; i++) {
    Serial.print((char)frame.data[i]);
  }

  Serial.println();
  }
    delay(1000); 
  }
