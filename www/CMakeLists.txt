cmake_minimum_required(VERSION 3.14)
project(snake-ftxui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 自动拉取 FTXUI 依赖
include(FetchContent)
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
  GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)

# 编译可执行文件
add_executable(snake
  src/main.cpp
  src/SnakeGame.cpp
)

# 链接 FTXUI 库
target_link_libraries(snake
  PRIVATE ftxui::component
  PRIVATE ftxui::dom
  PRIVATE ftxui::screen
)