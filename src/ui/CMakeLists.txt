find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(include ${GTKMM_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(gui 
    src/CameraDrawingArea.cpp
    src/MainWindow.cpp
    src/Main.cpp
)

target_link_libraries(gui ${GTKMM_LIBRARIES})
target_link_libraries( gui ${OpenCV_LIBS} )