include_directories( ${OpenCV_INCLUDE_DIRS} )
# include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_library(camera STATIC
    src/Camera.cpp
)

target_include_directories(camera
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries( camera
    Dexode::EventBus
    ${OpenCV_LIBS} )