cmake_minimum_required(VERSION 3.0)
project(eval)
set(SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)

include_directories("${PROJECT_SOURCE_DIR}/include")
add_executable(eval ${SOURCES})
set_property(TARGET eval PROPERTY CXX_STANDARD 17)
target_link_libraries(eval -llog4cplus)
target_compile_definitions(eval PRIVATE DEBUG_BUILD)
