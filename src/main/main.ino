#include <NmraDcc.h>
#include <Servo.h>

#define STRAIGHT 1
#define DIVERGING 0
#define OFF 2

#define A 0
#define B 1
#define C 2

#define NUM_TURNOUTS 5

#define PIN_SERVO 0
#define PIN_RELE 1
#define STRAIGHT_POS 2
#define DIVERGING_POS 3
#define POSTITONS_IDX 4

// [ PIN SERVO, PIN RELE, STRAIGHT POS, DIVERGING POS, POSTITONS IDX ]
int turnouts[NUM_TURNOUTS][5] = {
{ 4,  5, 70, 110, A},
{ 6,  7, 70, 110, A},
{ 8,  9, 70, 110, B},
{10, 11, 60, 120, B},
{13, 12, 60, 120, C}
};

Servo servos[NUM_TURNOUTS];

int positions[] = {STRAIGHT,STRAIGHT,STRAIGHT};

NmraDcc  Dcc;

void setup() {
  Serial.begin(115200);

  initDcc();
  initServos();

  Serial.println("Ready.");
}

void loop() {
  loopDcc();
}

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

void initServos() {
  for (int idx = 0; idx < NUM_TURNOUTS; idx++) {
    servos[idx].attach(turnouts[idx][PIN_SERVO]);
    pinMode(turnouts[idx][PIN_RELE], OUTPUT);
    delay(15);
  }

  for (int idx = 0; idx < NUM_TURNOUTS; idx++) {
    servos[idx].write(turnouts[idx][STRAIGHT_POS]);
    digitalWrite(turnouts[idx][PIN_RELE], 1);
    delay(15);
  }
}

void updateServos() {
  Serial.println("---------------") ;
  for (int idx = 0; idx < NUM_TURNOUTS; idx++) {
    int positionIdx = turnouts[idx][POSTITONS_IDX];
    int state = positions[positionIdx];
    int servoPos = (state!=OFF) ? turnouts[idx][2+state] : 90;
    digitalWrite(turnouts[idx][PIN_RELE], state);
    servos[idx].write(servoPos);

    Serial.print("servo: ") ;
    Serial.print(idx) ;
    Serial.print(" servoPos: ");
    Serial.print(servoPos) ;
    Serial.print(" state: ");
    Serial.print(state) ;
    Serial.print(" pin: ");
    Serial.println(turnouts[idx][PIN_SERVO]) ;

    delay(15);
  }
}
