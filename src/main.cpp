#include "SnakeGame.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <thread>
#include <chrono>
#include <functional>

using namespace ftxui;

// 构建游戏界面组件
Component GameComponent(SnakeGame& game, std::function<void()> exit_fn) {
    auto renderer = Renderer([&] {
        Elements grid_lines;
        // 逐行渲染游戏网格
        for (int y = 0; y < game.getHeight(); ++y) {
            Elements row;
            for (int x = 0; x < game.getWidth(); ++x) {
                Point curr{x, y};
                if (curr == game.getFood()) {
                    row.push_back(text("●") | color(Color::Red));
                } else {
                    bool is_snake = false;
                    for (const auto& seg : game.getSnake()) {
                        if (seg == curr) {
                            is_snake = true;
                            break;
                        }
                    }
                    row.push_back(is_snake ? text("■") | color(Color::Green) : text(" "));
                }
            }
            grid_lines.push_back(hbox(std::move(row)));
        }

        auto game_area = vbox(std::move(grid_lines)) | border;
        auto status_bar = hbox({
            text("分数: " + std::to_string(game.getScore())),
            separator(),
            text(game.isGameOver() ? "游戏结束 | 按 R 重新开始" : "方向键控制 | 按 Q 退出")
        }) | center;

        return vbox({
            text("贪吃蛇游戏") | bold | center,
            separator(),
            game_area | center,
            separator(),
            status_bar
        });
    });

    // 捕获键盘事件
    return CatchEvent(renderer, [&, exit_fn](Event event) {
        // 退出游戏
        if (event == Event::Character('q') || event == Event::Character('Q')) {
            exit_fn();
            return true;
        }
        // 游戏结束时按R重开
        if (game.isGameOver()) {
            if (event == Event::Character('r') || event == Event::Character('R')) {
                game.reset();
                return true;
            }
            return false;
        }
        // 方向控制
        if (event == Event::ArrowUp) {
            game.setDirection(Direction::Up);
            return true;
        } else if (event == Event::ArrowDown) {
            game.setDirection(Direction::Down);
            return true;
        } else if (event == Event::ArrowLeft) {
            game.setDirection(Direction::Left);
            return true;
        } else if (event == Event::ArrowRight) {
            game.setDirection(Direction::Right);
            return true;
        }
        return false;
    });
}

int main() {
    const int GAME_WIDTH = 30;
    const int GAME_HEIGHT = 20;
    SnakeGame game(GAME_WIDTH, GAME_HEIGHT);

    auto screen = ScreenInteractive::FitComponent();
    auto exit_fn = screen.ExitLoopClosure();
    auto component = GameComponent(game, exit_fn);

    // 独立线程驱动游戏帧更新
    std::thread game_thread([&] {
        while (!screen.HasQuitted()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
            if (!game.isGameOver()) {
                game.tick();
            }
            screen.PostEvent(Event::Custom); // 触发界面重绘
        }
    });

    screen.Loop(component);
    game_thread.join();
    return 0;
}
