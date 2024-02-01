#include <Servo.h>

class State{
public:

  
};

Servo mg995Servo; // create a servo object

int servoPin = 1; // define the PWM pin to which the servo is connected
// #define TRIG_PIN 2
// #define ECHO_PIN 3

void setup() {
  
  mg995Servo.attach(servoPin); // attaches the servo to the PWM pin
  mg995Servo.write(0);
  Serial.begin(9600);
  // pinMode(TRIG_PIN, OUTPUT);
  // pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Move the servo to the starting position (0 degrees)
  delay(3000); // Wait for 1 second
  
  // Move the servo to the middle position (90 degrees)
  mg995Servo.write(90);
  delay(3000); // Wait for 1 second
  
  // // Move the servo to the ending position (180 degrees)
  // mg995Servo.write(90);
  // delay(1000); // Wait for 1 second
}