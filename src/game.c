#include "game.h"

void StartGame(GameState *state) {
  state->character_count = 3;
  state->score = 0;
  state->screen = GAMEPLAY;
  Vector2 *player = &state->positions[PLAYER_ID];
  Vector2 *box = &state->positions[BOX_ID];
  player->x = (float) state->gameWidth / 2;
  player->y = (float) state->gameHeight / 2;
  box->x = player->x + FONT_SIZE * 2;
  box->y = player->y + FONT_SIZE * 2;
}
