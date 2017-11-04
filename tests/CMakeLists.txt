include_directories(${CMAKE_SOURCE_DIR}/json_lib)

set (SOURCE main.cpp)

add_executable(tests ${SOURCE})
target_link_libraries(tests json_lib)
