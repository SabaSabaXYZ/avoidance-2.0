#ifndef TYPES_H
#define TYPES_H

#include <raylib.h>
#include <stdint.h>

#define BOX_ID 0
#define PLAYER_ID 1
#define ENEMY_START_ID 2

#define PLAYER_CHARACTER "P"
#define BOX_CHARACTER "O"
#define ENEMY_CHARACTER "X"

#define MAX_CHARACTERS 512

#define THEME_COUNT 6

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

typedef struct Theme {
  Color backgroundColour;
  Color foregroundColour;
  Color borderColour;
  Color boxColour;
  Color playerColour;
  Color enemyColour;
} Theme;

typedef struct GameState {
  Vector2 positions[MAX_CHARACTERS];
  MoveDirection directions[MAX_CHARACTERS];
  Theme theme[THEME_COUNT];
  RenderTexture2D renderTexture;
  Rectangle gameBoundary;
  Vector2 characterDimensions;
  uint64_t score;
  uint32_t screenWidth;
  uint32_t screenHeight;
  float movementSpeed;
  uint16_t characterCount;
  uint8_t selectedTheme;
  uint8_t fontSize;
  GameScreen screen;
} GameState;

#endif
