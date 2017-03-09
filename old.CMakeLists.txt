cmake_minimum_required(VERSION 2.8.3)
project(mars)

set(CMAKE_BUILD_TYPE "Release")

find_package(catkin REQUIRED COMPONENTS
  cmake_modules
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_FFTW3 REQUIRED fftw3f)
pkg_check_modules(PC_ALSA REQUIRED alsa)
pkg_check_modules(PC_LIBCONFIG REQUIRED libconfig)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES mars
  CATKIN_DEPENDS
  DEPENDS
    PC_FFTW3
    PC_ALSA
    PC_LIBCONFIG
)

# include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories(include include/mars)
include_directories(
  ${PC_FFTW3_INCLUDE_DIRS}
  ${PC_ALSA_INCLUDE_DIRS}
  ${PC_LIBCONFIG_INCLUDE_DIRS}
)

file(GLOB_RECURSE SRC "*.c")

add_library(mars SHARED
  ${SRC}
)

target_link_libraries(mars
  ${PC_FFTW3_LIBRARIES}
  ${PC_ALSA_LIBRARIES}
  ${PC_LIBCONFIG_LIBRARIES}
)

add_executable(demo
  demo/demo.c
)

target_link_libraries(demo
  mars
)

## Mark executables and/or libraries for installation
install(TARGETS mars
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark cpp header files for installation
install(DIRECTORY include/
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)
install(DIRECTORY src/
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}/../src
  FILES_MATCHING PATTERN "*.h"
)
