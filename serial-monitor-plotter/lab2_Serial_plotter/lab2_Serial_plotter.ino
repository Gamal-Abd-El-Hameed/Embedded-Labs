void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 360; i += 10) {
    Serial.println(sin(i * DEG_TO_RAD));
    delay(50);
  }
}