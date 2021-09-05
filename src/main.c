#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct Platform {
    Rectangle rect;
    Color color;
} Platform;

int main(void)
{
    // Init
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PLATFORM FIGHTERS!");

    // Create Platforms
    Platform platforms[] = {
        {{144, 560, 512, 160}, DARKGRAY}, // Floor Platform
        {{208, 368, 368, 32}, DARKGRAY}, // Middle Platform
        {{96, 208, 128, 32}, DARKGRAY}, // Top Left Platform
        {{608, 208, 128, 32}, DARKGRAY} // Top Right Platform
    };

    int platformsLength = sizeof(platforms) / sizeof(platforms[0]);

    // Set Target FPS
    SetTargetFPS(60);

    // Main Game Loop
    while (!WindowShouldClose())
    {
        // Update


        // Draw
        BeginDrawing();
            ClearBackground(SKYBLUE);

            for (int i=0; i < platformsLength; i++) {
                DrawRectangleRec(platforms[i].rect, platforms[i].color);
            }

        EndDrawing();
    }

    // De-Init
    CloseWindow();

    return 0;
}