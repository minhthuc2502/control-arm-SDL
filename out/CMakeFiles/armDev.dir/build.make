# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/minhthuc/Desktop/control-arm/control-arm-SDL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/minhthuc/Desktop/control-arm/control-arm-SDL/out

# Include any dependencies generated for this target.
include CMakeFiles/armDev.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/armDev.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/armDev.dir/flags.make

CMakeFiles/armDev.dir/src/JoystickPS3.cpp.o: CMakeFiles/armDev.dir/flags.make
CMakeFiles/armDev.dir/src/JoystickPS3.cpp.o: ../src/JoystickPS3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/minhthuc/Desktop/control-arm/control-arm-SDL/out/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/armDev.dir/src/JoystickPS3.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/armDev.dir/src/JoystickPS3.cpp.o -c /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/JoystickPS3.cpp

CMakeFiles/armDev.dir/src/JoystickPS3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/armDev.dir/src/JoystickPS3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/JoystickPS3.cpp > CMakeFiles/armDev.dir/src/JoystickPS3.cpp.i

CMakeFiles/armDev.dir/src/JoystickPS3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/armDev.dir/src/JoystickPS3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/JoystickPS3.cpp -o CMakeFiles/armDev.dir/src/JoystickPS3.cpp.s

CMakeFiles/armDev.dir/src/JoystickPS3.cpp.o.requires:

.PHONY : CMakeFiles/armDev.dir/src/JoystickPS3.cpp.o.requires

CMakeFiles/armDev.dir/src/JoystickPS3.cpp.o.provides: CMakeFiles/armDev.dir/src/JoystickPS3.cpp.o.requires
	$(MAKE) -f CMakeFiles/armDev.dir/build.make CMakeFiles/armDev.dir/src/JoystickPS3.cpp.o.provides.build
.PHONY : CMakeFiles/armDev.dir/src/JoystickPS3.cpp.o.provides

CMakeFiles/armDev.dir/src/JoystickPS3.cpp.o.provides.build: CMakeFiles/armDev.dir/src/JoystickPS3.cpp.o


CMakeFiles/armDev.dir/src/main.cpp.o: CMakeFiles/armDev.dir/flags.make
CMakeFiles/armDev.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/minhthuc/Desktop/control-arm/control-arm-SDL/out/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/armDev.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/armDev.dir/src/main.cpp.o -c /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/main.cpp

CMakeFiles/armDev.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/armDev.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/main.cpp > CMakeFiles/armDev.dir/src/main.cpp.i

CMakeFiles/armDev.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/armDev.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/main.cpp -o CMakeFiles/armDev.dir/src/main.cpp.s

CMakeFiles/armDev.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/armDev.dir/src/main.cpp.o.requires

CMakeFiles/armDev.dir/src/main.cpp.o.provides: CMakeFiles/armDev.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/armDev.dir/build.make CMakeFiles/armDev.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/armDev.dir/src/main.cpp.o.provides

CMakeFiles/armDev.dir/src/main.cpp.o.provides.build: CMakeFiles/armDev.dir/src/main.cpp.o


CMakeFiles/armDev.dir/src/UdevHandler.cpp.o: CMakeFiles/armDev.dir/flags.make
CMakeFiles/armDev.dir/src/UdevHandler.cpp.o: ../src/UdevHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/minhthuc/Desktop/control-arm/control-arm-SDL/out/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/armDev.dir/src/UdevHandler.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/armDev.dir/src/UdevHandler.cpp.o -c /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/UdevHandler.cpp

CMakeFiles/armDev.dir/src/UdevHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/armDev.dir/src/UdevHandler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/UdevHandler.cpp > CMakeFiles/armDev.dir/src/UdevHandler.cpp.i

CMakeFiles/armDev.dir/src/UdevHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/armDev.dir/src/UdevHandler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/UdevHandler.cpp -o CMakeFiles/armDev.dir/src/UdevHandler.cpp.s

CMakeFiles/armDev.dir/src/UdevHandler.cpp.o.requires:

.PHONY : CMakeFiles/armDev.dir/src/UdevHandler.cpp.o.requires

CMakeFiles/armDev.dir/src/UdevHandler.cpp.o.provides: CMakeFiles/armDev.dir/src/UdevHandler.cpp.o.requires
	$(MAKE) -f CMakeFiles/armDev.dir/build.make CMakeFiles/armDev.dir/src/UdevHandler.cpp.o.provides.build
.PHONY : CMakeFiles/armDev.dir/src/UdevHandler.cpp.o.provides

CMakeFiles/armDev.dir/src/UdevHandler.cpp.o.provides.build: CMakeFiles/armDev.dir/src/UdevHandler.cpp.o


CMakeFiles/armDev.dir/src/ArmAL5D.cpp.o: CMakeFiles/armDev.dir/flags.make
CMakeFiles/armDev.dir/src/ArmAL5D.cpp.o: ../src/ArmAL5D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/minhthuc/Desktop/control-arm/control-arm-SDL/out/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/armDev.dir/src/ArmAL5D.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/armDev.dir/src/ArmAL5D.cpp.o -c /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/ArmAL5D.cpp

CMakeFiles/armDev.dir/src/ArmAL5D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/armDev.dir/src/ArmAL5D.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/ArmAL5D.cpp > CMakeFiles/armDev.dir/src/ArmAL5D.cpp.i

CMakeFiles/armDev.dir/src/ArmAL5D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/armDev.dir/src/ArmAL5D.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/ArmAL5D.cpp -o CMakeFiles/armDev.dir/src/ArmAL5D.cpp.s

CMakeFiles/armDev.dir/src/ArmAL5D.cpp.o.requires:

.PHONY : CMakeFiles/armDev.dir/src/ArmAL5D.cpp.o.requires

CMakeFiles/armDev.dir/src/ArmAL5D.cpp.o.provides: CMakeFiles/armDev.dir/src/ArmAL5D.cpp.o.requires
	$(MAKE) -f CMakeFiles/armDev.dir/build.make CMakeFiles/armDev.dir/src/ArmAL5D.cpp.o.provides.build
.PHONY : CMakeFiles/armDev.dir/src/ArmAL5D.cpp.o.provides

CMakeFiles/armDev.dir/src/ArmAL5D.cpp.o.provides.build: CMakeFiles/armDev.dir/src/ArmAL5D.cpp.o


CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.o: CMakeFiles/armDev.dir/flags.make
CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.o: ../src/TransmitionQueue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/minhthuc/Desktop/control-arm/control-arm-SDL/out/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.o -c /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/TransmitionQueue.cpp

CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/TransmitionQueue.cpp > CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.i

CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/TransmitionQueue.cpp -o CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.s

CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.o.requires:

.PHONY : CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.o.requires

CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.o.provides: CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.o.requires
	$(MAKE) -f CMakeFiles/armDev.dir/build.make CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.o.provides.build
.PHONY : CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.o.provides

CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.o.provides.build: CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.o


CMakeFiles/armDev.dir/src/log.cpp.o: CMakeFiles/armDev.dir/flags.make
CMakeFiles/armDev.dir/src/log.cpp.o: ../src/log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/minhthuc/Desktop/control-arm/control-arm-SDL/out/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/armDev.dir/src/log.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/armDev.dir/src/log.cpp.o -c /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/log.cpp

CMakeFiles/armDev.dir/src/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/armDev.dir/src/log.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/log.cpp > CMakeFiles/armDev.dir/src/log.cpp.i

CMakeFiles/armDev.dir/src/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/armDev.dir/src/log.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/log.cpp -o CMakeFiles/armDev.dir/src/log.cpp.s

CMakeFiles/armDev.dir/src/log.cpp.o.requires:

.PHONY : CMakeFiles/armDev.dir/src/log.cpp.o.requires

CMakeFiles/armDev.dir/src/log.cpp.o.provides: CMakeFiles/armDev.dir/src/log.cpp.o.requires
	$(MAKE) -f CMakeFiles/armDev.dir/build.make CMakeFiles/armDev.dir/src/log.cpp.o.provides.build
.PHONY : CMakeFiles/armDev.dir/src/log.cpp.o.provides

CMakeFiles/armDev.dir/src/log.cpp.o.provides.build: CMakeFiles/armDev.dir/src/log.cpp.o


CMakeFiles/armDev.dir/src/Server.cpp.o: CMakeFiles/armDev.dir/flags.make
CMakeFiles/armDev.dir/src/Server.cpp.o: ../src/Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/minhthuc/Desktop/control-arm/control-arm-SDL/out/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/armDev.dir/src/Server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/armDev.dir/src/Server.cpp.o -c /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/Server.cpp

CMakeFiles/armDev.dir/src/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/armDev.dir/src/Server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/Server.cpp > CMakeFiles/armDev.dir/src/Server.cpp.i

CMakeFiles/armDev.dir/src/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/armDev.dir/src/Server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/minhthuc/Desktop/control-arm/control-arm-SDL/src/Server.cpp -o CMakeFiles/armDev.dir/src/Server.cpp.s

CMakeFiles/armDev.dir/src/Server.cpp.o.requires:

.PHONY : CMakeFiles/armDev.dir/src/Server.cpp.o.requires

CMakeFiles/armDev.dir/src/Server.cpp.o.provides: CMakeFiles/armDev.dir/src/Server.cpp.o.requires
	$(MAKE) -f CMakeFiles/armDev.dir/build.make CMakeFiles/armDev.dir/src/Server.cpp.o.provides.build
.PHONY : CMakeFiles/armDev.dir/src/Server.cpp.o.provides

CMakeFiles/armDev.dir/src/Server.cpp.o.provides.build: CMakeFiles/armDev.dir/src/Server.cpp.o


# Object files for target armDev
armDev_OBJECTS = \
"CMakeFiles/armDev.dir/src/JoystickPS3.cpp.o" \
"CMakeFiles/armDev.dir/src/main.cpp.o" \
"CMakeFiles/armDev.dir/src/UdevHandler.cpp.o" \
"CMakeFiles/armDev.dir/src/ArmAL5D.cpp.o" \
"CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.o" \
"CMakeFiles/armDev.dir/src/log.cpp.o" \
"CMakeFiles/armDev.dir/src/Server.cpp.o"

# External object files for target armDev
armDev_EXTERNAL_OBJECTS =

armDev: CMakeFiles/armDev.dir/src/JoystickPS3.cpp.o
armDev: CMakeFiles/armDev.dir/src/main.cpp.o
armDev: CMakeFiles/armDev.dir/src/UdevHandler.cpp.o
armDev: CMakeFiles/armDev.dir/src/ArmAL5D.cpp.o
armDev: CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.o
armDev: CMakeFiles/armDev.dir/src/log.cpp.o
armDev: CMakeFiles/armDev.dir/src/Server.cpp.o
armDev: CMakeFiles/armDev.dir/build.make
armDev: /usr/lib/x86_64-linux-gnu/libevdev.so
armDev: /lib/x86_64-linux-gnu/libudev.so
armDev: CMakeFiles/armDev.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/minhthuc/Desktop/control-arm/control-arm-SDL/out/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable armDev"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/armDev.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/armDev.dir/build: armDev

.PHONY : CMakeFiles/armDev.dir/build

CMakeFiles/armDev.dir/requires: CMakeFiles/armDev.dir/src/JoystickPS3.cpp.o.requires
CMakeFiles/armDev.dir/requires: CMakeFiles/armDev.dir/src/main.cpp.o.requires
CMakeFiles/armDev.dir/requires: CMakeFiles/armDev.dir/src/UdevHandler.cpp.o.requires
CMakeFiles/armDev.dir/requires: CMakeFiles/armDev.dir/src/ArmAL5D.cpp.o.requires
CMakeFiles/armDev.dir/requires: CMakeFiles/armDev.dir/src/TransmitionQueue.cpp.o.requires
CMakeFiles/armDev.dir/requires: CMakeFiles/armDev.dir/src/log.cpp.o.requires
CMakeFiles/armDev.dir/requires: CMakeFiles/armDev.dir/src/Server.cpp.o.requires

.PHONY : CMakeFiles/armDev.dir/requires

CMakeFiles/armDev.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/armDev.dir/cmake_clean.cmake
.PHONY : CMakeFiles/armDev.dir/clean

CMakeFiles/armDev.dir/depend:
	cd /home/minhthuc/Desktop/control-arm/control-arm-SDL/out && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/minhthuc/Desktop/control-arm/control-arm-SDL /home/minhthuc/Desktop/control-arm/control-arm-SDL /home/minhthuc/Desktop/control-arm/control-arm-SDL/out /home/minhthuc/Desktop/control-arm/control-arm-SDL/out /home/minhthuc/Desktop/control-arm/control-arm-SDL/out/CMakeFiles/armDev.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/armDev.dir/depend

