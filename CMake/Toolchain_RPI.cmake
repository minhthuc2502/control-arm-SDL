SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_VERSION 1)
SET(CMAKE_SYSTEM_PROCESSOR arm)

# specify the cross compiler
SET(CMAKE_C_COMPILER $ENV{PI_TOOLS}/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER $ENV{PI_TOOLS}/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-g++)

SET(CMAKE_LIBRARY_ARCHITECTURE "arm-linux-gnueabihf")

# define sysroot path
SET(CMAKE_SYSROOT $ENV{PI_SYSROOT})
SET(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})
# search for programs only in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# search for libraries and headers only in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Fix some find locations for the compiler?
include_directories(${CMAKE_SYSROOT}/usr/include/${CMAKE_LIBRARY_ARCHITECTURE})
link_directories(${CMAKE_SYSROOT}/usr/lib/${CMAKE_LIBRARY_ARCHITECTURE} ${CMAKE_SYSROOT}/lib/${CMAKE_LIBRARY_ARCHITECTURE})

# Fix pkg-config search paths
set(ENV{PKG_CONFIG_DIR} "")
set(ENV{PKG_CONFIG_LIBDIR} "${CMAKE_SYSROOT}/usr/lib/pkgconfig:${CMAKE_SYSROOT}/usr/share/pkgconfig:${CMAKE_SYSROOT}/usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/pkgconfig")
set(ENV{PKG_CONFIG_SYSROOT_DIR} ${CMAKE_SYSROOT})

# Add special definition for RPI
add_definitions(-DRPI)