#ifndef GAME_H
#define GAME_H

#include "types.h"

void StartGame(GameState *state);
void Move(GameState *state, MoveDirection direction);
void UpdatePositions(GameState *state);

#endif
