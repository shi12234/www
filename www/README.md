# AI驱动开发实践——FTXUI贪吃蛇游戏
本项目是课程大作业，基于C++结合FTXUI终端UI库开发贪吃蛇小游戏，全部代码由AI辅助生成，满足作业全部规范要求。

## 一、项目功能介绍
经典终端贪吃蛇游戏，使用FTXUI绘制终端图形界面，具备完整游戏逻辑：
1. 方向键控制蛇上下左右移动，禁止直接反向掉头
2. 随机生成红色食物，吃到食物增加分数、蛇身变长
3. 撞墙、撞到自身身体判定游戏结束
4. 游戏结束后按R一键重新开局，Q键退出程序
5. 实时展示当前得分与游戏状态提示

## 二、项目目录结构
```
www/
├── CMakeLists.txt    # CMake编译构建脚本，自动拉取FTXUI依赖
├── README.md         # 项目说明文档（本文件）
└── src/
    ├── main.cpp      # 程序入口 + FTXUI界面渲染、键盘交互
    ├── SnakeGame.h   # 贪吃蛇游戏逻辑头文件
    └── SnakeGame.cpp # 游戏核心逻辑实现
```

## 三、环境依赖
1. CMake 3.14 及以上版本
2. C++17 标准编译器（GCC / Clang / MSVC均可）
3. Git（编译时自动下载FTXUI开源库）

## 四、编译与运行步骤
### 1. 创建编译文件夹
```bash
mkdir build
cd build
```

### 2. 生成编译文件
```bash
cmake ..
```

### 3. 编译代码
Windows：
```bash
cmake --build . --config Release
```
Linux / MacOS：
```bash
make -j4
```

### 4. 启动游戏
Windows：
```bash
Release\snake.exe
```
Linux / MacOS：
```bash
./snake
```

## 五、游戏操作说明
- ↑ ↓ ← → 方向键：控制蛇移动方向
- R：游戏结束后重新开始游戏
- Q：关闭退出游戏
