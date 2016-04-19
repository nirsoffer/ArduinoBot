
// Here's the motor manual : http://elesson.tc.edu.tw/md221/pluginfile.php/4241/mod_page/content/10/L298_Motor_Shield_Manual.pdf

//Arduino PWM Speed Control：

// V1 - simple interface

int M1 = 4; 
int E1 = 5;  
int E2 = 6;            
int M2 = 7;



unsigned long awakeTime = 2000;
int AVOID_THRESHOLD = 10;
int FULL_THROTTLE = 255;

// After setup() finishes, the loop() function runs over and over
// again, forever (or until you turn off or reset the Arduino).
// This is usually where the bulk of your program lives:

void setup() 
{ 
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(M1, OUTPUT);   
  pinMode(M2, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  randomSeed(analogRead(A0));
} 


void stopMotors () {
  analogWrite(E1, 0);
  analogWrite(E2, 0);
}

void back(int delayTime) { 
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  digitalWrite(E1, HIGH);
  digitalWrite(E2, HIGH);
  
  delay(delayTime); 
}

void turn(int angle) { // negative is stop E1, positive stop E2
  if (angle < 0 ) {
    analogWrite(E1, 0);
    analogWrite(E2, FULL_THROTTLE);  
  }
  else {
    analogWrite(E2, 0);
    analogWrite(E1, FULL_THROTTLE);  
  }
  delay(abs(angle));
  stopMotors();
}

int negativeRandom() {
  if (random(100)>50) {
    return 1;
  } 
  else {
    return -1; 
  }
}

void go(int ms) {
  Serial.println("I'm going! I'm going!");
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, FULL_THROTTLE);
  analogWrite(E2, FULL_THROTTLE); 
  delay(ms);
  stopMotors();
}

void loop()
{
  byte command = 0;
  Serial.println("Loop.");
  while (Serial.available() > 0 ) {
    command = Serial.read();
    Serial.print("Read: ");
    Serial.println(command);
    switch (command) {
      case 'g': go(100); break;
      case 'r': turn(100); break;
      case 'l': turn(-100); break;
      default: break;
    }
  }
}









