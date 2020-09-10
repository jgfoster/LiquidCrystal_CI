# Arduino CI and Unit Tests for LiquidCrystal

A [video](https://youtu.be/TEdCjEYrM6c) describing this library is available.

## Directory Organization

The top-level of this project is organized as follows:

* Hello1/
* Hello2/
* libraries/
  * HelloLCD/
  * LiquidCrystal_CI/
* LICENSE
* README.md

I suggest that you download and unzip this project to a temporary location (or fork/clone it to a checkout location), then _copy_ each of the four _folders_ (two top-level sketches and two libraries) to the appropriate Arduino location. In addition, install the [LiquidCrystal](https://www.arduino.cc/en/Reference/LiquidCrystal) library. With that done your Arduino folder should look something like the following:

* Arduino/
  * Hello1/
  * Hello2/
  * libraries/
    * HelloLCD/
    * LiquidCrystal/
    * LiquidCrystal_CI/

## Hello1 Sketch

[This](Hello1/Hello1.ino) simple sketch is based on a [tutorial](https://www.arduino.cc/en/Tutorial/HelloWorld) and prints "Hello sketch!" on the first line and a counter of seconds on the second line. It demonstrates the traditional method for using a standard library. Our problem with this approach is that it is not easy to use with automated tests.

## Hello2 Sketch and the HelloLCD Library

[This](Hello2/Hello2.ino) sketch has the same behavior as the prior sketch, but does so using an Arduino [Library](https://www.arduino.cc/en/Reference/Libraries). The sketch becomes a simple wrapper for the C++ code in the library which prints "Hello library!" on the first line and a counter of seconds on the second line. 

## Testing the HelloLCD Library

While the Hello2 sketch does not have any direct testing, the library is testable by [Arduino CI](https://github.com/ianfixes/arduino_ci), a cross-platform build/test system consting of a Ruby gem and a series of C++ mocks (see [Blink](https://github.com/jgfoster/Blink) for an introduction to this approach).

While it is relatively easy to test individual pins for high and low voltage using the hardware mocks provided by Arduino CI, it is less straightforward to test the impact of a series of commands sent to a device using those pins. For example, writing "Hello world!" to an LCD device may involve a couple hundred digitalWrite() instructions, and reverse-engineering the meanings is not trivial (but see [ReadPins.ino](https://github.com/jgfoster/Arduino/blob/master/LCD1602/ReadPins.ino)).

Since our [goal](https://stackoverflow.com/questions/780819/how-can-i-unit-test-arduino-code) is to test our code, not the standard libraries, it would be nice to have a higher-level interface to the [LiquidCrystal](https://www.arduino.cc/en/Reference/LiquidCrystal) library.

## LiquidCrystal_CI

One approach to testing _the use of_ a library (instead of testing the library itself) would be to mock the library (this is essentially the approach taken by Arduino CI) and we may come back and investigate this approach later.

Our current approach to testing is to use `LiquidCrystal_CI`, a subclass of `LiquidCrystal`, that intercepts and records the high-level function calls, then passes the request on to the the primary library (the superclass) for actual implementation. This means that in addition to capturing the high-level function calls, the pins are actually set and so we can let our test library run on the hardware itself (or let tests that look at the pins see the low-level actions).

The initial implementation captures such actions as setting the number of rows (see `LiquidCrystal_CI::begin(uint8_t cols, uint8_t lines, uint8_t dotsize)` in [`LiquidCrysal_CI.cpp](https://github.com/jgfoster/LiquidCrystal_CI/blob/master/libraries/LiquidCrystal_CI/LiquidCrystal_CI.cpp)) and testing those value [here](https://github.com/jgfoster/LiquidCrystal_CI/blob/master/libraries/HelloLCD/test/test.cpp). 

## Credits

This Arduino example was created in September 2020 by James Foster <arduino@jgfoster.net>.
