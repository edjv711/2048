project(2048 CXX)

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++1y")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -fsanitize=address")

add_executable(${PROJECT_NAME} main.cpp grid.cpp)

target_link_libraries(${PROJECT_NAME} ncurses)
