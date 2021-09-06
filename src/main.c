#include <stdio.h>
#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define PLAYER_MOVE_SPEED 200.0f
#define GRAVITY 500

typedef enum {
    PLAYER_LEFT = 0, // Uses WSAD and Space
    PLAYER_RIGHT = 1 // Uses Arrow Keys and Enter
} Controls;

typedef enum {
    MOVE_LEFT = 0,
    MOVE_RIGHT = 1,
    JUMP = 2
} Direction;

typedef struct Player {
    Vector2 position;
    Vector2 velocity;
    Controls controls;
    Color color;
} Player;

typedef struct Platform {
    Rectangle rect;
    Color color;
} Platform;

void UpdatePlayer(Player *player, Platform *patforms, int platformsLength, float deltaTime);
void MovePlayer(Player *player, float deltaTime, Direction direction);
void DrawPlayer(Player *player);

int main(void)
{
    // Init
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PLATFORM FIGHTERS!");

    // Create Players
    Player players[2] = {
        {(Vector2){240, 0}, {0}, PLAYER_LEFT, RED}, // Player 1
        {(Vector2){528, 0}, {0}, PLAYER_RIGHT, BLUE} // Player 2
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
        float deltaTime = GetFrameTime();

        for (int i=0; i<playersLength; i++) {
            UpdatePlayer(&players[i], platforms, platformsLength, deltaTime);
        }
        
        // Draw
        BeginDrawing();
            ClearBackground(SKYBLUE);

            // Draw Platforms
            for (int i=0; i < platformsLength; i++) {
                DrawRectangleRec(platforms[i].rect, platforms[i].color);
            }

            // Draw Players
            for (int i=0; i < playersLength; i++) {
                DrawPlayer(&players[i]);
            }

        EndDrawing();
    }

    // De-Init
    CloseWindow();

    return 0;
}

void UpdatePlayer(Player *player, Platform *platforms, int platformsLength, float deltaTime)
{
    // Left Player (Player 1)
    if (player->controls == PLAYER_LEFT) {
        if (IsKeyDown(KEY_A)) MovePlayer(player, deltaTime, MOVE_LEFT);
        if (IsKeyDown(KEY_D)) MovePlayer(player, deltaTime, MOVE_RIGHT);
    }
    // Right Player (Player 2)
    else if (player->controls == PLAYER_RIGHT) {
        if (IsKeyDown(KEY_LEFT)) MovePlayer(player, deltaTime, MOVE_LEFT);
        if (IsKeyDown(KEY_RIGHT)) MovePlayer(player, deltaTime, MOVE_RIGHT);
    }

    // Check Collisions
    int hitObstacle = 0;
    for (int i=0; i<platformsLength; i++)
    {
        Platform *pi = platforms + i;
        Vector2 *p = &(player->position);
        
        if (pi->rect.x <= p->x &&
            pi->rect.x + pi->rect.width >= p->x &&
            pi->rect.y >= p->y &&
            pi->rect.y < p->y + player->velocity.y * deltaTime
        ) {
            hitObstacle = 1;
            player->velocity = (Vector2){0, 0};
            p->y = pi->rect.y;
        }
    }

    if (!hitObstacle) {
        // Apply Gravity
        player->position.y += player->velocity.y * deltaTime;
        player->velocity.y += GRAVITY * deltaTime;
    }   
}

void MovePlayer(Player *player, float deltaTime, Direction direction)
{
    if (direction == MOVE_LEFT) {player->position.x -= PLAYER_MOVE_SPEED * deltaTime;}
    if (direction == MOVE_RIGHT) {player->position.x += PLAYER_MOVE_SPEED * deltaTime;}
}

void DrawPlayer(Player *player) 
{
    Rectangle playerRect = {player->position.x - 64, player->position.y - 116, 64, 128};
    DrawRectangleRec(playerRect, player->color);
}
