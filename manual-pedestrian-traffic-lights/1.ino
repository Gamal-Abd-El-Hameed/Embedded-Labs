int lastRed_State=HIGH;
void setup()
{
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  pinMode(8,OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(8,HIGH);
  digitalWrite(12,LOW);
}

void loop()
{
  if(debounce(2)){
     SwapPins(8,12);
  }
 
 // delay(20); 
}

void SwapPins(int pin1,int pin2)
{
  if(lastRed_State == HIGH){
       digitalWrite(pin1, LOW);
       digitalWrite(pin2,HIGH);
       lastRed_State=LOW;
  }
  else{
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2,LOW);
      lastRed_State=HIGH;
     }
}

boolean debounce(int pin)
{
  boolean state;
  boolean lastButtonState;
  lastButtonState=digitalRead(pin);
  for(int i=0;i<10;i++){
    delay(10);
    state=digitalRead(pin);
    if(lastButtonState != state){
     i=0;
     lastButtonState=state;
    }
  }
  return state ;
}