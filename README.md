# Description
The project aims to control a robotic arm with all kind of joystick (home made and commercial ones) or with server web.

## User-space applications

The user-space applications can be built using CMake. Some of them have dependencies that you will need to install first: `libevdev-dev libsdl2-dev libudev-dev libboost-dev libmicrohttpd-dev`

The easiest way to build it is to move to dev/user and run `cmake . && make`. This method allows you to build out of source wherever you want.
However, in each source directory, a `build.sh` script is provided for the sake of simplicity.

## Run applications
- After compiling source code, you can run program by 2 method:
> use play station 3 or nintendo switch

```
$ sudo ./armDev --mode "joystick" --config ../config/PS3Joystick.cfg
or 
$ sudo ./armDev --mode "joystick" --config ../config/nintendoJoystick.cfg
```

> use web server

```
$ sudo ./armDev --mode "server-web"
```

## Acces service web

- open/close connection with robotic arm using `localhost:3000/open`
- set position initial using `localhost:3000/initposition`
- control robotic arm using example `localhost:3000/shoulder?direction=1`





