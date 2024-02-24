void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("please enter first number:");
  int firstNumb=readNumber();
  Serial.println(firstNumb);
  Serial.println("please enter second number:");
  int secondNumb=readNumber();
  Serial.println(secondNumb);
  int result =firstNumb+secondNumb;
  Serial.println("The result is:");
  Serial.println(result);
  Serial.println("----------------------------");
}
int readNumber(){
  char value[5];
  for(int i=0;i<5;){
    if(Serial.available( ))
    {
      char inpChar =Serial.read();
      value[i]=inpChar;
      i++;
    }
  }
 
  return atoi(value);
}