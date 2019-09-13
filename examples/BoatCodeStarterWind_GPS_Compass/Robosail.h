// variables to hold input and output values
int rudderPulseWidth;
int rudderPosition = 0;
int rudderServoOut;
int sailPulseWidth;
int sailPosition = 45;
int sailServoOut;
//variables for WindSensor
int windAngle = 0;
int windPulseWidth = 0;

//create servo objects
Servo rudderServo;
Servo sailServo;

float pitchAccel = 0; //raw accelerometer value
float rollAccel = 0;  //raw accelerometer value
float yawAccel = 0;   //raw accelerometer value
float robosailRollAccel = 0;  // converted so Port lean is positive
float pitch = 0;  //value in degrees, converted from raw data
float roll = 0;   //value in degrees, converted from raw data
float yaw = 0;    //value in degrees, converted from raw data

float heading;  //value in degrees
float robosailHeading;  //value in degrees, converted to RoboSail FrameofRef
float robosailRoll;   // converted so Port lean is positive

/* Assign a ID to Accelerometer and Magnetometer and define eventt */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
sensors_event_t event;

//variables for GPS
// this will be false until GPS fix is found and starting position saved
bool start_pos_found = false;
int GPSfix;
int GPSqual;
int GPSsat;
// once GPS fix is found, these variables will be updated
float startPositionX = 0;
float startPositionY = 0;
float relPositionX = 0;
float relPositionY = 0;
float XYpos[2]; // this is xy position - it is in a 2 place array for x, y
float angleFromStart = 0;
