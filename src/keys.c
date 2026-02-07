#include "keys.h"
#include "game.h"

void HandleKeyPress(GameState *state) {
  switch (state->screen) {
    case TITLE:
      if (IsKeyPressed(KEY_H)) {
        state->screen = HELP;
      }
      else if (IsKeyPressed(KEY_P)) {
        StartGame(state);
      }
      break;
    case HELP:
      if (GetKeyPressed()) {
        state->screen = TITLE;
      }
      break;
    case GAMEPLAY:
      if (IsKeyPressed(KEY_Q)) {
        state->screen = TITLE;
      }
      break;
    default:
      break;
  }
}
