#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(void)
{
    // Init
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PLATFORM FIGHTERS!");

    SetTargetFPS(60);

    // Main Game Loop
    while (!WindowShouldClose())
    {
        // Update


        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Hello platform fighters!", 100, 100, 28, WHITE);
        EndDrawing();
    }

    // De-Init
    CloseWindow();

    return 0;
}