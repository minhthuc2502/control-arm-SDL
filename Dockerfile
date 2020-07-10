## GCC support can be specified at major, minor, or micro version
## (e.g. 8, 8.2 or 8.2.0).
FROM gcc:7.5.0

## These commands copy your files into the specified directory in the image
COPY . /usr/src/dockercontrolAL5Dapp

## and set that as the working location
WORKDIR /usr/src/dockercontrolAL5Dapp

## This command compiles your app using GCC, adjust for your source code
## 2 first lines to delete warning of using debconf
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
RUN apt-get update && apt-get install --assume-yes apt-utils
RUN apt-get install -y cmake
RUN apt-get install -y libevdev-dev
RUN apt-get install -y libsdl2-dev
RUN apt-get install -y libboost-dev
RUN apt-get install -y libmicrohttpd-dev
RUN ./build.sh .

## This command runs your application for control by web app, can change port, and standard http or https
CMD ["/bin/sh", "-c", "cd out/ && ./armDev -m server-web -p 3000 -s https"]

## This command runs your application for control by joystick, change parameters to choose file config
#CMD ["/bin/sh", "-c", "cd out/ && ./armDev -m joystick -c ../config/PS3Joystick.cfg"]

## This command just get in directory bin, you can run application by yourself (read README.md to know how to write command)
#CMD ["/bin/sh", "-c", "cd out/"]
## On terminal you can run container Docker like:
#docker run -it -p 3000:3000 devminhthuc/controlal5d /bin/sh
## Then run application with command line like the example in README.md
LABEL Name=control-arm-sdl Version=0.0.1
