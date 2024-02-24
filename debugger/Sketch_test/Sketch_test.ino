/*
 Name:		Sketch_test.ino
 Created:	5/15/2022 7:35:32 PM
 Author:	Ahmed
*/


int x;
int OutLed = 13;
int LatchButton = 4;
int State = LOW;
int buttonState = HIGH;
// the setup function runs once when you press reset or power the board
void setup() {
    x = 20;
    pinMode(OutLed, OUTPUT);
    pinMode(LatchButton, INPUT_PULLUP);
    digitalWrite(OutLed, LOW);
    Serial.begin(115200);
}

// the loop function runs over and over again until power down or reset
void loop() {

    if (digitalRead(LatchButton))
    {
        State = LOW;
        digitalWrite(OutLed, State);

    }
    else if(digitalRead(LatchButton)== LOW)
    {
        State = HIGH;
        digitalWrite(OutLed, State);
    }
    x++;
    buttonState = digitalRead(LatchButton);
    Serial.println(State);
    delay(10000);
}

