cmake_minimum_required(VERSION 3.20)
project(gpu-game-of-life)

include_directories(lib/raylib/src)
add_executable(gpu-game-of-life src/main.cpp)

if(EMSCRIPTEN)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s ERROR_ON_UNDEFINED_SYMBOLS=0 -sALLOW_MEMORY_GROWTH --bind --memory")
set(CMAKE_EXECUTABLE_SUFFIX ".html") # This line is used to set your executable to build with the emscripten html template so that you can directly open it.

find_library(RL_LIBRARY NAMES raylib PATHS lib/raylib/src NO_DEFAULT_PATH NO_CMAKE_FIND_ROOT_PATH)
set_target_properties(gpu-game-of-life PROPERTIES LINK_FLAGS "--preload-file ${CMAKE_SOURCE_DIR}/resources@resources")
target_link_libraries(gpu-game-of-life ${RL_LIBRARY})
else()
add_subdirectory(lib/raylib)
target_link_libraries(gpu-game-of-life raylib)
file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})
endif()