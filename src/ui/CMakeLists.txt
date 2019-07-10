find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(include ${GTKMM_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(motion-detector-tracker-gui 
    src/CameraDrawingArea.cpp
    src/MainWindow.cpp
    src/Main.cpp
)

target_link_libraries(motion-detector-tracker-gui
    ${GTKMM_LIBRARIES}
    ${OpenCV_LIBS}
    Dexode::EventBus
    core
)