find_package(PkgConfig REQUIRED)
pkg_check_modules(PKG_UDEV REQUIRED libudev)

set(UDEV_DEFINITIONS ${PKG_UDEV_CFLAGS_OTHER})
find_path(UDEV_INCLUDE_DIR libudev.h HINTS ${PKG_UDEV_INCLUDE_DIR} ${PKG_UDEV_INCLUDE_DIRS})
find_library(UDEV_LIBRARY libudev.so HINTS ${PKG_UDEV_LIBDIR} ${PKG_UDEV_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
#handle the QUIETLY and REQUIRED arguments and set UDEV_FOUND to true if all listed variables are true
find_package_handle_standard_args(UDEV DEFAULT_MSG UDEV_INCLUDE_DIR UDEV_LIBRARY)

mark_as_advanced(UDEV_INCLUDE_DIR UDEV_LIBRARY)

set(UDEV_INCLUDE_DIRS ${UDEV_INCLUDE_DIR})
set(UDEV_LIBRARIES ${UDEV_LIBRARY})
set(UDEV_LDFLAGS ${PKG_UDEV_LDFLAGS})
