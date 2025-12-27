#include <bits/stdc++.h>
using namespace std;

// Worker Bee by Dave Buckingham in 1972
bool board[11][16] = {
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
    {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
};

void print_board()
{
    // frame rendering function
    system("clear");
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            // ⬛ ⬜
            cout << (board[i][j] ? "⬜" : "⬛");
        }
        cout << endl;
    }
}

unsigned short int count_neighbours(unsigned short int x, unsigned short int y)
{
    unsigned short int count = 0;

    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0)
                continue;

            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < 11 && ny >= 0 && ny < 16) // checking for out of bound checks
            {
                if (board[nx][ny] == 1)
                    count++;
            }
        }
    }

    return count;
}

void calculate_next_frame()
{
    // using a second board so each frame is isolated and so the effect of one cell doesnt effect the others
    bool next_board[11][16] = {0};

    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            unsigned short int count = count_neighbours(i, j);
            if (board[i][j])
            {
                if (count == 2 || count == 3)
                    next_board[i][j] = 1;
                else
                    next_board[i][j] = 0;
            }
            else
            {
                if (count == 3)
                    next_board[i][j] = 1;
                else
                    next_board[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 16; j++)
            board[i][j] = next_board[i][j];
}

int main()
{
    while (true)
    {
        print_board();
        calculate_next_frame();
        // cin.get();
        this_thread::sleep_for(chrono::milliseconds(300)); // delaying for 0.3 seconds for each frame
    }
}
