#include <Servo.h>

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
