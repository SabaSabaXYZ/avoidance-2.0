#include "game.h"
#include "keys.h"
#include "render.h"
#include "types.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void InitializeGame(GameState *state) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(800, 800, "Avoidance");
  SetTargetFPS(60);
  int monitor = GetCurrentMonitor();
  state->gameWidth = GetMonitorWidth(monitor);
  state->gameHeight = GetMonitorHeight(monitor);
  SetWindowSize(state->gameWidth, state->gameHeight);
  state->renderTexture = LoadRenderTexture(state->gameWidth, state->gameHeight);
  SetTextureFilter(state->renderTexture.texture, TEXTURE_FILTER_BILINEAR);
  state->screen = TITLE;
  state->score = 0;
  state->positions = calloc((state->gameWidth * state->gameHeight) / FONT_SIZE, sizeof(Vector2));
  if (state->positions == NULL) {
    perror("Failed to initialize game state");
    exit(EXIT_FAILURE);
  }
  state->directions = calloc((state->gameWidth * state->gameHeight) / FONT_SIZE, sizeof(MoveDirection));
  if (state->directions == NULL) {
    perror("Failed to initialize game state");
    exit(EXIT_FAILURE);
  }
  ToggleFullscreen();
  HideCursor();
}

void DestroyGame(GameState *state) {
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
