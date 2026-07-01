#include <stdio.h>
#include <raylib.h>

#define MAX_SQUARE_COUNT 16
#define SCREEN_WIDTH fibonacci(MAX_SQUARE_COUNT)
#define SCREEN_HEIGHT fibonacci(MAX_SQUARE_COUNT - 1)

typedef struct
{
    float pos_x;
    float pos_y;
    int size;
} Square;

int fibonacci(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}

void calculate_squares(Square *squares)
{
    int k = 0;
    int l = 0;
    int m = 0;
    int o = 0;

    int x_offset = 90;
    int y_offset = 56;

    for (int n = 0; n < MAX_SQUARE_COUNT; n++)
    {
        squares[n].size = fibonacci(n);

        if (n == 0)
        {
            squares[n].pos_x = SCREEN_WIDTH - SCREEN_WIDTH / 3 + x_offset;
            squares[n].pos_y = SCREEN_HEIGHT - SCREEN_HEIGHT / 3 + y_offset;
        }
        else if (n == 1)
        {
            squares[n].pos_x = squares[n - 1].pos_x + squares[n].size;
            squares[n].pos_y = squares[n - 1].pos_y;
        }
        else if (n == 2 + k)
        {
            squares[n].pos_x = squares[n - 2].pos_x;
            squares[n].pos_y = squares[n - 1].pos_y - squares[n].size;
            k += 4;
        }
        else if (n == 3 + l)
        {
            squares[n].pos_x = squares[n - 1].pos_x - squares[n].size;
            squares[n].pos_y = squares[n - 1].pos_y;
            l += 4;
        }
        else if (n == 4 + m)
        {
            squares[n].pos_x = squares[n - 1].pos_x;
            squares[n].pos_y = squares[n - 1].pos_y + squares[n - 1].size;
            m += 4;
        }
        else if (n == 5 + o)
        {
            squares[n].pos_x = squares[n - 1].pos_x + squares[n - 1].size;
            squares[n].pos_y = squares[n - 2].pos_y;
            o += 4;
        }
    }
}

void draw_squares(Square *squares)
{
    for (int n = 0; n < MAX_SQUARE_COUNT; n++)
    {
        float pos_x = squares[n].pos_x;
        float pos_y = squares[n].pos_y;
        int size = squares[n].size;

        DrawRectangleLines(pos_x, pos_y, size, size, GOLD);
    }
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Golden Ratio");

    SetTargetFPS(15);

    Square squares[MAX_SQUARE_COUNT];

    calculate_squares(&squares[0]);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        draw_squares(&squares[0]);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}