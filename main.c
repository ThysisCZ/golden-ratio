#include <stdio.h>
#include <raylib.h>
#include <math.h>

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
    int x_offset = 90;
    int y_offset = 56;
    int k = 0;

    for (int n = 0; n < MAX_SQUARE_COUNT; n++)
    {
        squares[n].size = fibonacci(n);

        // Calculate upper left corner positions of squares
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
        }
        else if (n == 3 + k)
        {
            squares[n].pos_x = squares[n - 1].pos_x - squares[n].size;
            squares[n].pos_y = squares[n - 1].pos_y;
        }
        else if (n == 4 + k)
        {
            squares[n].pos_x = squares[n - 1].pos_x;
            squares[n].pos_y = squares[n - 1].pos_y + squares[n - 1].size;
        }
        else if (n == 5 + k)
        {
            squares[n].pos_x = squares[n - 1].pos_x + squares[n - 1].size;
            squares[n].pos_y = squares[n - 2].pos_y;
            k += 4;
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

void draw_spiral()
{
    float angle = 0;
    int k = 0;

    float pos_x = 0;
    float pos_y = fibonacci(MAX_SQUARE_COUNT - 1);

    Vector2 center;
    float step;
    float rad;

    for (int j = MAX_SQUARE_COUNT - 1; j >= 0; j--)
    {
        // Calculate center positions of quarter circles
        if (j == 15 - k)
        {
            center = (Vector2){pos_x + (float)fibonacci(j), pos_y};
        }
        else if (j == 14 - k)
        {
            center = (Vector2){pos_x, pos_y + (float)fibonacci(j)};
        }
        else if (j == 13 - k)
        {
            center = (Vector2){pos_x - (float)fibonacci(j), pos_y};
        }
        else if (j == 12 - k)
        {
            center = (Vector2){pos_x, pos_y - (float)fibonacci(j)};
            k += 4;
        }

        step = (PI / 2) / fibonacci(j);
        rad = fibonacci(j);

        for (int i = 0; i < fibonacci(j); i++)
        {
            pos_x = center.x - rad * cos(angle);
            pos_y = center.y - rad * sin(angle);

            DrawCircle(pos_x, pos_y, 1, BLUE);
            angle += step;
        }
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
        draw_spiral();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}