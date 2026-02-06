#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define FONT_SIZE 20

typedef enum GameScreen {
  TITLE = 0,
  GAMEPLAY,
  HELP
} GameScreen;

typedef struct GameState {
  GameScreen screen;
  Vector2 *positions;
  unsigned int character_count;
  unsigned int score;
} GameState;

void DrawTextCentre(const char *text, int posY, Color color) {
  int textWidth = MeasureText(text, FONT_SIZE);
  DrawText(text, (SCREEN_WIDTH - textWidth) / 2, posY, FONT_SIZE, color);
}

void DrawTitle() {
  int startHeight = SCREEN_HEIGHT / 5;
  DrawTextCentre("==Avoidance 2.0==", startHeight, WHITE);
  DrawTextCentre("Move: W/A/S/D", startHeight + FONT_SIZE * 2, WHITE);
  DrawTextCentre("Help: H", startHeight + FONT_SIZE * 4, WHITE);
  DrawTextCentre("Play: P", startHeight + FONT_SIZE * 6, WHITE);
  DrawTextCentre("Stop Game: Q", startHeight + FONT_SIZE * 8, WHITE);
  DrawTextCentre("Quit: Esc", startHeight + FONT_SIZE * 10, WHITE);
}

void DrawGameplay(GameState state) {
  int startHeight = SCREEN_HEIGHT / 4;
  DrawTextCentre("GAME", startHeight, WHITE);
  DrawTextCentre("GAME", startHeight + FONT_SIZE * 2, WHITE);
  DrawTextCentre("GAME", startHeight + FONT_SIZE * 4, WHITE);
  DrawTextCentre("GAME", startHeight + FONT_SIZE * 6, WHITE);
  DrawTextCentre("GAME", startHeight + FONT_SIZE * 8, WHITE);
}

void DrawHelp() {
  int startWidth = SCREEN_WIDTH / 4;
  int startHeight = SCREEN_HEIGHT / 7;
  int helpFontSize = 10;
  DrawText("Use W, A, S, and D to move up, left, down, and right respectively.", startWidth, startHeight, helpFontSize, WHITE);
  DrawText("Press Q during an active game to return to the main menu.", startWidth, startHeight + helpFontSize * 2, helpFontSize, WHITE);
  DrawText("Press Q while on the main menu to terminate the application.", startWidth, startHeight + helpFontSize * 4, helpFontSize, WHITE);
  DrawText("OBJECTIVE:", startWidth, startHeight + helpFontSize * 8, helpFontSize, WHITE);
  DrawText("Push the box around the screen, making sure that it is not pushed off the edge.", startWidth, startHeight + helpFontSize * 12, helpFontSize, WHITE);
  DrawText("Box thieves will appear sporadically to steal the box.", startWidth, startHeight + helpFontSize * 14, helpFontSize, WHITE);
  DrawText("Your objective is to keep the box on-screen for as long as possible.", startWidth, startHeight + helpFontSize * 16, helpFontSize, WHITE);
  DrawText("P: Player", startWidth + helpFontSize * 4, startHeight + helpFontSize * 20, helpFontSize, WHITE);
  DrawText("O: Box", startWidth + helpFontSize * 4, startHeight + helpFontSize * 22, helpFontSize, WHITE);
  DrawText("X: Box Thief", startWidth + helpFontSize * 4, startHeight + helpFontSize * 24, helpFontSize, WHITE);
  DrawText("Press any key to return to the main menu.", startWidth, startHeight + helpFontSize * 28, helpFontSize, WHITE);
}

void DrawScore(GameState state) {
  DrawText(TextFormat("Score: %u", state.score), SCREEN_WIDTH / 32, SCREEN_HEIGHT - (FONT_SIZE * 12), FONT_SIZE, WHITE);
  DrawFPS(0, 0);
}

void HandleDraw(GameState state) {
  BeginDrawing();
  ClearBackground(BLACK);
  switch (state.screen) {
    case TITLE:
      DrawTitle();
      break;
    case GAMEPLAY:
      DrawGameplay(state);
      break;
    case HELP:
      DrawHelp();
      break;
    default:
      break;
  }
  DrawScore(state);
  EndDrawing();
}

void StartGame(GameState *state) {
  state->character_count = 3;
  state->score = 0;
  state->screen = GAMEPLAY;
}

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

void InitializeGame(GameState *state) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Avoidance");
  SetTargetFPS(60);
  ToggleFullscreen();
  state->screen = TITLE;
  state->score = 0;
  state->positions = calloc((SCREEN_WIDTH * SCREEN_HEIGHT) / FONT_SIZE, sizeof(Vector2));
  if (state->positions == NULL) {
    perror("Failed to initialize game state");
    exit(EXIT_FAILURE);
  }
}

void DestroyGame(GameState *state) {
  CloseWindow();
  free(state->positions);
}

int main(void) {
  GameState state;
  InitializeGame(&state);
  while (!WindowShouldClose()) {
    HandleKeyPress(&state);
    HandleDraw(state);
  }
  DestroyGame(&state);
  return 0;
}
