/* AutoRudder-POS with Switch - Sample code 1/19/2016
© 2014-2016 RoboSail
This program contains code for a boat to sail to
a specified Point of Sail (POS) using information from the Wind Sensor.
Rudder control can be manual or automatic, determined by the
Sail control lever.
For detailed information about getting input from the WindSensor,
input from the RC receiver, and sending output to the Servos,
see these programs: WindSensor and RCPassThrough
Sail control is always automatic.
The variable "automatic" sets the rudder to automatic.
The variable "POS" holds a specified point of sail.
Program values are displayed to the Serial Monitor when the
variable "verbose" is set to true.  otherwise set verbose to false.
*/

#include <Servo.h>
#include <RoboSail_Hardware.h>


boolean automatic = true; // set to true for automatic rudder
boolean verbose = true;  //true calls function for values to be printed to monitor
int POS=90; // desired wind angle

//************************//create servo objects
Servo rudderServo;
Servo sailServo;
//************************// variables to hold input and output values
int rudderPulseWidth;
int rudderServoOut;
int sailPulseWidth;
int sailServoOut;
//************************//variables for WindSensor
int windAngle = 0;
int windPulseWidth = 0;
int rudderPosition = 0;
int sailPosition = 45;

/****************************** SETUP ******************/
void setup() {
  Serial.begin(115200);
  Serial.println("\nRoboSail BoatCode - AutoRudderPOS with Switch");  //write program name here
  // Set RC receiver and WindSensor on digital input pins
  pinMode(ROBOSAIL_PIN_RUDDER_RC, INPUT);
  pinMode(ROBOSAIL_PIN_SAIL_RC, INPUT);
  pinMode(ROBOSAIL_PIN_WIND, INPUT);

  // attach the servos to the proper pins
  rudderServo.attach(ROBOSAIL_PIN_RUDDER_SERVO);
  sailServo.attach(ROBOSAIL_PIN_SAIL_SERVO);
}

void loop() {
//*********** Read in data from the RC receiver and sensors *********
  // Read the command pulse from the RC receiver
  rudderPulseWidth = pulseIn(ROBOSAIL_PIN_RUDDER_RC, HIGH);
  sailPulseWidth = pulseIn(ROBOSAIL_PIN_SAIL_RC, HIGH);
  // Calculate the servo position in degrees.
  sailPosition = map(sailPulseWidth, ROBOSAIL_SAIL_LOW, ROBOSAIL_SAIL_HIGH, 0, 90);
  rudderPosition = map(rudderPulseWidth, ROBOSAIL_RUDDER_LOW, ROBOSAIL_RUDDER_HIGH, -60, 60);

  // Read values from the WindSensor
  windPulseWidth = pulseIn(ROBOSAIL_PIN_WIND, HIGH);
  // Convert the wind angle to degrees from PWM.  Range -180 to +180
  windAngle = map(windPulseWidth, ROBOSAIL_WIND_LOW, ROBOSAIL_RUDDER_HIGH, 180, -180);
  windAngle = constrain(windAngle, -180, 180);  // gets rid of noisy readings

//**************** your code here ******************
// calculate your values for rudderPosition and sailPosition in degrees
// and set those variables to the new values.
// If you do not set the values, it will use the values from the Transmitter
// For example, to make the rudder follow the wind angle you would have:
// rudderPosition = windAngle;

/*******************  always set sail angle automatically *******************/

// sailPosition = (180-abs(windAngle))/2;  // a different algorithm for automatic sail

if (sailPulseWidth > 1850){automatic = true;} // use sail lever "full up" to set automatic
else {automatic = false;}

if (automatic)
  {
   rudderPosition = POS-windAngle;
   if (rudderPosition > 60) rudderPosition = 60;
   if (rudderPosition < -60) rudderPosition = -60;
    // rudderPosition = min(max((POS-windAngle),-60),60);  // alternate statement
  }
 // if automatic = false rudderPosition will be set by RC transmitter signal

 windAngle = abs(windAngle);           // sail position can only be positive
if (windAngle < 45) sailPosition = 0;
if ((windAngle >= 45) && (windAngle < 135)) sailPosition = windAngle - 45;
if (windAngle >= 135) sailPosition = 90;
/********************* send commands to motors *************************/
  driveSailServo(sailPosition);
  driveRudderServo(rudderPosition);

  if (verbose) {printToMonitor();}
} //end of loop()

/************Functions to drive Sail and Rudder servos ******************/
 // This code takes in the desired postions for the servos in degrees (as
 // defined in RoboSail) then calculates appropriate values for the servo commands,
 // making sure not to send the servos to impossible positions, which could
 // damage the servo motors.
 // The Rudder servo motor ranges from 0 to 180 with 90 deg in the center
 // The Sailwinch servo is at ~55 deg when full-in, which we think of as 0 deg,
 // and ~125 deg when full out, which we think of as 90 deg

void driveSailServo(int sailPos)
{
  if ((sailPos >= 0) && (sailPos <= 90))  // the command in degrees is valid
  {
    sailServoOut = map(sailPos, 0, 90, 55, 125);
    sailServo.write(sailServoOut);
  }
  else
  {
    Serial.print("ERROR - sail position out of range: ");
    Serial.println(sailPos);
    }
}

void driveRudderServo(int rudderPos)
{
  if ((rudderPos >= -60) && (rudderPos <= 60))
  {
    rudderServoOut = map(rudderPos, -90, 90, 0, 180);
    rudderServo.write(rudderServoOut);
  }
  else
    {
    Serial.print("ERROR - rudder position out of range: ");
    Serial.println(rudderPos);
    }
}

// Function to Print out all values for debug.
void printToMonitor()
{
  Serial.print("Mode: ");
  if (automatic) Serial.println("automatic rudder");
  else Serial.println("manual rudder");
  Serial.print("Wind Angle: ");
  Serial.print(windAngle);

  Serial.print("  Rudder, RC: ");
  Serial.print(rudderPulseWidth);
   Serial.print("  desired angle: ");
  Serial.print(rudderPosition);
  Serial.print("  to servo: ");
  Serial.print(rudderServoOut);

  Serial.print("     Sail, RC: ");
  Serial.print(sailPulseWidth);
  Serial.print("  desired angle: ");
  Serial.print(sailPosition);
  Serial.print("  to servo: ");
  Serial.print(sailServoOut);

  Serial.print("\n"); // Print a new line
}

