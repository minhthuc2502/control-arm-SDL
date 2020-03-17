find_package(PkgConfig REQUIRED)
pkg_check_modules(PKG_EVDEV REQUIRED libevdev)

set(EVDEV_DEFINITIONS ${PKG_EVDEV_CFLAGS_OTHER})
find_path(EVDEV_INCLUDE_DIR libevdev/libevdev.h HINTS ${PKG_EVDEV_INCLUDE_DIR} ${PKG_EVDEV_INCLUDE_DIRS})
find_library(EVDEV_LIBRARY libevdev.so HINTS ${PKG_EVDEV_LIBDIR} ${PKG_EVDEV_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
#handle the QUIETLY and REQUIRED arguments and set EVDEV_FOUND to true if all listed variables are true
find_package_handle_standard_args(EVDEV DEFAULT_MSG EVDEV_INCLUDE_DIR EVDEV_LIBRARY)

mark_as_advanced(EVDEV_INCLUDE_DIR EVDEV_LIBRARY)

set(EVDEV_INCLUDE_DIRS ${EVDEV_INCLUDE_DIR})
set(EVDEV_LIBRARIES ${EVDEV_LIBRARY})
set(EVDEV_LDFLAGS ${PKG_EVDEV_LDFLAGS})
