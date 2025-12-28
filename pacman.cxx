#include <ncurses.h>
#include <bits/stdc++.h>

using namespace std;

constexpr int FPS = 30;
constexpr int frameDelay = 1000 / FPS;

class Map
{
public:
    bool is_wall(int y, int x) const;
    bool is_point(int y, int x) const;
    void eat_point(int y, int x);

    void render_map() const;

private:
    vector<string> gameMap = {
        "############################",
        "#............##............#",
        "#.####.#####.##.#####.####.#",
        "#.####.#####.##.#####.####.#",
        "#..........................#",
        "#.####.##.########.##.####.#",
        "#......##....##....##......#",
        "######.##### ## #####.######",
        "######.##### ## #####.######",
        "#............##............#",
        "#.####.#####.##.#####.####.#",
        "#.####.#####.##.#####.####.#",
        "#..........................#",
        "############################"};
};

bool Map::is_wall(int y, int x) const
{
    return gameMap[y][x] == '#';
}

bool Map::is_point(int y, int x) const
{
    return gameMap[y][x] == '.';
}

void Map::eat_point(int y, int x)
{
    if (is_point(y, x))
        gameMap[y][x] = ' ';
}

void Map::render_map() const
{
    for (int y = 0; y < gameMap.size(); ++y)
    {
        for (int x = 0; x < gameMap[y].size(); ++x)
        {
            if (gameMap[y][x] == '#')
                mvprintw(y, x, "#");
            // mvprintw(y, x, "█");
            else if (gameMap[y][x] == '.')
                mvaddch(y, x, '.');
            else
                mvaddch(y, x, ' ');
        }
    }
}

class Entity
{
public:
    float speed = 0.1;
    char sprite = 'E';
    float y = 1;
    float x = 1;
    char moving_direction = 's';
    bool is_moving = false;

    void render_entity() const;
    void move();
};

void Entity::render_entity() const
{
    mvaddch(y, x, sprite);
}

void Entity::move()
{
    switch (moving_direction)
    {
    case 'w':
        y -= speed / 2;
        break;
    case 'a':
        x -= speed;
        break;
    case 's':
        y += speed / 2;
        break;
    case 'd':
        x += speed;
        break;
    }
}

class Player : public Entity
{
public:
};

class Game
{
public:
    void init();
    void run();
    void exit();

private:
    bool running = true;
    unsigned short int score = 0;
    Map m;
    Player p;
    void render() const;
    void update();
    void handle_input();
    void handle_movements();
    void handle_collisions();

    bool can_entity_move(Entity e) const;
};

void Game::init()
{
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

void Game::run()
{
    while (running)
    {
        update();
        render();
        refresh();
        napms(frameDelay);
    }
}

void Game::handle_input()
{
    int ch = getch();

    if (ch != ERR)
    {
        if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd')
        {
            p.moving_direction = ch;
            p.is_moving = true;
        }
        else if (ch == 'q')
            running = false;
    }
}

bool Game::can_entity_move(Entity e) const
{
    int x_offset = 0;
    int y_offset = 0;
    switch (e.moving_direction)
    {
    case 'w':
        y_offset -= 1;
        break;
    case 'a':
        x_offset -= 1;
        break;
    case 's':
        y_offset += 1;
        break;
    case 'd':
        x_offset += 1;
        break;
    }
    return !m.is_wall(p.y + y_offset, p.x + x_offset);
}

void Game::handle_movements()
{
    if (can_entity_move(p))
        p.move();
    else
        p.is_moving = false;
}

void Game::handle_collisions()
{
    if (m.is_point(p.y, p.x))
    {
        m.eat_point(p.y, p.x);
        score++;
    }
}

void Game::update()
{
    handle_input();
    handle_movements();
    handle_collisions();
}

void Game::render() const
{
    m.render_map();
    p.render_entity();
    mvaddstr(14, 0, "Score : ");
    mvaddstr(14, 8, to_string(score).c_str());
}

void Game::exit()
{
    endwin();
}

int main()
{
    Game g;
    g.init();
    g.run();
    g.exit();
}