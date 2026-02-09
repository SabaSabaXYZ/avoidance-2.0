#include "keys.h"
#include "game.h"

static void HandleTitleKeyPress(GameState *state) {
  if (IsKeyPressed(KEY_H)) {
    state->screen = HELP;
  }
  else if (IsKeyPressed(KEY_P)) {
    StartGame(state);
  }
}

static void HandleHelpKeyPress(GameState *state) {
  if (GetKeyPressed()) {
    state->screen = TITLE;
  }
}

static void HandleGameplayKeyPress(GameState *state) {
  if (IsKeyPressed(KEY_Q)) {
    state->screen = TITLE;
  }
  else if (IsKeyDown(KEY_A)) {
    Move(state, LEFT);
  }
  else if (IsKeyDown(KEY_W)) {
    Move(state, UP);
  }
  else if (IsKeyDown(KEY_D)) {
    Move(state, RIGHT);
  }
  else if (IsKeyDown(KEY_S)) {
    Move(state, DOWN);
  }
  else if (!GetKeyPressed()) {
    Move(state, NONE);
  }
}

void HandleKeyPress(GameState *state) {
  switch (state->screen) {
    case TITLE:
      HandleTitleKeyPress(state);
      break;
    case HELP:
      HandleHelpKeyPress(state);
      break;
    case GAMEPLAY:
      HandleGameplayKeyPress(state);
      break;
    default:
      break;
  }
}
