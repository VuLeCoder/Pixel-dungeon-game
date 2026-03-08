#include "raylib.h"

int main()
{
    InitWindow(800, 600, "raylib + cmake");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello CMake!", 300, 280, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
}