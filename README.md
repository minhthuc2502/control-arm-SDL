# Description
The project aims to control a robotic arm with all kind of joystick (home made and commercial ones) or with server web.

## User-space applications

The user-space applications can be built using CMake. Some of them have dependencies that you will need to install first: `libevdev-dev libsdl2-dev libudev-dev libboost-dev libmicrohttpd-dev`

After installing the packages above, if it exists an error not find directory, find directory `libmicrohttpd-dev.so` in your machine and change `include_directories : /usr/lib/x86_64-linux-gnu/` to your directory.

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
$ sudo ./armDev --mode "server-web" --port [Number of port listening]
```

## Acces service web

- open/close connection with robotic arm using `https://localhost:[port]/open`
- set position initial using `https://localhost:[port]/initposition`
- control robotic arm using example `https://localhost:[port]/shoulder?direction=1`

Otherwise, you can control robotic's arm by web application which will call rest api https. This web application give you a joystick virtual.  
> note
the port used to be called in web application is 3000. If you want to call rest api https in another port, please change url fetched in `app.js` 