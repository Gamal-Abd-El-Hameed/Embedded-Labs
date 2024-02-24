#include <Servo.h>


// single_step & trace

bool single_step = true;
bool trace = false;

// action

#define ERROR 0
#define DISCH 1
#define CHARG 2
#define IDLE  3

char *action_lable[] = {"ERROR","DISCH  ","CHARG  ","IDLE   "};

int action_state = IDLE;
int next_action_state; 

// button 

bool button_led = false;
bool button_state = false;
bool button_led_state = false;
// volatile bool buttonInterrupted = false;
volatile bool button_latch = false;

int button_Pin = 2;
int button_led_Pin = 13;

unsigned long button_time = 0;  
unsigned long last_button_time = 0;

// max_limit

bool max_limit_state = false;

// min_limit

bool min_limit_state = false;

// threshold

bool threshold_state = false;

// time_to_limit

float time_to_limit_state = 9999.0;
float time_to_limit = 9999.0;

// interval

int interval_counter_state = 0;

float interval = 60.00;


// capacity

float capacity = 12000.0;

// rate

float max_charge_rate = 200.0;
float max_discharge_rate = 40.0;
float rate_state = 0.0; 
float next_rate_state;

// quantity

float max_quantity = 0.95 * capacity;
float min_quantity = 0.05 * capacity;
float quantity_state = 0.0;

// charge_pot

int   charge_pot_pin = PIN_A0;
float charge_pot_state = 0.0;
float charge_pot_percent = 0.0;

// discharge_pot

int   discharge_pot_pin = PIN_A1;
float discharge_pot_state = 0.0;
float discharge_pot_percent = 0.0;

// servo

Servo servo_control;
int servo_pin = 9;
float servo_state = 0.0;
float next_servo_state = 0.0;
   
// RGB_led

char *RGB_led_color[] = {"___    ","RED    ","GREEN  ","BLUE   "};

bool RGB_led_anode = true;

int RGB_led_disch_Pin = 3;
int RGB_led_charg_Pin = 4;
int RGB_led_idle_Pin = 5;

int next_RGB_led_state = IDLE;
int RGB_led_state = IDLE;

// report

bool report_state = false;

// buzzer

int  buzzer_pin = 6;
bool buzzer_state = false;
bool next_buzzer_state = false;

void setup () {

pinMode(button_Pin, INPUT_PULLUP);
pinMode(button_led_Pin, OUTPUT);
pinMode(RGB_led_disch_Pin, OUTPUT);
pinMode(RGB_led_charg_Pin, OUTPUT);
pinMode(RGB_led_idle_Pin, OUTPUT);
pinMode(buzzer_pin, OUTPUT);

// servo_pin below, _pot_pin  two anaalog

servo_control.attach(servo_pin);


// attachInterrupt(0, button_ISR, FALLING);
attachInterrupt(digitalPinToInterrupt(button_Pin), button_ISR, FALLING); /////////////////////////////////

Serial.begin(9600);

//
// test cases - override the above initial settings
//   numbered according to the given transition table 
//   labeled according to to expected action
// uncomment the one you choose
//

// 1IDLE
// action_state    = CHARG;
// button_state    = true;
// max_limit_state = false;
// min_limit_state = false;
// threshold_state = false;
// Serial.println("====  (1)IDLE  =====");
//

/* 2IDLE
action_state    = CHARG;
button_state    = false;
max_limit_state = true;
min_limit_state = false;
threshold_state = false;
Serial.println("====  (2)IDLE  =====");
*/

/* 3CHARG
action_state    = CHARG;
button_state    = false;
max_limit_state = false;
min_limit_state = false;
threshold_state = false;
Serial.println("====  (3))CHARG  =====");
*/

/* 4IDLE
action_state    = DISCH;
button_state    = true;
max_limit_state = false;
min_limit_state = false;
threshold_state = false;
Serial.println("====  (4)IDLE  =====");
*/

/* 5IDLE
action_state    = DISCH;
button_state    = false;
max_limit_state = false;
min_limit_state = true;
threshold_state = false;
Serial.println("====  (5))IDLE  =====");
*/

// 6DISCH
// action_state    = DISCH;
// button_state    = false;
// max_limit_state = false;
// min_limit_state = false;
// threshold_state = false;
// Serial.println("====  (6)DISCH  =====");
//

// 7DISCH
// action_state    = IDLE;
// button_state    = true;
// max_limit_state = true;
// min_limit_state = false;
// threshold_state = false;
// Serial.println("====  (7)DISCH  =====");
//

/* 8CHARG
action_state    = IDLE;
button_state    = true;
max_limit_state = false;
min_limit_state = true;
threshold_state = false;
Serial.println("====  (8)CHARG  =====");
*/


// 9DISCH
// action_state    = IDLE;
// button_state    = true;
// max_limit_state = false;
// min_limit_state = false;
// threshold_state = true;
// Serial.println("====  (9)DISCH  =====");
//

// 10CHARG
// action_state    = IDLE;
// button_state    = true;
// max_limit_state = false;
// min_limit_state = false;
// threshold_state = false;
// Serial.println("====  (10)CHARG  =====");
//

// 11IDLE
action_state    = IDLE;
button_state    = false;
max_limit_state = false;
min_limit_state = false;
threshold_state = false;
Serial.println("====  (11)IDLE  =====");
}


void loop () {

//calculate settings


   calcuate_report_setting();

   calculate_action_setting();
  
   calculate_rate_setting();
   
   calculate_servo_setting();
   
   calculate_buzzer_setting();
   
   calculate_RGB_led_setting();
   


// apply settings

   
   set_report();

   set_action(); 

   set_rate();

   set_servo();
   
   set_buzzer();

   set_RGB_led();


// delay or single step


   if (single_step)
   {
    
        Serial.println("     ??????????");
        Serial.println("     waiting");
  
        bool nothing_received = true;
        while (nothing_received)
        {
            //Check to see if anything is available in the serial receive buffer
            while (Serial.available() > 0)
            {
                 nothing_received = false;
                 char inByte = Serial.read();
            }
       }
    
       Serial.println("    ok");
  
    }
   

    else { delay (30000);}


// update  sensors

   // update  timing sensors

   update_interval_counter();
   
   // update  tank sensors

   update_quantity();
   
   update_max_limit();  
   
   update_min_limit();  

  //  update_threshold();  

   update_time_to_limit();  
   
   
   update_button();
   
   // update  pot sensors

   update_charge_pot();
   
   update_discharge_pot();

   cli(); 
  EIMSK |= _BV(INT0);
  sei();

  // if (buttonInterrupted) {
        // Clear the interrupt status
        
        
        // cli();
        // // unmask the external interrupt
        // EIMSK |= 0x03;

        // sei();
        // buttonInterrupted = false; ////////////////////////////////////////
        // button_state = false;
        // set_button_led (true);  // Do not press button 
  //   }

}

// report =========================

void calcuate_report_setting() {
      
  charge_pot_percent = charge_pot_state * 100.0; 
  discharge_pot_percent = discharge_pot_state * 100.0; 

}


void set_report () {

  Serial.println("********** REPORT  ********");

  Serial.print("INTERVAL#        ");
  Serial.println(interval_counter_state);

  Serial.print("ACTION           ");
  Serial.println(action_lable[action_state]);

  Serial.print("QUANTITY         ");
  Serial.println(quantity_state);

  Serial.print("PERCENTAGE         ");
  Serial.print(100.0 * quantity_state / capacity, 0);
  Serial.println("%");

  Serial.print("RATE             ");
  Serial.println(rate_state);

  Serial.print("TIME TO LIMIT    ");
  Serial.println(time_to_limit_state);

  Serial.print("BUTTON           ");
  Serial.println(button_state ? "TRUE  " : "FALSE ");

  Serial.println();

  Serial.print("BUTTON_LED       ");
  Serial.println(button_led_state ? "TRUE  " : "FALSE ");

  Serial.print("MAX_LIMIT        ");
  Serial.println(max_limit_state ? "TRUE  " : "FALSE ");

  Serial.print("MIN_LIMIT        ");
  Serial.println(min_limit_state ? "TRUE  " : "FALSE ");

  Serial.print("THRESHOLD        ");
  Serial.println(threshold_state ? "TRUE  " : "FALSE ");

  Serial.print("RGB_LED          ");
  Serial.println(RGB_led_color[RGB_led_state]);

  Serial.print("CHARGE_POT       ");
  Serial.print(charge_pot_percent,0);
  Serial.println("%");

  Serial.print("DISCHARGE_POT    ");
  Serial.print(discharge_pot_percent,0);
  Serial.println("%");

  Serial.print("SERVO_POSITION   ");
  Serial.println(servo_state,0);

  Serial.println("================================================");

  report_state = true;

if (trace && single_step)
{
  Serial.println("++++++++++***************+++++  report"); 
  Serial.print("report ");
  Serial.println(report_state ? "TRUE" : "FALSE");  
}

}


// action ====================

void calculate_action_setting(){
  if      ((action_state== CHARG) &&  button_state                   ) {next_action_state =  IDLE ;}
  else if ((action_state== CHARG) && !button_state&&  max_limit_state) {next_action_state =  IDLE ;} 
  else if ((action_state== CHARG) && !button_state&& !max_limit_state) {next_action_state =  CHARG;}  

  else if ((action_state== DISCH) &&  button_state                   ) {next_action_state =  IDLE ;}  
  else if ((action_state== DISCH) && !button_state&&  min_limit_state) {next_action_state =  IDLE ;}  
  else if ((action_state== DISCH) && !button_state&& !min_limit_state) {next_action_state =  DISCH;} 

  else if ((action_state== IDLE ) &&  button_state &&  !min_limit_state) {next_action_state =  DISCH;}  
  else if ((action_state== IDLE ) &&  button_state &&  min_limit_state) {next_action_state =  CHARG;} 
  else if ((action_state== IDLE ) && !button_state                   ) {next_action_state =  IDLE ;}  
  else {next_action_state =  ERROR;} 
}


void set_action(){
  action_state =  next_action_state;
}  



//
// *--------------------------------------------* 
// **************** TANK SENSORS **************** 
// *--------------------------------------------*
//
 
// quantity =================

void update_quantity() {  
  float old_quantity_state = quantity_state;
  float incr = rate_state * interval / 60;
  quantity_state = old_quantity_state + incr;
}


// max_limit =====================

void  update_max_limit() {
  max_limit_state = false;
  if (quantity_state >= max_quantity) {max_limit_state = true;}
}


// min_limit ===================

void  update_min_limit() {
  min_limit_state = false;
  if (quantity_state <= min_quantity) {min_limit_state = true;}
}


// threshold ===================

// void  update_threshold() {
//   threshold_state = false;
//   if (quantity_state > threshold_quantity) {threshold_state = true;}
// }
// *----------------------------end TANK SENSORS

// time_to_limit ===============

void  update_time_to_limit (){

  if      (action_state == IDLE)  {time_to_limit_state = 9999;}
  else if (action_state == CHARG) {time_to_limit_state = (max_quantity - quantity_state) / rate_state;}
  else if (action_state == DISCH) {time_to_limit_state = (min_quantity - quantity_state) / rate_state;}
  else                            {time_to_limit_state = -9999;}
}


//
// *---------------------------------------------* 
// **************** BUTTON SENSOR **************** 
// *---------------------------------------------*
//

//  button ===================
  
void  update_button() {

  bool old_button_latch = button_latch;
button_state = old_button_latch;
button_latch = false;
set_button_led (true);  // button ready  
}

// button_ISR =================

// void button_ISR() {

// button_time = millis();
// //check to see if increment() was called in the last 250 milliseconds
// if (button_time - last_button_time > 250)
//    {
//    button_latch = true ;
//    set_button_led (false);  // Do not press button 
//    last_button_time = button_time;
//    }
// }
 
void button_ISR() {
  cli();
  EIMSK &= ~(1 << INT0);
  EIFR |= (1 << INTF0);
    button_latch = true ;
   set_button_led (false);  // Do not press button 
  sei();  
}


void update_charge_pot() {

  float old_charge_pot_state = charge_pot_state ;

  int val = analogRead(charge_pot_pin);

  charge_pot_state = (float)val/1024.0;
}


// discharge_pot ===================

void update_discharge_pot() {

float old_discharge_pot_state = discharge_pot_state;

int val = analogRead(discharge_pot_pin);

discharge_pot_state = (float)val/1024.0;
}
// *------------------------------end POT SENSORS


// rate ===================

void calculate_rate_setting() {
  if      (action_state == DISCH) {next_rate_state = - max_discharge_rate * discharge_pot_state;}
  else if (action_state == CHARG) {next_rate_state =   max_charge_rate    *    charge_pot_state;}
  else if (action_state == IDLE ) {next_rate_state = 0.0;}
  else                            {next_rate_state = 0.0;}  
  
}
 
 
void set_rate() {
  float old_rate_state = rate_state;
  rate_state = next_rate_state;
}
 
 
// servo ========================

void calculate_servo_setting() {
  
  if (action_state == IDLE) { next_servo_state = 90.0; }
    else if (action_state == CHARG) { next_servo_state = charge_pot_state * 85.0/ max_charge_rate; }
    else if (action_state == DISCH) { next_servo_state = 180.0 + discharge_pot_state * 85.0; }
    else { next_servo_state = 90.0;}
    
}

 
void set_servo() {
  float old_servo_state = servo_state; 
  servo_state = next_servo_state;
  servo_control.write(servo_state); //////////////////////////////////////////
}

 
// buzzer ================
   
void calculate_buzzer_setting() {
  
    next_buzzer_state = false;
    
  bool charge_buzzer = (action_state == CHARG) && max_limit_state;
  bool discharge_buzzer = (action_state == DISCH) && min_limit_state;
  if( charge_buzzer || discharge_buzzer ) {next_buzzer_state = true;}   
}


void set_buzzer() {
  
  bool old_buzzer_state = buzzer_state;
  buzzer_state = next_buzzer_state;
  if (buzzer_state) {
    tone(buzzer_pin, 1500, 500);
  }
}


//
// *---------------------------------------------* 
// **********************  LEDS  ***************** 
// *---------------------------------------------*
//

// button_led =================

void set_button_led (bool settng) {

  bool old_button_led_state = button_led_state;

  if (settng) {
    
    digitalWrite(button_led_Pin, HIGH); 
    button_led_state = true;

    
    }
  else {
    
    digitalWrite(button_led_Pin, LOW); 
    button_led_state = false;

    }
} 


// RGB_led =================
     
void calculate_RGB_led_setting() {  
    next_RGB_led_state = action_state;  
}

   
void set_RGB_led() {
  
  int old_RGB_led_state = RGB_led_state;
  RGB_led_state = next_RGB_led_state;

  // all off  

  bool on  = !RGB_led_anode;
  bool off =  RGB_led_anode; 

  digitalWrite(RGB_led_disch_Pin, off);
  digitalWrite(RGB_led_charg_Pin, off);
  digitalWrite(RGB_led_idle_Pin , off);

  // only one on

  if (next_RGB_led_state == DISCH) {digitalWrite(RGB_led_disch_Pin, on);} 
  if (next_RGB_led_state == CHARG) {digitalWrite(RGB_led_charg_Pin, on);} 
  if (next_RGB_led_state == IDLE ) {digitalWrite(RGB_led_idle_Pin,  on);} 
}
// *--------------------------------------end LEDS


//
// *---------------------------------------------* 
// **************  TIMING COUNTERS  ************** 
// *---------------------------------------------*
//

// interval_counter  ==================

void update_interval_counter() {
  int old_interval_counter_state = interval_counter_state;
  interval_counter_state ++;
}
// *----------------------------end TIMING SENSORS

// ++++++++++  END  ++++++++++
