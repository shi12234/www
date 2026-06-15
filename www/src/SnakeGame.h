#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <deque>
#include <random>

// 移动方向枚举
enum class Direction {
    Up,
    Down,
    Left,
    Right
};

// 坐标点结构体
struct Point {
    int x;
    int y;
    bool operator==(const Point& other) const;
};

// 贪吃蛇游戏核心类
class SnakeGame {
public:
    SnakeGame(int width, int height);

    void reset();                // 重置游戏状态
    void setDirection(Direction dir); // 设置移动方向（防反向）
    void tick();                 // 执行一次游戏帧更新
    bool isGameOver() const;     // 获取游戏结束状态
    int getScore() const;        // 获取当前分数
    const std::deque<Point>& getSnake() const; // 获取蛇身坐标
    Point getFood() const;       // 获取食物坐标
    int getWidth() const;        // 获取游戏区域宽度
    int getHeight() const;       // 获取游戏区域高度

private:
    int width_;
    int height_;
    std::deque<Point> snake_;    // 蛇身队列（头部在前）
    Direction direction_;        // 当前移动方向
    Direction nextDirection_;    // 下一帧生效的方向
    Point food_;                 // 食物坐标
    int score_;                  // 当前分数
    bool gameOver_;              // 游戏结束标志
    std::mt19937 rng_;           // 随机数生成器

    void generateFood();         // 随机生成食物（避开蛇身）
    bool checkCollision(const Point& point) const; // 碰撞检测
};

#endif // SNAKE_GAME_H