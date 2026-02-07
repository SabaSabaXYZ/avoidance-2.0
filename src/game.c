#include "game.h"

void StartGame(GameState *state) {
  state->character_count = 3;
  state->score = 0;
  state->screen = GAMEPLAY;
  Vector2 *player = &state->positions[PLAYER_ID];
  Vector2 *box = &state->positions[BOX_ID];
  box->x = (float) state->gameWidth / 2;
  box->y = (float) state->gameHeight / 2;
  player->x = box->x - FONT_SIZE * 2;
  player->y = box->y - FONT_SIZE * 2;
}

void Move(GameState *state, MoveDirection direction) {
  Vector2 *player = &state->positions[PLAYER_ID];
  switch (direction) {
    case UP:
      player->y -= PLAYER_MOVEMENT;
      break;
    case DOWN:
      player->y += PLAYER_MOVEMENT;
      break;
    case LEFT:
      player->x -= PLAYER_MOVEMENT;
      break;
    case RIGHT:
      player->x += PLAYER_MOVEMENT;
      break;
  }
}
