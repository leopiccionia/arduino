#include <string.h>

String inputString = "";         // A string to hold incoming data
boolean stringComplete = false;  // Whether the string is complete

// X axis
#define M_X_01 13
#define M_X_02 12
#define M_X_03 11
#define M_X_04 10
int x_state = M_X_01; // Current X pin

// Y axis
#define M_Y_01 9
#define M_Y_02 8
#define M_Y_03 7
#define M_Y_04 6
int y_state = M_Y_01; // Current Y pin

// Z axis
#define M_Z_01 A0
#define M_Z_02 A1
#define M_Z_03 A2
#define M_Z_04 A3
int z_state = M_Z_01; // Current Z pin

// Switch pins
#define SWITCH_X 5
#define SWITCH_Y 4

// Current cartesians positions
int current_x = 0;
int current_y = 0;
int current_z = 0;

// Head stuff
int s = 10;

// Switch stuff

const char SPACE_CHAR = ' ';

void signal_and_sleep(int pin, int t){
  digitalWrite(pin, HIGH);
  delay(t);
  digitalWrite(pin, LOW);
  delay(t);
}

void inc_x(int t){
  current_x++;
  switch(x_state){
    case M_X_01:
      x_state = M_X_02;
      break;
    case M_X_02:
      x_state = M_X_03;
      break;
    case M_X_03:
      x_state = M_X_04;
      break;
    case M_X_04:
      x_state = M_X_01;
      break;
  }
  signal_and_sleep(x_state, t);
}

void inc_y(int t){
  current_y++;
  switch(y_state){
    case M_Y_01:
      y_state = M_Y_02;
      break;
    case M_Y_02:
      y_state = M_Y_03;
      break;
    case M_Y_03:
      y_state = M_Y_04;
      break;
    case M_Y_04:
      y_state = M_Y_01;
      break;
  }
  signal_and_sleep(y_state, t);
}

void dec_x(int t){
  current_x--;
  switch(x_state){
    case M_X_01:
      x_state = M_X_04;
      break;
    case M_X_02:
      x_state = M_X_01;
      break;
    case M_X_03:
      x_state = M_X_02;
      break;
    case M_X_04:
      x_state = M_X_03;
      break;
  }
  signal_and_sleep(x_state, t);
}

void dec_y(int t){
  current_y--;
  switch(y_state){
    case M_Y_01:
      y_state = M_Y_04;
      break;
    case M_Y_02:
      y_state = M_Y_01;
      break;
    case M_Y_03:
      y_state = M_Y_02;
      break;
    case M_Y_04:
      y_state = M_Y_03;
      break;
  }
  signal_and_sleep(y_state, t);
}

void z_up(int t){
  current_z++;
  switch(z_state){
    case M_Z_01:
      z_state = M_Z_02;
      break;
    case M_Z_02:
      z_state = M_Z_03;
      break;
    case M_Z_03:
      z_state = M_Z_04;
      break;
    case M_Z_04:
      z_state = M_Z_01;
      break;
  }
  signal_and_sleep(z_state, t);
}

void z_down(int t){
  current_z--;
  switch(z_state){
    case M_Z_01:
      z_state = M_Z_04;
      break;
    case M_Z_02:
      z_state = M_Z_01;
      break;
    case M_Z_03:
      z_state = M_Z_02;
      break;
    case M_Z_04:
      z_state = M_Z_03;
      break;
  }
  signal_and_sleep(z_state, t);
}



void mov_x(String inputString){
  int desired_x = inputString.toInt();
  while(desired_x > current_x)
    inc_x(20);
  while(desired_x < current_x)
    dec_x(20);
}

void mov_y(String inputString){
  int desired_y = inputString.toInt();
  while(desired_y > current_y)
    inc_y(20);
  while(desired_y < current_y)
    dec_y(20);
}



void setup() {
  Serial.begin(9600);         // Initialize serial
  inputString.reserve(200);   // Reserve 200 bytes for the inputString

  pinMode(M_X_01, OUTPUT);
  pinMode(M_X_02, OUTPUT);
  pinMode(M_X_03, OUTPUT);
  pinMode(M_X_04, OUTPUT);

  pinMode(M_Y_01, OUTPUT);
  pinMode(M_Y_02, OUTPUT);
  pinMode(M_Y_03, OUTPUT);
  pinMode(M_Y_04, OUTPUT);

  pinMode(M_Z_01, OUTPUT);
  pinMode(M_Z_02, OUTPUT);
  pinMode(M_Z_03, OUTPUT);
  pinMode(M_Z_04, OUTPUT);
  
  pinMode(SWITCH_X, INPUT);
  pinMode(SWITCH_Y, INPUT);
  
  
  // RESET
   
  z_up(s);
  z_up(s);
  z_up(s);
  z_up(s);
  z_up(s);
  z_up(s);  
  z_up(s);
  z_up(s);
  z_up(s);
  z_up(s);
  z_up(s);
  
  
 
  while(1){
    if(digitalRead(SWITCH_X) == LOW) break;
    dec_x(s);
  }

  while(1){
    if(digitalRead(SWITCH_Y) == LOW) break;
     dec_y(s);
  }


  
  current_x = 0;
  current_y = 0;
}


void loop() { 
  if (stringComplete) {
    //Serial.println(inputString);
    
    if(inputString.startsWith("INC_X"))
      inc_x(20);
    else if(inputString.startsWith("INC_Y"))
      inc_y(20);
    else if(inputString.startsWith("DEC_X"))
      dec_x(20);
    else if(inputString.startsWith("DEC_Y"))
      dec_y(20);
    else if(inputString.startsWith("Z_UP")){
      z_up(s);
      z_up(s);
      z_up(s);
      z_up(s);
      z_up(s);
      z_up(s);
      z_up(s);
      z_up(s);
      z_up(s);
    }
    else if(inputString.startsWith("Z_DOWN")){
      z_down(s);
      z_down(s);
      z_down(s);
      z_down(s);
      z_down(s);
      z_down(s);
      z_down(s);
      z_down(s);
      z_down(s);
    }
    else if(inputString.startsWith("MOV_X"))
      mov_x(inputString);
    else if(inputString.startsWith("MOV_Y"))
      mov_y(inputString);
    delay(50);
    inputString = "";
    stringComplete = false;
    
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX.  This routine is run between each
  time loop() runs, so using delay inside loop can delay
  response.  Multiple bytes of data may be available.
 */
void serialEvent() {
    while (Serial.available()) {
      char inChar = (char)Serial.read();    // Get the new byte
      inputString += inChar;
      if (inChar == '\n') {                 // If the incoming character is a newline, set a flag
        stringComplete = true;
      }
    }
}
