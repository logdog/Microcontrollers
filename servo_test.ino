/*
 * Servo Testing
 * Logan Dihel
 * 9-13-17
 * Code for basic robot functionality
 * Added push button for robot direction.
 * 
 * See https://www.arduino.cc/en/Reference/Servo for documentation on the Servo.h library
 */

#include <Servo.h> 

// macros for servo.writeMilliseconds(int)
#define MAX_SPEED_MILLIS 2000
#define STOP_SPEED_MILLIS 1515
#define MIN_SPEED_MILLIS 1000

// macro for fastest speed in the user-defined functions
#define MAX_SPEED MAX_SPEED_MILLIS - STOP_SPEED_MILLIS

// marcos for pin connections
#define SERVO_LEFT_PIN 30
#define SERVO_RIGHT_PIN 31
#define BUTTON_PIN 32

// macro for enabling and disabling the push button feature
// comment out this line below to disable the feature
#define USE_BUTTON

// enum for determining direction
#ifdef USE_BUTTON
enum direction {
  forward,
  stoppedF, // stopped: was forward
  reverse,
  stoppedR  // stopped: was reverse
};
#endif // USE_BUTTON

// globals defined here
Servo servoLeft, servoRight;

#ifdef USE_BUTTON
direction robot_direction;
#endif

/*
 * void setup(void):
 * Attaches pins to proper servos, 
 * sets robot in proper direction,
 * starts serial connection.
 */
void setup()
{
   servoLeft.attach(SERVO_LEFT_PIN); 
   servoRight.attach(SERVO_RIGHT_PIN);

   moveLeftForward(0);
   moveRightForward(0);

   #ifdef USE_BUTTON
   robot_direction = forward;
   #endif // USE_BUTTON
   
   Serial.begin(9600); 
}

/*
 * void loop(void):
 * Logic section of program. Tells robot to move forward
 * backward or stop. Also includes logic for the button
 * and deciding which direction the robot should move.
 */
#ifdef USE_BUTTON
void loop()
{

  // robot movement
  if(robot_direction == forward) {
    moveForward(MAX_SPEED);
  }
  else if (robot_direction == reverse) {
     moveForward(-MAX_SPEED);
  }
  else { // robot_direction == stopped
    moveForward(0);
  }
  
  // check if button was pressed
  bool pressed_button = false;
  while(digitalRead(BUTTON_PIN)) {
     pressed_button = true;
  }

  // change direction of the robot
  if(pressed_button) {
    switch(robot_direction) {
      case forward:
        robot_direction = stoppedF;
        break;
      case reverse:
        robot_direction = stoppedR;
        break;
      case stoppedF:
        robot_direction = reverse;
        break;
      case stoppedR:
        robot_direction = forward;
        break;
    }
  }
}
#else // USE_BUTTON not defined
void loop() {
  Serial.println("Going left");
  moveLeftForward(MAX_SPEED);
  moveRightForward(0);
  delay(1000);

  Serial.println("Going straight");

  moveLeftForward(MAX_SPEED);
  moveRightForward(MAX_SPEED);
  delay(1000);

  Serial.println("Going right");

  moveLeftForward(0);
  moveRightForward(MAX_SPEED);
  delay(1000);

  Serial.println("Going straight");

  moveLeftForward(MAX_SPEED);
  moveRightForward(MAX_SPEED);
  delay(1000);
}
#endif // USE_BUTTON

/*
 * //======================\\
 * ||USER DEFINED FUNCTIONS||
 * \\======================//
 */

 
/*
 * void moveForward(int speed)
 * Moves the robot forward at a given speed.
 * Speed must be within -MAX_SPEED (-485) to MAX_SPEED (485).
 * Otherwise, speed will be adjsuted to fit this window.
 */
void moveForward(int speed) {
  moveLeftForward(speed);
  moveRightForward(speed);
}

/*
 * moveLeftForward(int speed)
 * Moves the left wheel forward.
 * Speed >= -MAX_SPEED (-485) and <= MAX_SPEED (485). Numbers outside this
 * range will be forced within bounds.
 */
void moveLeftForward(int speed) {
  speed = getSpeedBounds(speed);
  servoLeft.writeMicroseconds(STOP_SPEED_MILLIS + speed);
}

/*
 * moveRightForward(int speed)
 * Moves the right wheel forward.
 * Speed >= -MAX_SPEED (-485) and <= MAX_SPEED (485). Numbers outside this
 * range will be forced within bounds.
 */
void moveRightForward(int speed) {
  speed = getSpeedBounds(speed);
  servoRight.writeMicroseconds(STOP_SPEED_MILLIS - speed);
}

/*
 * int getSpeedBounds(int speed)
 * Takes parameter speed and forces it to be within the range of
 * -MAX_SPEED (-485) to MAX_SPEED (485). Returns this adjusted value.
 */
int getSpeedBounds(int speed) {
  if(speed > MAX_SPEED) {
    speed = MAX_SPEED;
  } else if (speed < -MAX_SPEED) {
    speed = -MAX_SPEED;
  }
  return speed;
}