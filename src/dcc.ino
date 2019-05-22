#include <NmraDcc.h>

NmraDcc  Dcc;

void initDcc() {
  Dcc.pin(0, 2, 1);
  Dcc.init( MAN_ID_DIY, 10, CV29_ACCESSORY_DECODER | CV29_OUTPUT_ADDRESS_MODE, 0 );
  Serial.println("DCC Ready.");
}

void loopDcc() {
  Dcc.process();
}

extern "C" void notifyDccIdle(void) {
  // Serial.println("notifyDccIdle");
  updateDisplay();
}

extern "C" void notifyDccAccTurnoutOutput( uint16_t address, uint8_t direction, uint8_t outputPower ) {
  address += 4; // ???? multiMaus ???
  // Serial.print("notifyDccAccTurnoutOutput: ") ;
  // Serial.print(address,DEC) ;
  // Serial.print(',');
  // Serial.print(direction,DEC) ;
  // Serial.print(',');
  // Serial.println(outputPower, HEX) ;

  if(address <= 3) {
    positions[address-1] = direction;
  } else if (address == 99) {
    for (int i = 0; i < 3; i++) {
      positions[i] = (direction==DIVERGING) ? OFF : STRAIGHT;
    }
  }

  updateDisplay();
  updateServos();
}

// void IdlePacket_Handler(byte byteCount, byte* packetBytes) {
//   updateDisplay();
// }
//
// void BasicAccDecoderPacket_Handler(int address, boolean activate, byte data) {
//   address -= 1;
//   address *= 4;
//   address += 1;
//   address += (data & 0x06) >> 1;
//   address += 4; // ???? multiMaus ???
//   boolean enable = (data & 0x01) ? 1 : 0;
//
// }

