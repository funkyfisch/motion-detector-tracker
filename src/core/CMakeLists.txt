include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_library(core STATIC
    src/Core.cpp
)

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(core
    PUBLIC
        ${CMAKE_THREAD_LIBS_INIT}
        Dexode::EventBus
        camera
        motiondetect
)