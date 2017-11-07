include_directories(${CMAKE_SOURCE_DIR})

set (SOURCE lib.cpp lib.h json_types.cpp json_types.h)

find_package(Boost 1.65)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_library(json_lib ${SOURCE})
else()
    message(FATAL_ERROR "Could not find Boost")
endif()



