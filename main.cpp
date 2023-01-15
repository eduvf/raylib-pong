#include "raylib.h"

struct Ball {
  float x, y;
  float speedX, speedY;
  float radius;

  void Draw() { DrawCircle((int)x, (int)y, radius, BLUE); }
};

struct Paddle {
  float x, y;
  float speed;
  float width, height;

  Rectangle GetRect() {
    return Rectangle{x - width / 2, y - height / 2, width, height};
  };

  void Draw() { DrawRectangleRec(GetRect(), RED); }
};

int main() {
  InitWindow(512, 256, "pong");
  SetWindowState(FLAG_VSYNC_HINT);

  const int WIDTH = GetScreenWidth();
  const int HEIGHT = GetScreenHeight();

  Ball ball;
  ball.x = WIDTH / 2.0f;
  ball.y = HEIGHT / 2.0f;
  ball.radius = 3;
  ball.speedX = 100;
  ball.speedY = 100;

  Paddle leftPaddle;
  leftPaddle.x = 20;
  leftPaddle.y = HEIGHT / 2.0f;
  leftPaddle.width = 5;
  leftPaddle.height = 50;
  leftPaddle.speed = 200;

  Paddle rightPaddle;
  rightPaddle.x = WIDTH - 20;
  rightPaddle.y = HEIGHT / 2;
  rightPaddle.width = 5;
  rightPaddle.height = 50;
  rightPaddle.speed = 200;

  const char *winnerText = nullptr;

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

    if (IsKeyDown(KEY_W)) {
      leftPaddle.y -= leftPaddle.speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_S)) {
      leftPaddle.y += leftPaddle.speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_UP)) {
      rightPaddle.y -= rightPaddle.speed * GetFrameTime();
    }
    if (IsKeyDown(KEY_DOWN)) {
      rightPaddle.y += rightPaddle.speed * GetFrameTime();
    }

    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                                leftPaddle.GetRect())) {
      if (ball.speedX < 0) {
        ball.speedX *= -1.1f;
        ball.speedY =
            (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;
      }
    };
    if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                                rightPaddle.GetRect())) {
      if (ball.speedX > 0) {
        ball.speedX *= -1.1f;
        ball.speedY =
            (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * ball.speedX;
      }
    };

    if (ball.x < 0) {
      winnerText = "RIGHT WINS";
    }
    if (ball.x > WIDTH) {
      winnerText = "LEFT WINS";
    }
    if (winnerText && IsKeyPressed(KEY_SPACE)) {
      ball.x = WIDTH / 2.0f;
      ball.y = HEIGHT / 2.0f;
      ball.speedX = 100;
      ball.speedY = 100;
      winnerText = nullptr;
    }

    BeginDrawing();
    ClearBackground(WHITE);

    ball.Draw();
    leftPaddle.Draw();
    rightPaddle.Draw();

    if (winnerText) {
      int textWidth = MeasureText(winnerText, 60);
      DrawText(winnerText, WIDTH / 2 - textWidth / 2, HEIGHT / 2 - 30, 60,
               BLACK);
    }

    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}