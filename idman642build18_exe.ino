// --- Pin Definitions ---
#define ENB 11      // Motor A PWM pin
#define INB1 8       // Motor A direction pin 1
#define INB2 12      // Motor A direction pin 2
#define INA1 6       // Motor B direction pin 1
#define INA2 7       // Motor B direction pin 2
#define ENA 5        // Motor B PWM pin
#define LED 3        // Status LED

const int pingPin = 9;   // Ultrasonic trigger
const int echoPin = 10;  // Ultrasonic echo
const int buzzer  = 2;   // Buzzer for alert

int threshhold = 470;
int blinking = false;
long blinkTime;
int LEDON = LOW;

#define IR_SENSOR_LEFT_PIN  A2
#define IR_SENSOR_RIGHT_PIN A3

int turnratio = 0.75;
int basespeed = 180;
float ratioL = 1;
float ratioR = 1;
int RSpeed = -basespeed * ratioR;
int LSpeed = basespeed * ratioR;
long ultraDelay = millis();

bool init54 = true;

void stopMotorA() {
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, LOW);
  analogWrite(ENA, 0);
}
void stopMotorB() {
  digitalWrite(INB1, LOW);
  digitalWrite(INB2, LOW);
  analogWrite(ENB, 0);
}

void stopAllMotors() {
  stopMotorA();
  stopMotorB();
}

long getDis() {
  long duration, inches, cm;
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  return cm;
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

// Motor A control functions
void setMotorA(int speed) {
  speed = -constrain(speed, -255, 255); // Limit to 8-bit range
  
  if(speed > 0) {
    // Forward
    digitalWrite(INA1, HIGH);
    digitalWrite(INA2, LOW);
    analogWrite(ENA, speed);
  } else if(speed < 0) {
    // Reverse
    digitalWrite(INA1, LOW);
    digitalWrite(INA2, HIGH);
    analogWrite(ENA, -speed);
  } else {
    // Stop
    stopMotorA();
  }
}


// Motor B control functions
void setMotorB(int speed) {
  speed = -constrain(speed, -255, 255); // Limit to 8-bit range
  
  if(speed > 0) {
    // Forward
    digitalWrite(INB1, HIGH);
    digitalWrite(INB2, LOW);
    analogWrite(ENB, speed);
  } else if(speed < 0) {
    // Reverse
    digitalWrite(INB1, LOW);
    digitalWrite(INB2, HIGH);
    analogWrite(ENB, -speed);
  } else {
    // Stop
    stopMotorB();
  }
}



// Combined motor control
void setBothMotors(int speedA, int speedB) {
  setMotorA(speedA);
  setMotorB(speedB);
}



void Motorsetup() {  
  // Initialize PWM channels exactly as you specified
  // Setup direction pins
  pinMode(INA1, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(INB2, OUTPUT);
  
  // Initialize motors in stopped state
  stopMotorA();
  stopMotorB();
}


void setup(){
  Motorsetup();
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(IR_SENSOR_LEFT_PIN, INPUT);
  pinMode(IR_SENSOR_RIGHT_PIN, INPUT);

  digitalWrite(LED,LOW);
}

void loop(){
  if(init54 == true){
    int leftSensorState = analogRead(IR_SENSOR_LEFT_PIN);
    int rightSensorState = analogRead(IR_SENSOR_RIGHT_PIN);
    long cm = 0;
    if(millis()- ultraDelay > 500){
      ultraDelay = millis();
      cm = getDis();
    }
    if((leftSensorState >= threshhold || rightSensorState >= threshhold) && blinking == false ){
      digitalWrite(LED,HIGH);
      blinking = true;
      blinkTime = millis();
    }
    if(blinking && millis() - blinkTime > 500){
      blinkTime = millis();
      if(LEDON == HIGH){
        LEDON = LOW;
      }else{LEDON = HIGH;}
    }
    digitalWrite(LED,LEDON);
    if(cm <= 7 && cm > 0){
      digitalWrite(buzzer,HIGH);
      setBothMotors(0,0);
      delay(2000);
      digitalWrite(buzzer,LOW);
      digitalWrite(LED,LOW);
      init54 = false;
    }
  }

if (Serial.available()) {
    char message = Serial.read();
    String m = String(message);
    if(m == "S"){
      setBothMotors(0,0);
    }
    if(m == "F"){
      setBothMotors(RSpeed,LSpeed);
    }
    if(m == "B"){
      setBothMotors(-RSpeed,-LSpeed);
    }
    if(m == "L"){
      setBothMotors(RSpeed,-LSpeed);
    }
    if(m == "R"){
      setBothMotors(-RSpeed,LSpeed);
    }
    if(m == "G"){
      setBothMotors(RSpeed,-LSpeed*turnratio);
    }
    if(m == "H"){
      setBothMotors(-RSpeed*turnratio,LSpeed);
    }
    if(m == "I"){
      setBothMotors(-RSpeed,LSpeed*turnratio);
    }
    if(m == "J"){
      setBothMotors(RSpeed*turnratio,-LSpeed);
    }
  }
}