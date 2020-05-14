cmake_minimum_required( VERSION 3.1 )
project (unit_test_control_arm)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")  #-Werror -D_REENTRANT")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../CMake)
find_package(Libevdev REQUIRED)
find_package(Libudev REQUIRED)
find_package(SDL2 REQUIRED)
#
# Declare the directories of header file
#
include_directories(${CMAKE_SOURCE_DIR}/../includes/
                    ${EVDEV_INCLUDE_DIRS}
                    ${UDEV_INCLUDE_DIRS}
                    ${SDL2_INCLUDE_DIRS}
                    /usr/lib/x86_64-linux-gnu/
                    )
#
# Add source file
#
file(GLOB_RECURSE SOURCES  ${CMAKE_SOURCE_DIR}/testcase/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/../includes/*.hpp ${CMAKE_SOURCE_DIR}/../includes/*.h)

#
# Define the relation between file execute and source file
#
add_executable(unittest ${SOURCES} ${HEADERS})

set_property(TARGET unittest PROPERTY CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ./)
#
# Use the library 
#
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(unittest
                      ${EVDEV_LIBRARIES} ${EVDEV_LDFLAGS}
                      ${UDEV_LIBRARIES} ${UDEV_LDFLAGS}
                      ${SDL2_LIBRARIES} ${SDL2_LDFLAGS}
                      microhttpd
                      pthread
                      -lboost_unit_test_framework
                      )