#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct Player {
    Rectangle rect;
    Color color;
} Player;

typedef struct Platform {
    Rectangle rect;
    Color color;
} Platform;

int main(void)
{
    // Init
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PLATFORM FIGHTERS!");

    // Create Players
    Player players[2] = {
        {{208, 440, 64, 128}, RED}, // Player 1
        {{528, 440, 64, 128}, BLUE} // Player 2
    };

    int playersLength = sizeof(players) / sizeof(players[0]);

    // Create Platforms
    Platform platforms[] = {
        {{144, 560, 512, 160}, DARKGRAY}, // Floor Platform
        {{208, 320, 368, 32}, DARKGRAY}, // Middle Platform
        {{96, 144, 128, 32}, DARKGRAY}, // Top Left Platform
        {{608, 144, 128, 32}, DARKGRAY} // Top Right Platform
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

            // Draw Platforms
            for (int i=0; i < platformsLength; i++) {
                DrawRectangleRec(platforms[i].rect, platforms[i].color);
            }

            // Draw Players
            for (int i=0; i < playersLength; i++) {
                DrawRectangleRec(players[i].rect, players[i].color);
            }

        EndDrawing();
    }

    // De-Init
    CloseWindow();

    return 0;
}