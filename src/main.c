#include "game.h"
#include "keys.h"
#include "render.h"
#include "types.h"
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <time.h>

static Theme defaultTheme = {
  .backgroundColour = BLACK,
  .foregroundColour = WHITE,
  .borderColour = RED,
  .boxColour = GREEN,
  .playerColour = SKYBLUE,
  .enemyColour = PINK
};

static Theme lightTheme = {
  .backgroundColour = LIGHTGRAY,
  .foregroundColour = BLACK,
  .borderColour = DARKBROWN,
  .boxColour = DARKGREEN,
  .playerColour = DARKBLUE,
  .enemyColour = MAROON
};

static Theme greyTheme = {
  .backgroundColour = DARKGRAY,
  .foregroundColour = RAYWHITE,
  .borderColour = BEIGE,
  .boxColour = GREEN,
  .playerColour = SKYBLUE,
  .enemyColour = MAGENTA
};

static Theme goldTheme = {
  .backgroundColour = DARKBROWN,
  .foregroundColour = GOLD,
  .borderColour = YELLOW,
  .boxColour = YELLOW,
  .playerColour = PURPLE,
  .enemyColour = BEIGE
};

static Theme purpleTheme = {
  .backgroundColour = DARKPURPLE,
  .foregroundColour = YELLOW,
  .borderColour = RED,
  .boxColour = GREEN,
  .playerColour = SKYBLUE,
  .enemyColour = PINK
};

static Theme greenTheme = {
  .backgroundColour = DARKGREEN,
  .foregroundColour = LIGHTGRAY,
  .borderColour = GOLD,
  .boxColour = GREEN,
  .playerColour = SKYBLUE,
  .enemyColour = PINK
};

static void InitializeThemes(GameState *state) {
  state->selectedTheme = 0;
  state->theme[0] = defaultTheme;
  state->theme[1] = lightTheme;
  state->theme[2] = greyTheme;
  state->theme[3] = goldTheme;
  state->theme[4] = purpleTheme;
  state->theme[5] = greenTheme;
}

static void InitializeGame(GameState *state) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(800, 800, "Avoidance");
  SetTargetFPS(60);
  int monitor = GetCurrentMonitor();
  state->screenWidth = GetMonitorWidth(monitor);
  state->screenHeight = GetMonitorHeight(monitor);
  SetWindowSize(state->screenWidth, state->screenHeight);
  float scale = fminf((float) state->screenWidth / 1920.0, (float) state->screenHeight / 1200.0);
  state->fontSize = scale * 32.0;
  state->movementSpeed = scale * 8.0;
  state->renderTexture = LoadRenderTexture(state->screenWidth, state->screenHeight);
  SetTextureFilter(state->renderTexture.texture, TEXTURE_FILTER_BILINEAR);
  state->gameBoundary = (Rectangle) { 0, state->fontSize, state->screenWidth, state->screenHeight - state->fontSize };
  state->screen = TITLE;
  state->score = 0;
  state->characterCount = 2;
  const Font font = GetFontDefault();
  state->characterDimensions = MeasureTextEx(font, PLAYER_CHARACTER, state->fontSize, 0.0f);
  InitializeThemes(state);
#ifndef TARGET_WEB
  ToggleFullscreen();
  HideCursor();
#endif
}

static void DestroyGame() {
  CloseWindow();
}

static void ExecuteGameFrame(GameState *state) {
  HandleKeyPress(state);
  HandleDraw(state);
  UpdatePositions(state);
}

int main(void) {
  SetRandomSeed(time(NULL));
  GameState state;
  InitializeGame(&state);
  while (!WindowShouldClose()) {
    ExecuteGameFrame(&state);
  }
  DestroyGame();
  return 0;
}
