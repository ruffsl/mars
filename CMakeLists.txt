cmake_minimum_required(VERSION 2.8.12)  # Ships with Ubuntu 14.04 (Trusty)
project(mars)

set(CMAKE_BUILD_TYPE "Release")

find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_FFTW3 REQUIRED fftw3f)
pkg_check_modules(PC_ALSA REQUIRED alsa)
pkg_check_modules(PC_LIBCONFIG REQUIRED libconfig)

# Install catkin package.xml
install(FILES package.xml DESTINATION share/mars)

include_directories("${PROJECT_SOURCE_DIR}/include")

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
