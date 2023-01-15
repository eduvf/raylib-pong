#include "raylib.h"

struct Ball {
  float x, y;
  float speedX, speedY;
  float radius;

  void Draw() { DrawCircle((int)x, (int)y, radius, BLUE); }
};

int main() {
  InitWindow(512, 256, "pong");
  SetWindowState(FLAG_VSYNC_HINT);

  const int WIDTH = GetScreenWidth();
  const int HEIGHT = GetScreenHeight();

  Ball ball;
  ball.x = WIDTH / 2.0f;
  ball.y = WIDTH / 2.0f;
  ball.radius = 3;
  ball.speedX = 100;
  ball.speedY = 100;

  while (!WindowShouldClose()) {
    ball.x += ball.speedX * GetFrameTime();
    ball.y += ball.speedY * GetFrameTime();

    if (ball.y < 0) {
      ball.y = 0;
      ball.speedY *= -1;
    } else if (ball.y > HEIGHT) {
      ball.y = HEIGHT;
      ball.speedY *= -1;
    }

    BeginDrawing();
    ClearBackground(WHITE);

    ball.Draw();
    DrawRectangle(20, HEIGHT / 2 - 25, 2, 50, RED);
    DrawRectangle(WIDTH - 20 - 2, HEIGHT / 2 - 25, 2, 50, RED);

    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}