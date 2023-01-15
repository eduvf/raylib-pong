#include "raylib.h"

int main() {
  InitWindow(256, 256, "pong");
  SetWindowState(FLAG_VSYNC_HINT);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(WHITE);

    DrawFPS(0, 0);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}