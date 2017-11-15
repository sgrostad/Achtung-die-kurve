cmake_minimum_required(VERSION 3.8)
project(achtung-die-kurve)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Player.cpp Utility.cpp Utility.hpp Player.cpp Player.hpp GameObject.hpp Snake.cpp Snake.hpp Line.cpp Line.hpp WindowSpec.cpp WindowSpec.hpp ResourcePath.hpp)
add_executable(achtung-die-kurve ${SOURCE_FILES})

set(/usr/local/Cellar/sfml/)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(achtung-die-kurve ${SFML_LIBRARIES})
endif()