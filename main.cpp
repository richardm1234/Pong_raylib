#include "raylib.h"
#include <iostream>
#include <math.h>

struct Ball {
    Vector2 pos;
    Vector2 velocity;
    float radius;
};

struct Player {
    float x,y,w,h;
    float velocity;
    int score;
};

#define velX -5.0f
#define velY 1.0f
void movePlayer(Player& board, int key) {
    
    if (key == KEY_UP) {
        if (board.y > 0) {
            board.y -= board.velocity;
        }         
    } else if (key == KEY_DOWN) {
        if (board.y + board.h < GetScreenHeight()) {
            board.y += board.velocity;
        } 
    }
}

void moveBot(Player& bot, Ball& b) {
    
    if (bot.y <= 0 || bot.y + bot.h >= GetScreenHeight()) {
        bot.velocity = -bot.velocity;
    }
    float timeNeeded = (bot.x - b.pos.x) / b.velocity.x;
    float predY = b.pos.y + b.velocity.y * timeNeeded;
    
    float center = bot.y + bot.h / 2.0f;
    if (center == predY) {
        bot.velocity = 0;
    } else if (center > predY) {
        bot.y -= bot.velocity;
    } else {
        bot.y += bot.velocity;
    }
    
}

void score(Ball& b, Player& p) {
    p.score++;
    b.pos.x = GetScreenWidth()/2;
    b.pos.y = GetScreenHeight()/2;
}

void changeDirection(Ball& b, float center) {
    float dirY;
    float speed = fabsf(b.velocity.y);
    
    if (b.velocity.y > 0) {
        if (b.pos.y <= center) {
            b.velocity.y = speed;
        } else {
            b.velocity.y = -speed;
        }
    } else if (b.velocity.y < 0) {
            if (b.pos.y <= center) {
                b.velocity.y = -speed;
            } else {
                b.velocity.y = speed;
            }
    } else {
        b.velocity.y = 0;
    }

    b.velocity.x = -b.velocity.x;
}

void moveBall(Ball& b, Player& p1, Player& p2) {
    float centerP1 = p1.y + p1.h / 2.0f;
    float centerP2 = p2.y + p2.h / 2.0f;
    float speed = fabsf(b.velocity.y);

    if (b.pos.y - b.radius <= 0 || b.pos.y + b.radius >= GetScreenHeight()) {
        b.velocity.y = -b.velocity.y;
    } else if (b.velocity.x < 0) {
        if (b.pos.x - b.radius <= 0) {
            score(b, p2);
            return;
        }
        if (b.pos.x - b.radius <= p1.x + p1.w && b.pos.y <= p1.y + p1.h && b.pos.y >= p1.y) {
            changeDirection(b, centerP1);
        }
    } else {
        if (b.pos.x + b.radius >= GetScreenWidth()) {
            score(b, p1);
            return;
        }
        if (b.pos.x + b.radius >= p2.x && b.pos.y <= p2.y + p2.h && b.pos.y >= p2.y) {
            changeDirection(b, centerP2);
        }
    }
    b.pos.x += b.velocity.x;
    b.pos.y += b.velocity.y;
}

int main() {
    const int W = 800, H = 600;
    InitWindow(W, H, "Pong Game");
    SetTargetFPS(60);

    Vector2 ballPos = {W/2, H/4};
    Vector2 ballVel = {-5.0f, 1.0f}; 
    float radius = 10.0f;
    Ball ball = {ballPos, ballVel, radius};

    float playerVel = 5.0f;
    Player p1 = {10, H/2, 10, 50, playerVel, 0};
    Player p2 = {W - 10, H/2, 10, 50, playerVel, 0};

    while (!WindowShouldClose()) {

        if (IsKeyDown(KEY_UP)) movePlayer(p1, KEY_UP);
        else if (IsKeyDown(KEY_DOWN)) movePlayer(p1, KEY_DOWN);

        moveBot(p2, ball);
        moveBall(ball, p1, p2);

        BeginDrawing();
            ClearBackground(BLACK);

            DrawCircleV(ball.pos, radius, WHITE);
            DrawRectangle(p1.x, p1.y, p1.w, p1.h, WHITE);
            DrawCircleV({p1.x, p1.y}, 5.0f, RED);
            DrawRectangle(p2.x, p2.y, p2.w, p2.h, WHITE);
            DrawText("Pong Game", W/2 - 50, 25, 20, WHITE);
            DrawText(TextFormat("%d %d", p1.score, p2.score), W/2 - 25, 50, 20, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}