void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = 6;
  int y = 7;
  Serial.println(x + 2 * y);

}
