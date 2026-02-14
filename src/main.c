#include "game.h"
#include "keys.h"
#include "render.h"
#include "types.h"
#include <raylib.h>
#include <raymath.h>
#include <time.h>

static void InitializeGame(GameState *state) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(800, 800, "Avoidance");
  SetTargetFPS(60);
  int monitor = GetCurrentMonitor();
  state->screenWidth = GetMonitorWidth(monitor);
  state->screenHeight = GetMonitorHeight(monitor);
  SetWindowSize(state->screenWidth, state->screenHeight);
  state->renderTexture = LoadRenderTexture(state->screenWidth, state->screenHeight);
  SetTextureFilter(state->renderTexture.texture, TEXTURE_FILTER_BILINEAR);
  state->gameBoundary = (Rectangle) { GAME_LEFT, GAME_TOP, state->screenWidth - GAME_LEFT, state->screenHeight - GAME_TOP };
  state->screen = TITLE;
  state->score = 0;
  const Font font = GetFontDefault();
  state->characterDimensions = MeasureTextEx(font, PLAYER_CHARACTER, FONT_SIZE, 0.0f);
  ToggleFullscreen();
  HideCursor();
}

static void DestroyGame(GameState *state) {
  CloseWindow();
}

int main(void) {
  SetRandomSeed(time(NULL));
  GameState state;
  InitializeGame(&state);
  while (!WindowShouldClose()) {
    HandleKeyPress(&state);
    HandleDraw(state);
    UpdatePositions(&state);
  }
  DestroyGame(&state);
  return 0;
}
