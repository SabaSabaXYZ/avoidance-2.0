#ifndef TYPES_H
#define TYPES_H

#include <raylib.h>

#define FONT_SIZE 20

#define GAME_LEFT FONT_SIZE
#define GAME_TOP FONT_SIZE
#define GAME_RIGHT SCREEN_WIDTH - FONT_SIZE
#define GAME_BOTTOM SCREEN_HEIGHT - FONT_SIZE

typedef enum GameScreen {
  TITLE = 0,
  GAMEPLAY,
  HELP
} GameScreen;

typedef struct GameState {
  GameScreen screen;
  int gameWidth;
  int gameHeight;
  Vector2 *positions;
  unsigned int character_count;
  unsigned int score;
  RenderTexture2D renderTexture;
} GameState;

#endif
