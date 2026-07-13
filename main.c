#include <stdio.h>
#include <raylib.h>
#include <math.h>

#define SCREEN_WIDTH fibonacci(MAX_SQUARE_COUNT)
#define SCREEN_HEIGHT fibonacci(MAX_SQUARE_COUNT - 1)
#define MAX_SQUARE_COUNT 16
#define MAX_POINT_COUNT get_point_count(MAX_SQUARE_COUNT - 1)

typedef struct
{
    float pos_x;
    float pos_y;
    int size;
} Square;

typedef struct
{
    float pos_x;
    float pos_y;
    int rad;
} Point;

typedef struct
{
    float current_phi;
    float points_per_frame;
    int current_point_count;
    int square_index;
} Spiral;

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

void calculate_spiral(Square *squares, Point *points)
{
    float angle = 0;
    int k = 0;
    int square_start_index = 0;
    int current_index = 0;

    float pos_x = squares[0].pos_x;
    float pos_y = squares[0].pos_y;
    int point_rad = 1;

    Vector2 center;
    float step;
    float square_rad;

    for (int j = 0; j < MAX_SQUARE_COUNT; j++)
    {
        // Calculate center positions of quarter circles
        if (j == k)
        {
            center = (Vector2){pos_x + (float)fibonacci(j), pos_y};
        }
        else if (j == 1 + k)
        {
            center = (Vector2){pos_x, pos_y - (float)fibonacci(j)};
        }
        else if (j == 2 + k)
        {
            center = (Vector2){pos_x - (float)fibonacci(j), pos_y};
        }
        else if (j == 3 + k)
        {
            center = (Vector2){pos_x, pos_y + (float)fibonacci(j)};
            k += 4;
        }

        step = (PI / 2) / fibonacci(j);
        square_rad = fibonacci(j);

        // Create spiral points based on the first quarter circle
        for (int i = 0; i < fibonacci(j); i++)
        {
            pos_x = center.x - square_rad * cos(angle); // point moves towards center from left horizontally => subtract cosine
            pos_y = center.y + square_rad * sin(angle); // point moves away from center towards bottom vertically => add sine

            current_index = square_start_index + i;

            points[current_index].pos_x = pos_x;
            points[current_index].pos_y = pos_y;
            points[current_index].rad = point_rad;

            angle += step;
        }

        square_start_index += fibonacci(j);
    }
}

void draw_square_sizes(Square *squares)
{
    int font_size = 10;
    const int k = 3;

    for (int i = 2 * k; i < MAX_SQUARE_COUNT; i++)
    {
        float offset = sqrt(MAX_SQUARE_COUNT - i);

        if (i <= 2 * k)
        {
            offset = sqrt(MAX_SQUARE_COUNT - i);
        }
        else if (i > 2 * k && i <= 3 * k - 1)
        {
            offset += i / 4;
        }
        else if (i > 3 * k - 1 && i <= 4 * k - 1)
        {
            offset += i * 0.7;
        }
        else
        {
            offset += 35;
        }

        float center_x = squares[i].pos_x + squares[i].size / 2 - offset;
        float center_y = squares[i].pos_y + squares[i].size / 2 - offset;

        if (i > 4 * k - 1 && i <= 5 * k - 1)
        {
            center_y += i;
        }

        const char *size_text = TextFormat("%d", squares[i].size);

        if (i == 3 * k)
        {
            font_size += 10;
        }
        else if (i == 4 * k)
        {
            font_size += 30;
        }

        DrawText(size_text, center_x, center_y, font_size, WHITE);
    }
}

int get_point_count(int square_count)
{
    int sum = 0;

    for (int i = 0; i <= square_count; i++)
    {
        sum += fibonacci(i);
    }

    return sum;
}

void draw_spiral(Point *points, Spiral *spiral)
{
    for (int i = 0; i < spiral->current_point_count; i++)
    {
        float pos_x = points[i].pos_x;
        float pos_y = points[i].pos_y;
        int rad = points[i].rad;

        DrawCircle(pos_x, pos_y, rad, BLUE);
    }
}

void animate_spiral(Spiral *spiral)
{
    if (spiral->current_point_count < MAX_POINT_COUNT - spiral->points_per_frame)
    {
        const int n1 = fibonacci(MAX_SQUARE_COUNT - 1);
        const int n2 = fibonacci(MAX_SQUARE_COUNT);
        const float phi = (float)n2 / (float)n1;

        // Multiply points per frame with golden ratio on each square for smooth speed
        if (spiral->current_point_count == get_point_count(spiral->square_index - 1))
        {
            spiral->points_per_frame *= phi;
        }

        spiral->current_point_count += spiral->points_per_frame;
    }
}

void calculate_phi(Square *squares, Spiral *spiral)
{
    // Divide current square size with its predecessor's size
    if (spiral->current_point_count >= get_point_count(spiral->square_index) - spiral->points_per_frame)
    {
        float n1 = squares[spiral->square_index - 1].size;
        float n2 = squares[spiral->square_index].size;

        spiral->current_phi = n2 / n1;

        spiral->square_index++;
    }

    const char *phi_text = TextFormat("phi = ± %f", spiral->current_phi);

    int pos_x = 10;
    int pos_y = 5;
    int font_size = 30;

    DrawText(phi_text, pos_x, pos_y, font_size, WHITE);
}

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Golden Ratio");

    SetTargetFPS(15);

    Square squares[MAX_SQUARE_COUNT];
    Point points[MAX_POINT_COUNT];
    Spiral spiral;

    spiral.points_per_frame = 1;
    spiral.current_point_count = 0;
    spiral.square_index = 1;

    calculate_squares(&squares[0]);
    calculate_spiral(&squares[0], &points[0]);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        draw_squares(&squares[0]);
        draw_square_sizes(&squares[0]);
        draw_spiral(&points[0], &spiral);

        calculate_phi(&squares[0], &spiral);

        EndDrawing();

        animate_spiral(&spiral);
    }

    CloseWindow();

    return 0;
}