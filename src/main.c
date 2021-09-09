#include <stdio.h>
#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define PLAYER_MOVE_SPEED 300
#define PLAYER_JUMP_SPEED 500
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
    int width;
    int height;
    float velocity;
    Controls controls;
    Color color;
    int jump;
} Player;

typedef struct Platform {
    Rectangle rect;
    Color color;
} Platform;

void UpdatePlayer(Player *player, Platform *patforms, int platformsLength, float deltaTime);
bool CheckPlatformCollision(Player *player, Platform *patforms, int platformsLength, float deltaTime);
void MovePlayer(Player *player, float deltaTime, Direction direction);
void DrawPlayer(Player *player);

int main(void)
{
    // Init
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PLATFORM FIGHTERS!");

    // Create Players
    Player players[2] = {
        {(Vector2){240, 500}, 64, 128, 0, PLAYER_LEFT, RED, 0}, // Player 1
        {(Vector2){528, 500}, 64, 128, 0, PLAYER_RIGHT, BLUE, 0} // Player 2
    };

    int playersLength = sizeof(players) / sizeof(players[0]);

    // Create Platforms
    Platform platforms[4] = {
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

        for (int i = 0; i < playersLength; i++) {
            UpdatePlayer(&players[i], platforms, platformsLength, deltaTime);
        }
        
        // Draw
        BeginDrawing();
            ClearBackground(SKYBLUE);

            // Draw Platforms
            for (int i = 0; i < platformsLength; i++) {
                DrawRectangleRec(platforms[i].rect, platforms[i].color);
            }

            // Draw Players
            for (int i = 0; i < playersLength; i++) {
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
        if (IsKeyPressed(KEY_W)) MovePlayer(player, deltaTime, JUMP);
    }
    // Right Player (Player 2)
    else if (player->controls == PLAYER_RIGHT) {
        if (IsKeyDown(KEY_LEFT)) MovePlayer(player, deltaTime, MOVE_LEFT);
        if (IsKeyDown(KEY_RIGHT)) MovePlayer(player, deltaTime, MOVE_RIGHT);
        if (IsKeyPressed(KEY_UP)) MovePlayer(player, deltaTime, JUMP);
    }

    // Check collisions with platforms
    if (CheckPlatformCollision(player, platforms, platformsLength, deltaTime)) {
        player->jump = 0;
    }
    else {
        // Apply Gravity
        player->position.y += player->velocity * deltaTime;
        player->velocity += GRAVITY * deltaTime;
    }
}

bool CheckPlatformCollision(Player *player, Platform *platforms, int platformsLength, float deltaTime)
{
    bool collision = false;    
    Vector2 *p = &(player->position);
    for (int i = 0; i < platformsLength; i++) {
        Platform *pi = platforms + i;
        if (
            pi->rect.x <= p->x &&
            pi->rect.x + pi->rect.width + player->width >= p->x &&  
            pi->rect.y >= p->y &&
            pi->rect.y < p->y + player->velocity * deltaTime
        ) {
            // Player on Platform
            collision = true;
            player->position.y = platforms[i].rect.y;
            player->velocity = 0;
        }
    }
    return collision;
}

void MovePlayer(Player *player, float deltaTime, Direction direction)
{
    if (direction == MOVE_LEFT) {player->position.x -= PLAYER_MOVE_SPEED * deltaTime;}
    if (direction == MOVE_RIGHT) {player->position.x += PLAYER_MOVE_SPEED * deltaTime;}
    if (direction == JUMP && player->jump <= 1) {
        player->velocity = -PLAYER_JUMP_SPEED;
        player->jump++;
    }
}

void DrawPlayer(Player *player) 
{
    Rectangle playerRect = {
        player->position.x - player->width,
        player->position.y - player->height,
        player->width,
        player->height};
    DrawRectangleRec(playerRect, player->color);
}
