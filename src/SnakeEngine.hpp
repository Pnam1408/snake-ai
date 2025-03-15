#pragma one;

#include <deque>
#include <List>


enum class Direction {
    Up, Down, Left, Right
};

enum class GameState {
    Running, Win, GameOver
};

struct Coordinates
{
    int col;
    int row;
};

class SnakeEngine
{
private:

    bool generateFood();
    bool hitBody(Coordinates pos);
    bool hitWall(Coordinates pos);
    void createSnake();

public:
    std::deque<Coordinates> snakeBody;
    Direction headDirection;
    Coordinates food;
    int score;
    int cols, rows;
    GameState state;

    SnakeEngine(int cols, int rows);

    void newGame();
    void update(Direction input);
};

bool operator == (Coordinates a, Coordinates b);
