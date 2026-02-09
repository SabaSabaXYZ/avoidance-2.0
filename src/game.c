#include "game.h"
#include <raymath.h>

void StartGame(GameState *state) {
  state->character_count = 3;
  state->score = 0;
  state->screen = GAMEPLAY;
  Vector2 *player = &state->positions[PLAYER_ID];
  Vector2 *box = &state->positions[BOX_ID];
  box->x = (float) state->screenWidth / 2;
  box->y = (float) state->screenHeight / 2;
  player->x = box->x - FONT_SIZE * 2;
  player->y = box->y - FONT_SIZE * 2;
}

void UpdatePositionByDirection(GameState *state, Vector2 *position, MoveDirection direction) {
  switch (direction) {
    case UP:
      position->y -= MOVEMENT_SPEED;
      break;
    case DOWN:
      position->y += MOVEMENT_SPEED;
      break;
    case LEFT:
      position->x -= MOVEMENT_SPEED;
      break;
    case RIGHT:
      position->x += MOVEMENT_SPEED;
      break;
    default:
      break;
  }
  position->x = Clamp(position->x, state->gameBoundary.x, state->gameBoundary.width);
  position->y = Clamp(position->y, state->gameBoundary.y, state->gameBoundary.height);
}

void UpdatePositions(GameState *state) {
  if (state->screen != GAMEPLAY) {
    return;
  }
  state->score++;
  for (unsigned int i = 0; i < state->character_count; ++i) {
    UpdatePositionByDirection(state, &state->positions[i], state->directions[i]);
  }
}

void Move(GameState *state, MoveDirection direction) {
  state->directions[PLAYER_ID] = direction;
}
