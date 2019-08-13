BoatCode
[![Build Status](https://travis-ci.org/RoboSail/BoatCode.svg?branch=master)](https://travis-ci.org/RoboSail/BoatCode)
========


BoatCode is a very thin Arduino library that serves as a container for starter boat code sketches for RoboSail.  Some examples use more sensors than others.

> As of this writing, the "library" portion of the library (the header file) is empty.  This is by design, taking advantage of [the format of an Arduino Library](https://github.com/arduino/Arduino/wiki/Arduino-IDE-1.5:-Library-specification) to easily bundle examples and present them to the Arduino IDE (in the dropdown menu of examples).


Installation
------------

This repository is an Arduino Library, and should be downloaded to your Arduino Libray folder -- the Libraries folder in the Sketchbook location.

For all information on pins and hardware calibration, this library depends on the `RoboSail_Hardware_Tests` library (which must be installed in the same way), available at:
https://github.com/RoboSail/RoboSail_Hardware_Tests

The purpose of this dependency is to ensure that the test code and vehicle code are using the same constants -- to ensure validity between tests and deployment.  These constants are defined in `RoboSail_Hardware.h` in `RoboSail_Hardware_Tests`.