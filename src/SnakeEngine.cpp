#include "SnakeEngine.hpp"
#include "Random.hpp"
#include "config.hpp"
#include <list>
#include <iostream>

SnakeEngine::SnakeEngine(int rows, int cols) : cols(cols), rows(rows) {}

void SnakeEngine::createSnake() {
    if (!snakeBody.empty()) {
        snakeBody.clear();
    }
    // initialize snake
    Coordinates startPos = {(int)std::floor(Random::rf()*(cols-4)) + 2, (int)std::floor(Random::rf()*(rows-4)) + 2};
    snakeBody.push_front(startPos);

    int i = (int) std::floor(Random::rf() * 4);
    switch (i)
    {
    case 0:
        headDirection = Direction::Up;
        snakeBody.push_front({startPos.col, startPos.row - 1});
        snakeBody.push_front({startPos.col, startPos.row - 2});
        break;
    case 1:
        headDirection = Direction::Down;
        snakeBody.push_front({startPos.col, startPos.row + 1});
        snakeBody.push_front({startPos.col, startPos.row + 2});
        break;
    case 2:
        headDirection = Direction::Left;
        snakeBody.push_front({startPos.col - 1, startPos.row});
        snakeBody.push_front({startPos.col - 2, startPos.row});
        break;
    case 3:
        headDirection = Direction::Right;
        snakeBody.push_front({startPos.col + 1, startPos.row});
        snakeBody.push_front({startPos.col + 2, startPos.row});
        break;
    default:
        break;
    }
}

bool SnakeEngine::generateFood() {
    std::list<Coordinates> emptySpace;
    for (int i = 0; i < cf::NumCols; i++) {
        for (int j = 0; j < cf::NumRows; j++) {
            if (!hitBody({i, j})) {
                emptySpace.push_front({i, j});
            }
        }
    }
    if (emptySpace.empty()) {
        return false;
    } else {
        food = *select_randomly(emptySpace.begin(), emptySpace.end());
        return true;
    }
}

void SnakeEngine::update(Direction input) {
    Coordinates nextPos;
    switch (input)
    {
    case Direction::Up:
        if (headDirection == Direction::Down) {
            return;
        }
        nextPos = {snakeBody.front().col, snakeBody.front().row - 1};
        break;
    case Direction::Down:
        if (headDirection == Direction::Up) {
            return;
        }
        nextPos = {snakeBody.front().col, snakeBody.front().row + 1};
        break;
    case Direction::Left:
        if (headDirection == Direction::Right) {
            return;
        }
        nextPos = {snakeBody.front().col - 1, snakeBody.front().row};
        break;
    case Direction::Right:
        if (headDirection == Direction::Left) {
            return;
        }
        nextPos = {snakeBody.front().col + 1, snakeBody.front().row};
        break;
    default:
        break;
    }
    
    if (hitWall(nextPos) || (hitBody(nextPos) && !(nextPos == snakeBody.back()))) {
        state = GameState::GameOver;
    }
    else if (nextPos == food) {
        snakeBody.push_front(nextPos);
        headDirection = input;
        if(!generateFood()) {
            state = GameState::Win;
        }
        score++;
    }
    else {
        snakeBody.push_front(nextPos);
        snakeBody.pop_back();
        headDirection = input;
    }
}

bool SnakeEngine::hitBody(Coordinates pos) {
    for (Coordinates bodyPart : snakeBody) {
        if (pos == bodyPart) {
                return true;
        }
    }
    return false;
}

bool SnakeEngine::hitWall(Coordinates pos) {
    if (pos.col < 0 || pos.col >= cols || pos.row < 0 || pos.row >= rows) {
        return true;
    } else {
        return false;
    }
}

void SnakeEngine::newGame() {
    score = 3;
    state = GameState::Running;
    createSnake();
    generateFood();
}

bool operator == (Coordinates a, Coordinates b) {
    if ((a.col == b.col) && (a.row == b.row)) {
        return true;
    } else {
        return false;
    }
}