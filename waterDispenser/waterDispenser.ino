#include <Servo.h>

Servo mg995Servo; // create a servo object
bool dispensing{false};
bool holding{false};
constexpr int SERVO_PIN{27}; // define the PWM pin to which the servo is connected
constexpr int SENSOR_PIN{28};  // This is our input pin
uint onHoldCount = 0;
uint offHoldCount = 0;
constexpr uint ON_THRESHOLD{3};
constexpr uint OFF_THRESHOLD{2};
constexpr uint CYCLE_TIME_ms{100};
constexpr int OPEN_SERVO_VALUE{90};
constexpr int CLOSE_SERVO_VALUE{0};

void setupServo(){
  mg995Servo.attach(SERVO_PIN); // attaches the servo to the PWM pin
  mg995Servo.write(CLOSE_SERVO_VALUE);
};

void setupSensor(){
  pinMode(SENSOR_PIN, INPUT);
}

void closeTap()
{
  Serial.println("Close");
  mg995Servo.write(CLOSE_SERVO_VALUE);
}

void openTap()
{
  Serial.println("Open");
  mg995Servo.write(OPEN_SERVO_VALUE);
}

bool cupDetected()
{
  int reading = digitalRead(SENSOR_PIN);
  if(reading == LOW) return true;
  return false;
}

void checkReady()
{
  if(onHoldCount>ON_THRESHOLD){
    // Serial.println("Ready to dispense!");
    dispensing = true;
  }
  else{
   onHoldCount++;
   Serial.println("ON Holding");
  }
  offHoldCount = 0; // offHolding resets whenever cup is detected
}

void checkIdle()
{
  if(offHoldCount>OFF_THRESHOLD){
    // Serial.println("Back to idle!");
    dispensing = false;
    onHoldCount = 0;
  }
  else{
   offHoldCount++;
   Serial.println("OFF Holding");
  }
  onHoldCount = 0; // onHolding resets whenever no cup is detected
}

void checkSensor(){
  if (cupDetected()){
    checkReady();
  }
  else {
    checkIdle();
  }
};
void updateServo(){
  if(dispensing)
  openTap();
  else closeTap();
};

void setup() {
  Serial.begin(9600);
  Serial.println("Start!");
  setupServo();
  setupSensor();

}

void loop() {
  checkSensor();
  updateServo();
  delay(CYCLE_TIME_ms);
}  