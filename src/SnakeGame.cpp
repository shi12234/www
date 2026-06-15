#include "SnakeGame.h"

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

SnakeGame::SnakeGame(int width, int height)
    : width_(width), height_(height), rng_(std::random_device{}()) {
    reset();
}

void SnakeGame::reset() {
    snake_.clear();
    // 初始蛇在画面中央，长度3，默认向右移动
    int start_x = width_ / 2;
    int start_y = height_ / 2;
    snake_.push_back({start_x, start_y});
    snake_.push_back({start_x - 1, start_y});
    snake_.push_back({start_x - 2, start_y});

    direction_ = Direction::Right;
    nextDirection_ = Direction::Right;
    score_ = 0;
    gameOver_ = false;
    generateFood();
}

void SnakeGame::setDirection(Direction dir) {
    // 禁止180度反向移动
    if ((dir == Direction::Up && direction_ == Direction::Down) ||
        (dir == Direction::Down && direction_ == Direction::Up) ||
        (dir == Direction::Left && direction_ == Direction::Right) ||
        (dir == Direction::Right && direction_ == Direction::Left)) {
        return;
    }
    nextDirection_ = dir;
}

void SnakeGame::tick() {
    if (gameOver_) return;
    direction_ = nextDirection_;

    Point new_head = snake_.front();
    switch (direction_) {
        case Direction::Up:    new_head.y--; break;
        case Direction::Down:  new_head.y++; break;
        case Direction::Left:  new_head.x--; break;
        case Direction::Right: new_head.x++; break;
    }

    // 撞墙或撞自身则游戏结束
    if (checkCollision(new_head)) {
        gameOver_ = true;
        return;
    }

    snake_.push_front(new_head);

    // 吃到食物则加分并生成新食物，否则移除尾部
    if (new_head == food_) {
        score_ += 10;
        generateFood();
    } else {
        snake_.pop_back();
    }
}

bool SnakeGame::isGameOver() const {
    return gameOver_;
}

int SnakeGame::getScore() const {
    return score_;
}

const std::deque<Point>& SnakeGame::getSnake() const {
    return snake_;
}

Point SnakeGame::getFood() const {
    return food_;
}

int SnakeGame::getWidth() const {
    return width_;
}

int SnakeGame::getHeight() const {
    return height_;
}

void SnakeGame::generateFood() {
    std::uniform_int_distribution<int> dist_x(0, width_ - 1);
    std::uniform_int_distribution<int> dist_y(0, height_ - 1);
    // 循环直到生成不在蛇身上的食物
    do {
        food_.x = dist_x(rng_);
        food_.y = dist_y(rng_);
    } while (checkCollision(food_));
}

bool SnakeGame::checkCollision(const Point& point) const {
    // 边界碰撞
    if (point.x < 0 || point.x >= width_ || point.y < 0 || point.y >= height_) {
        return true;
    }
    // 蛇身碰撞
    for (const auto& seg : snake_) {
        if (seg == point) return true;
    }
    return false;
}