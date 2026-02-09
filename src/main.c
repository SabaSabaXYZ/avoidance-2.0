#include "game.h"
#include "keys.h"
#include "render.h"
#include "types.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int GetMaxCharacters(GameState *state) {
  return (state->screenWidth * state->screenHeight) / FONT_SIZE;
}

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
  state->positions = calloc(GetMaxCharacters(state), sizeof(Vector2));
  if (state->positions == NULL) {
    perror("Failed to initialize game state");
    exit(EXIT_FAILURE);
  }
  state->directions = calloc(GetMaxCharacters(state), sizeof(MoveDirection));
  if (state->directions == NULL) {
    perror("Failed to initialize game state");
    exit(EXIT_FAILURE);
  }
  ToggleFullscreen();
  HideCursor();
}

static void DestroyGame(GameState *state) {
  CloseWindow();
  free(state->positions);
  free(state->directions);
}

int main(void) {
  srand(time(NULL));
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
