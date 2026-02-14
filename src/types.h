#ifndef TYPES_H
#define TYPES_H

#include <raylib.h>

#define FONT_SIZE 32

#define GAME_LEFT FONT_SIZE
#define GAME_TOP FONT_SIZE
#define GAME_RIGHT SCREEN_WIDTH - FONT_SIZE
#define GAME_BOTTOM SCREEN_HEIGHT - FONT_SIZE

#define BOX_ID 0
#define PLAYER_ID 1
#define ENEMY_START_ID 2

#define PLAYER_CHARACTER "P"
#define BOX_CHARACTER "O"
#define ENEMY_CHARACTER "X"

#define MOVEMENT_SPEED 8.0f
#define MAX_CHARACTERS 30000

typedef enum GameScreen {
  TITLE = 0,
  GAMEPLAY,
  HELP
} GameScreen;

typedef enum MoveDirection {
  NONE = 0,
  UP,
  DOWN,
  LEFT,
  RIGHT
} MoveDirection;

typedef struct GameState {
  GameScreen screen;
  int screenWidth;
  int screenHeight;
  Rectangle gameBoundary;
  Vector2 positions[MAX_CHARACTERS];
  MoveDirection directions[MAX_CHARACTERS];
  Vector2 characterDimensions;
  unsigned int characterCount;
  unsigned long score;
  RenderTexture2D renderTexture;
} GameState;

#endif
