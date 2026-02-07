#include "keys.h"
#include "game.h"

void HandleTitleKeyPress(GameState *state) {
  if (IsKeyPressed(KEY_H)) {
    state->screen = HELP;
  }
  else if (IsKeyPressed(KEY_P)) {
    StartGame(state);
  }
}

void HandleHelpKeyPress(GameState *state) {
  if (GetKeyPressed()) {
    state->screen = TITLE;
  }
}

void HandleGameplayKeyPress(GameState *state) {
  if (IsKeyPressed(KEY_Q)) {
    state->screen = TITLE;
  }
  else if (IsKeyPressed(KEY_A)) {
    Move(state, LEFT);
  }
  else if (IsKeyPressed(KEY_W)) {
    Move(state, UP);
  }
  else if (IsKeyPressed(KEY_D)) {
    Move(state, RIGHT);
  }
  else if (IsKeyPressed(KEY_S)) {
    Move(state, DOWN);
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
