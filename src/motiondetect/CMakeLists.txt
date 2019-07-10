include_directories( ${OpenCV_INCLUDE_DIRS} )
# include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_library(motiondetect STATIC
    src/MotionDetect.cpp
)

target_include_directories(motiondetect
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries( motiondetect
    Dexode::EventBus
    ${OpenCV_LIBS}
    camera
)