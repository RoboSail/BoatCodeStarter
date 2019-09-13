/*

Yes, this file is empty.

The initial goal of this library is simply to act as a nice package
for all the BoatCode examples.  However, any code that is common to
all (or at least several) examples should be relocated here in the
future.

Some possible candidates would be functions that do the following:

rudderPulseWidth = pulseIn(ROBOSAIL_PIN_RUDDER_RC, HIGH, 25000);
rudderServoOut = map(rudderPulseWidth, ROBOSAIL_RUDDER_RC_LOW, ROBOSAIL_RUDDER_RC_HIGH, -75, 75) + 90;

sailPulseWidth = pulseIn(ROBOSAIL_PIN_SAIL_RC, HIGH, 25000);
sailServoOut = map(sailPulseWidth, ROBOSAIL_SAIL_RC_LOW, ROBOSAIL_SAIL_RC_HIGH, 0, 90);

windPulseWidth = pulseIn(ROBOSAIL_PIN_WIND, HIGH, 25000);
windAngle = map(windPulseWidth, ROBOSAIL_WIND_SENSOR_LOW, ROBOSAIL_WIND_SENSOR_HIGH, 180, -180);

*/
