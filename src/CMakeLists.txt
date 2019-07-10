cmake_minimum_required(VERSION 3.1.0...3.5.0 FATAL_ERROR)
project( motion-detector-tracker VERSION 0.1 LANGUAGES CXX )

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" CMAKELISTS_FILE)
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} OR EXISTS "${CMAKELISTS_FILE}")
    message(FATAL_ERROR "
    Cannot write to source folder, please run CMake from another dir.
    Please remove CMakeCache.txt and CMakeFiles
    (or any directory without a CMakeLists.txt file) and then do an out-of-source build
    try console commands mkdir build && cd build && cmake ..
    ")
endif()

find_path(EventBus_INCLUDE_DIR ...)
if ((NOT EventBus_INCLUDE_DIR) OR (NOT EXISTS ${EventBus_INCLUDE_DIR}))
    message("${CMAKE_CURRENT_SOURCE_DIR}")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../lib/EventBus/lib" "${CMAKE_CURRENT_BINARY_DIR}/EventBus")
endif()

# add_library(EvBus)
# Add google test google mock library
set(GTEST_GMOCK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test-utils/gtest_gmock_1.7.0")

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
# set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=undefined -fno-sanitize=vptr")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -pthread \
    -std=c++17 \
    -Wcast-align \
    -pedantic \
    -Wcast-qual \
    -Wconversion \
    -Wctor-dtor-privacy \
    -Wdisabled-optimization \
    -Winit-self \
    -Wmissing-include-dirs \
    -Wnon-virtual-dtor \
    -Woverloaded-virtual \
    -Wparentheses \
    -Wredundant-decls \
    -Wshadow \
    -Wsign-promo \
    -Wstrict-aliasing \
    -Wundef \
    -Wall \
    -Wextra \
    ")
    # -Werror \

    
set(VERSION "1.0")
find_package( Threads REQUIRED )
find_package( OpenCV REQUIRED )

enable_testing()
add_subdirectory(core)
add_subdirectory(motiondetect)
add_subdirectory(camera)
add_subdirectory(app)
add_subdirectory(ui)