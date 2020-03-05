cmake_minimum_required( VERSION 3.1 )
set (CMAKE_BUILD_TYPE Debug)
project (C++_arm_PS3joystick)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")  #-Werror -D_REENTRANT")
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
                    )
#
# Add source file
#
set(SOURCES
    src/JoystickPS3.cpp
    src/main.cpp
    src/UdevHandler.cpp
    src/ArmAL5D.cpp
    src/TransmitionQueue.cpp
    src/log.cpp
    )

option(DEBUG "use debug file" OFF)
if(${CMAKE_C_FLAGS_DEBUG} STREQUAL "-g")
  add_definitions(-DDEBUG)
endif()

option(RPI "Compile for RPI" OFF)
if(RPI)
  add_definitions(-DRPI)
endif()

#
# Define the relation between file execute and source file
#
add_executable(armDev ${SOURCES})

set_property(TARGET armDev PROPERTY CXX_STANDARD 11)
message(STATUS "EVDEV_LEDFLAGS = ${EVDEV_LDFLAGS}")

#
# Use the library 
#
target_link_libraries(armDev
                      ${EVDEV_LIBRARIES} ${EVDEV_LDFLAGS}
                      ${UDEV_LIBRARIES} ${UDEV_LDFLAGS}
                      ${SDL2_LIBRARIES} ${SDL2_LDFLAGS}
                      pthread
                      )

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/armDev
    DESTINATION bin
  RENAME ${CMAKE_PROJECT_NAME}-armDev)
