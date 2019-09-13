#include <RoboSail_Hardware.h>

/*********Functions for Setup ************/
void declarePins()
{
  pinMode(ROBOSAIL_PIN_RUDDER_RC, INPUT);
  pinMode(ROBOSAIL_PIN_SAIL_RC, INPUT);
  pinMode(ROBOSAIL_PIN_WIND, INPUT);

  // attach the servos to the proper pins
  rudderServo.attach(ROBOSAIL_PIN_RUDDER_SERVO);
  sailServo.attach(ROBOSAIL_PIN_SAIL_SERVO);
}


/*********Functions to read RC Transmitter/Receiver and Sensors *****/
 // Takes in the PWM signals from the RC Receiver and translate
 // them to the servo positions in degrees.
 // Takes in the PWM signals from the WindSensor and translate
 // it to the windvane position in degrees.

 void readReceiver()
 {
  // Read the command pulse from the RC receiver
  rudderPulseWidth = pulseIn(ROBOSAIL_PIN_RUDDER_RC, HIGH);
  sailPulseWidth = pulseIn(ROBOSAIL_PIN_SAIL_RC, HIGH);
  // Calculate the servo position in degrees.
  rudderPosition = map(rudderPulseWidth,
                       ROBOSAIL_RUDDER_RC_LOW, ROBOSAIL_RUDDER_RC_HIGH,
                       ROBOSAIL_RUDDER_ANGLE_LOW, ROBOSAIL_RUDDER_ANGLE_HIGH);
  sailPosition = map(sailPulseWidth,
                     ROBOSAIL_SAIL_RC_LOW, ROBOSAIL_SAIL_RC_HIGH,
                     ROBOSAIL_SAIL_ANGLE_LOW, ROBOSAIL_SAIL_ANGLE_HIGH);
 }

 void readWind()
 {
  // Read values from the WindSensor
  windPulseWidth = pulseIn(ROBOSAIL_PIN_WIND, HIGH);
  // Convert the wind angle to degrees from PWM.  Range -180 to +180
  windAngle = -map(windPulseWidth,
                   ROBOSAIL_WIND_SENSOR_LOW, ROBOSAIL_WIND_SENSOR_HIGH,
                   ROBOSAIL_WIND_ANGLE_LOW, ROBOSAIL_WIND_ANGLE_HIGH);
  windAngle = constrain(windAngle, ROBOSAIL_WIND_ANGLE_LOW, ROBOSAIL_WIND_ANGLE_HIGH);
 }

void readAccel()   /* Read the Accelerometer event and put data in variables */
{
  sensors_event_t accel_event;
  accel.getEvent(&event);   // will only need roll, pitch and yaw not necessary
  pitchAccel = event.acceleration.x;
  rollAccel = event.acceleration.y;
  yawAccel = event.acceleration.z;

  //define roll for RoboSail as rolling to Port side is positive, rolling to Starboard is negative
  robosailRollAccel  = -1 * rollAccel;
}
/************Functions to drive Sail and Rudder servos ****************/
 // This code takes in the desired postions for the servos in degrees (as
 // defined in RoboSail) then calculates appropriate values for the servo commands,
 // making sure not to send the servos to impossible positions, which could
 // damage the servo motors.
 // The Rudder servo motor ranges from 0 to 180 with 90 deg in the center
 // The Sailwinch servo is at ~55 deg when full-in, which we think of as 0 deg,
 // and ~125 deg when full out, which we think of as 90 deg

void driveSailServo(int sailPos)
{
  if ((sailPos >= ROBOSAIL_SAIL_ANGLE_LOW) && (sailPos <= ROBOSAIL_SAIL_ANGLE_HIGH))  // the command in degrees is valid
  {
    sailServoOut = map(sailPos,
                       ROBOSAIL_SAIL_ANGLE_LOW, ROBOSAIL_SAIL_ANGLE_HIGH,
                       ROBOSAIL_SAIL_SERVO_LOW, ROBOSAIL_SAIL_SERVO_HIGH);
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
  if ((rudderPos >= ROBOSAIL_RUDDER_ANGLE_LOW) && (rudderPos <= ROBOSAIL_RUDDER_ANGLE_HIGH))
  {
    rudderServoOut = map(rudderPos,
                         ROBOSAIL_RUDDER_ANGLE_LOW, ROBOSAIL_RUDDER_ANGLE_HIGH,
                         ROBOSAIL_RUDDER_SERVO_LOW, ROBOSAIL_RUDDER_SERVO_HIGH);
    rudderServo.write(rudderServoOut);
  }
  else
    {
    Serial.print("ERROR - rudder position out of range: ");
    Serial.println(rudderPos);
    }
}
/****************************************************/
// Function to Print out all values for debug.
void printToMonitor()
{
  Serial.print("Wind Angle: ");
  Serial.print(windAngle);

  Serial.print("     Sail, RC: ");
  Serial.print(sailPulseWidth);
  Serial.print("  desired angle: ");
  Serial.print(sailPosition);
  Serial.print("  to servo: ");
  Serial.print(sailServoOut);

  Serial.print("  Rudder, RC: ");
  Serial.print(rudderPulseWidth);
   Serial.print("  desired angle: ");
  Serial.print(rudderPosition);
  Serial.print("  to servo: ");
  Serial.print(rudderServoOut);

  Serial.print("\n"); // Print a new line
 /* Display the results (acceleration is measured in m/s^2) */

  Serial.print("robosailRoll: "); Serial.print(robosailRollAccel); Serial.print("  ");Serial.println("m/s^2 ");
  Serial.print("\n"); // Print a new line
}
