#include <TimerOne.h>

#include <LiquidCrystal_I2C.h>
#include <Wire.h>


LiquidCrystal_I2C lcd(0x27,16,2);

int year,month,day,dWeek,hours,seconds,minutes;
// const array include limit for seconds ,minutes, years, day week, months respectively
const int limitArr[6]={60,60,24,7,12};
bool input_OK=false;
//Use string array for month names, week of the day to display on screen
String dayWeek[] = {"Sat","Sun", "Mon", "Tue", "Wed", "Thu", "Fri"}; // Array of day names
String monthName[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; // Array of month names
int cursors_Posittion[6][2]={{4,0},{7,0},{10,0},{2,1},{6,1},{10,1}};
int iterr_count=0;
void Interrupt_fun(){
  interrupts();
  iterr_count++;
  if(iterr_count == 2 ){
    updateClock();
    updateScreen();
    iterr_count=0;
    }
  noInterrupts();
}
void updateClock(){
  if(input_OK){
  seconds++;
  if(seconds<limitArr[0]){return;}
  seconds=0;
  minutes++;
  if(minutes<limitArr[1]){return;}
  minutes=0;
  hours++;
  if(hours<limitArr[2]){return;}
  day=(day+1);
  dWeek=(dWeek+1)%7;
  if (month == 2) {
    // If current months is February
    if ((year % 4) == 0) {
      if(day<=29){return;}
    } else {
      if(day<=28){return;}
    }
  } 
  else if (month == 4 || month == 6 || month == 9 || month == 11) { 
    // If current months has 30 days
    if(day<=30){return;}
  } 
  else { 
    // If current months has 31 days
    if(day<=31){return;}
  }
  day=1;
  month++;
  if(month<limitArr[4]){return;}
  month=1;
  year++;
  }
}


void updateScreen(){
  if(input_OK){
  lcd.clear();
  lcd.setCursor(cursors_Posittion[0][0],cursors_Posittion[0][1]);
  String LCDScreen="";
  String sec=String(seconds);
  String min=String(minutes);
  String hour=String(hours);
  if(hour.length()<2)
  {
    LCDScreen += String("0" + hour);
    LCDScreen += ":";
  }
  else
  {
    LCDScreen += hour;
    LCDScreen += ":";
  }
  lcd.print(LCDScreen);
  lcd.setCursor(cursors_Posittion[1][0],cursors_Posittion[1][1]);
  LCDScreen="";
   if(min.length()<2)
  {
    LCDScreen += String("0" + min);
    LCDScreen += ":";
  }
  else
  {
    LCDScreen += min;
    LCDScreen += ":";
  }
  lcd.print(LCDScreen);
  lcd.setCursor(cursors_Posittion[2][0],cursors_Posittion[2][1]);
  LCDScreen="";
  if(sec.length()<2)
  {
    LCDScreen += String("0" + sec);
  }
  else
  {
    LCDScreen += sec;
  }
  lcd.print(LCDScreen);
  lcd.setCursor(cursors_Posittion[3][0],cursors_Posittion[3][1]);
  LCDScreen="";
  LCDScreen =dayWeek[dWeek-1] + "-" + monthName[month-1] + "-" + String(year);
  lcd.print(LCDScreen);
  }
}

void GetInitialDateTime(){
  Serial.println("\nEnter Year:"); 
  while (!Serial.available()) ;
  year = Serial.parseInt(); // Read the numeric input from the Serial port
  Serial.println(year);
  Serial.println("enter month:");
  while (!Serial.available()) ;
  month = Serial.parseInt(); // Read the numeric input from the Serial port
  Serial.println(month);
  Serial.println("enter Day:");
  while (!Serial.available()) ;
  day = Serial.parseInt(); // Read the numeric input from the Serial port
  Serial.println(day);
  Serial.println("enter Day of week");
  while (!Serial.available()) ;
  dWeek = Serial.parseInt(); // Read the numeric input from the Serial port
  Serial.println(dWeek);
  Serial.println("enter Hours");
  while (!Serial.available()) ;
  hours = Serial.parseInt(); // Read the numeric input from the Serial port
  Serial.println(hours);
  Serial.println("enter minutes");
  while (!Serial.available()) ;
  minutes = Serial.parseInt(); // Read the numeric input from the Serial port
  Serial.println(minutes);
  Serial.println("enter seconds");
  while (!Serial.available()) ;
  seconds = Serial.parseInt(); // Read the numeric input from the Serial port
  Serial.println(seconds);
  input_OK=true; 
}


void setup()
{
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  Timer1.initialize(500000);
  Timer1.attachInterrupt(Interrupt_fun); 
  GetInitialDateTime();
  updateScreen();
  
}

void loop()
{
  //  updateScreen();
  //  delay(1000);
}