# Description
The project aims to control a robotic arm with with all kind of joystick (home made and commercial ones).

## User-space applications
The user-space applications can be built using CMake. Some of them have dependencies that you will need to install first: `libevdev-dev SDL2-dev libudev-dev`

The easiest way to build it is to move to dev/user and run `cmake . && make`. This method allows you to build out of source wherever you want.
However, in each source directory, a `build.sh` script is provided for the sake of simplicity.



