cmake_minimum_required( VERSION 3.1 )
set (CMAKE_BUILD_TYPE Debug)
project (C++_arm_PS3joystick)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")  #-Werror -D_REENTRANT -g")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
find_package(Libevdev REQUIRED)
find_package(Libudev REQUIRED)
find_package(SDL2 REQUIRED)
#
# Declare the directories of header file
#
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes
                    ${EVDEV_INCLUDE_DIRS}
                    ${UDEV_INCLUDE_DIRS}
                    ${SDL2_INCLUDE_DIRS}
                    /usr/lib/x86_64-linux-gnu/
                    )
#
# Add source file
#
set(SOURCES
    src/joystickPS3.cpp
    src/main.cpp
    src/udevhandler.cpp
    src/armAL5D.cpp
    src/transmitionqueue.cpp
    src/log.cpp
    src/servercontroller.cpp
    src/resthttp.cpp
    src/httpserver.cpp
    src/joystickVir.cpp
    )

# option(DEBUG "use debug file" OFF)
IF(CMAKE_BUILD_TYPE MATCHES Debug)
  add_definitions(-DDEBUG)
ENDIF()

option(RPI "Compile for RPI" OFF)
IF(RPI)
  add_definitions(-DRPI)
ENDIF()

#
# Define the relation between file execute and source file
#
add_executable(armDev ${SOURCES})

set_property(TARGET armDev PROPERTY CXX_STANDARD 11)
message(STATUS "EVDEV_LEDFLAGS = ${EVDEV_LDFLAGS}")

#
# Use the library 
#
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(armDev
                      ${EVDEV_LIBRARIES} ${EVDEV_LDFLAGS}
                      ${UDEV_LIBRARIES} ${UDEV_LDFLAGS}
                      ${SDL2_LIBRARIES} ${SDL2_LDFLAGS}
                      microhttpd
                      pthread
                      )
# Install program into usr/local/bin by make install
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/armDev
    DESTINATION bin
  RENAME ${CMAKE_PROJECT_NAME}-armDev)
