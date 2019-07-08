include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(motion-detector-tracker
    src/Main.cpp
)

target_link_libraries(motion-detector-tracker
    core
    Dexode::EventBus)