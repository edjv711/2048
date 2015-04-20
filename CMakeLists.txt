project(2048 CXX)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")

add_executable(${PROJECT_NAME} main.cpp grid.cpp)

target_link_libraries(${PROJECT_NAME} ncurses)
