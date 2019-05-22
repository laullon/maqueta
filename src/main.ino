#define STRAIGHT 1
#define DIVERGING 0
#define OFF 2

#define A 0
#define B 1
#define C 2

int positions[] = {STRAIGHT,STRAIGHT,STRAIGHT};

void setup() {
  Serial.begin(115200);

  initDisplay();
  initDcc();
  initServos();

  Serial.println("Ready.");
}

void loop() {
  loopDcc();
}
