/* BoatCodeStarterWindOnly rev 9/22/2019
© 2014-2019 RoboSail
Find detailed description in Decription tab
*/

#include <RoboSail_Hardware.h>  //Fill in min/max hardware parameters in this file
#include <Servo.h>
#include "declarations.h"       // tab with variable declarations

boolean displayValues = true;  //true calls function for values to be printed to monitor

void setup() {
  Serial.begin(115200);
  Serial.println("\nRoboSail BoatCode using WindSensor only - XXXXX");  //write program name here
  declarePins();    // Set RC receiver and WindSensor on digital input pins
}

void loop() {
//*********** Read in data from the RC receiver and sensors *********
readReceiver();
readWind();

// You should have values from the RC Receiver and Sensors in these variable: 
// rudderPosition, sailPosition, and windAngle
// Calculate new values for rudderPosition and sailPosition in degrees 
// and set those variables to the new values.
// If you do not set the values, it will use the values from the RC Receiver

//**************** your code here ******************


  
/********************* send commands to motors *************************/
  driveSailServo(sailPosition);
  driveRudderServo(rudderPosition);
  
  if (displayValues) {printToMonitor();}
  
} //end of loop()
