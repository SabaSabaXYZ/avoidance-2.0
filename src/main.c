#include <raylib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define FONT_SIZE 20

typedef enum GameScreen {
  TITLE = 0,
  GAMEPLAY,
  HELP
} GameScreen;

void DrawTextCentre(const char *text, int posY, Color color) {
  int textWidth = MeasureText(text, FONT_SIZE);
  DrawText(text, (SCREEN_WIDTH - textWidth) / 2, posY, FONT_SIZE, color);
}

void DrawTitle() {
  int startHeight = SCREEN_HEIGHT / 4;
  DrawTextCentre("==Avoidance==", startHeight, WHITE);
  DrawTextCentre("Move: W/A/S/D", startHeight + FONT_SIZE * 2, WHITE);
  DrawTextCentre("Help: H", startHeight + FONT_SIZE * 4, WHITE);
  DrawTextCentre("Play: P", startHeight + FONT_SIZE * 6, WHITE);
  DrawTextCentre("Quit: Q", startHeight + FONT_SIZE * 8, WHITE);
}

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Avoidance");
  SetTargetFPS(60);
  ToggleFullscreen();
  GameScreen gameScreen = TITLE;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    switch (gameScreen) {
      case TITLE:
        DrawTitle();
        break;
      default:
        break;
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
