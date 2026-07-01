#include <stdio.h>
#include <raylib.h>

#define SCREEN_WIDTH 987
#define SCREEN_HEIGHT 610
#define MAX_SQUARE_COUNT 15

typedef struct
{
    float pos_x;
    float pos_y;
    int size;
} Square;

int fibonacci(int n)
{
    if (n == 1 || n == 2)
    {
        return 1;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Golden Ratio");

    SetTargetFPS(15);

    Square squares[MAX_SQUARE_COUNT];

    for (int n = 1; n <= MAX_SQUARE_COUNT; n++)
    {
        squares[n].size = fibonacci(n);
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}