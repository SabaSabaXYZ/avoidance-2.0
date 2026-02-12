#include "game.h"
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

static Rectangle VectorToRectangle(GameState *state, Vector2 vector) {
  return (Rectangle) {
    vector.x,
    vector.y,
    state->characterDimensions.x,
    state->characterDimensions.y
  };
}

static void RestrictToGameArea(GameState *state, Vector2 *position) {
  position->x = Clamp(position->x, state->gameBoundary.x, state->gameBoundary.width);
  position->y = Clamp(position->y, state->gameBoundary.y, state->gameBoundary.height);
}

static void UpdatePositionByDirection(GameState *state, Vector2 *position, MoveDirection direction) {
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
}

static void UpdateBoxDirection(GameState *state) {
  Rectangle boxRectangle = VectorToRectangle(state, state->positions[BOX_ID]);
  for (unsigned int i = PLAYER_ID; i < state->characterCount; ++i) {
    if (CheckCollisionRecs(boxRectangle, VectorToRectangle(state, state->positions[i]))) {
      state->directions[BOX_ID] = state->directions[i];
      return;
    }
  }
  state->directions[BOX_ID] = NONE;
}

static void CheckGameEnd(GameState *state) {
  Vector2 initialBoxPosition = state->positions[BOX_ID];
  RestrictToGameArea(state, &state->positions[BOX_ID]);
  if (initialBoxPosition.x != state->positions[BOX_ID].x || initialBoxPosition.y != state->positions[BOX_ID].y) {
    state->screen = TITLE;
    return;
  }
}

static void InitializeEnemy(GameState *state, Vector2 *position, MoveDirection *direction) {
  if (position->x >= state->gameBoundary.x && position->x <= state->gameBoundary.width && position->y >= state->gameBoundary.y && position->y <= state->gameBoundary.height) {
    return;
  }
  *direction = (MoveDirection) GetRandomValue(UP, RIGHT);
  switch (*direction) {
    case UP:
      position->x = GetRandomValue(state->gameBoundary.x, state->gameBoundary.width);
      position->y = state->gameBoundary.height;
      break;
    case DOWN:
      position->x = GetRandomValue(state->gameBoundary.x, state->gameBoundary.width);
      position->y = state->gameBoundary.y;
      break;
    case LEFT:
      position->x = state->gameBoundary.width;
      position->y = GetRandomValue(state->gameBoundary.y, state->gameBoundary.height);
      break;
    case RIGHT:
      position->x = state->gameBoundary.x;
      position->y = GetRandomValue(state->gameBoundary.y, state->gameBoundary.height);
      break;
    default:
      perror("Invalid MoveDirection defined for enemy");
      exit(EXIT_FAILURE);
      break;
  }
}

void StartGame(GameState *state) {
  state->characterCount = 3;
  state->score = 0;
  state->screen = GAMEPLAY;
  Vector2 *box = &state->positions[BOX_ID];
  box->x = (float) state->screenWidth / 2;
  box->y = (float) state->screenHeight / 2;
  Vector2 *player = &state->positions[PLAYER_ID];
  player->x = box->x - FONT_SIZE * 2;
  player->y = box->y - FONT_SIZE * 2;
  state->directions[BOX_ID] = NONE;
}

void UpdatePositions(GameState *state) {
  if (state->screen != GAMEPLAY) {
    return;
  }
  state->score++;
  for (unsigned int i = ENEMY_START_ID; i < state->characterCount; ++i) {
    InitializeEnemy(state, &state->positions[i], &state->directions[i]);
  }
  for (unsigned int i = 0; i < state->characterCount; ++i) {
    UpdatePositionByDirection(state, &state->positions[i], state->directions[i]);
  }
  UpdateBoxDirection(state);
  CheckGameEnd(state);
  for (unsigned int i = PLAYER_ID; i < ENEMY_START_ID; ++i) {
    RestrictToGameArea(state, &state->positions[i]);
  }
}

void Move(GameState *state, MoveDirection direction) {
  state->directions[PLAYER_ID] = direction;
}
