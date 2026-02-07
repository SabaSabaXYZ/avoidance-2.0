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

void UpdatePositions(GameState *state) {
  Vector2 *playerPosition = &state->positions[PLAYER_ID];
  Vector2 *boxPosition = &state->positions[BOX_ID];
  MoveDirection playerDirection = state->directions[PLAYER_ID];
  MoveDirection boxDirection = state->directions[BOX_ID];
  switch (playerDirection) {
    case UP:
      playerPosition->y -= PLAYER_MOVEMENT;
      break;
    case DOWN:
      playerPosition->y += PLAYER_MOVEMENT;
      break;
    case LEFT:
      playerPosition->x -= PLAYER_MOVEMENT;
      break;
    case RIGHT:
      playerPosition->x += PLAYER_MOVEMENT;
      break;
    default:
      break;
  }
}

void Move(GameState *state, MoveDirection direction) {
  state->directions[PLAYER_ID] = direction;
}
