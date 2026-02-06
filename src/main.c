#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

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

void DrawTextCentre(const char *text, int posY, Color color, int gameWidth) {
  const int textWidth = MeasureText(text, FONT_SIZE);
  DrawText(text, (gameWidth - textWidth) / 2, posY, FONT_SIZE, color);
}

void DrawBoundary(GameState state) {
  DrawRectangleLines(GAME_LEFT, GAME_TOP, state.gameWidth - GAME_LEFT, state.gameHeight - GAME_TOP, GOLD);
}

void DrawTitle(GameState state) {
  const int startHeight = state.gameHeight / 2 - 5 * FONT_SIZE;
  DrawTextCentre("==Avoidance 2.0==", startHeight, WHITE, state.gameWidth);
  DrawTextCentre("Move: W/A/S/D", startHeight + FONT_SIZE * 2, WHITE, state.gameWidth);
  DrawTextCentre("Help: H", startHeight + FONT_SIZE * 4, WHITE, state.gameWidth);
  DrawTextCentre("Play: P", startHeight + FONT_SIZE * 6, WHITE, state.gameWidth);
  DrawTextCentre("Stop Game: Q", startHeight + FONT_SIZE * 8, WHITE, state.gameWidth);
  DrawTextCentre("Quit: Esc", startHeight + FONT_SIZE * 10, WHITE, state.gameWidth);
}

void DrawGameplay(GameState state) {
  const int startHeight = state.gameHeight / 4;
  DrawTextCentre("GAME", startHeight, WHITE, state.gameWidth);
  DrawTextCentre("GAME", startHeight + FONT_SIZE * 2, WHITE, state.gameWidth);
  DrawTextCentre("GAME", startHeight + FONT_SIZE * 4, WHITE, state.gameWidth);
  DrawTextCentre("GAME", startHeight + FONT_SIZE * 6, WHITE, state.gameWidth);
  DrawTextCentre("GAME", startHeight + FONT_SIZE * 8, WHITE, state.gameWidth);
}

void DrawHelp(GameState state) {
  const int startWidth = state.gameWidth / 4;
  const int startHeight = state.gameHeight / 2 - 14 * FONT_SIZE;
  DrawText("Use W, A, S, and D to move up, left, down, and right respectively.", startWidth, startHeight, FONT_SIZE, WHITE);
  DrawText("Press Q during an active game to return to the main menu.", startWidth, startHeight + FONT_SIZE * 2, FONT_SIZE, WHITE);
  DrawText("Press Q while on the main menu to terminate the application.", startWidth, startHeight + FONT_SIZE * 4, FONT_SIZE, WHITE);
  DrawText("OBJECTIVE:", startWidth, startHeight + FONT_SIZE * 8, FONT_SIZE, WHITE);
  DrawText("Push the box around the screen, making sure that it is not pushed off the edge.", startWidth, startHeight + FONT_SIZE * 12, FONT_SIZE, WHITE);
  DrawText("Box thieves will appear sporadically to steal the box.", startWidth, startHeight + FONT_SIZE * 14, FONT_SIZE, WHITE);
  DrawText("Your objective is to keep the box on-screen for as long as possible.", startWidth, startHeight + FONT_SIZE * 16, FONT_SIZE, WHITE);
  DrawText("P: Player", startWidth + FONT_SIZE * 4, startHeight + FONT_SIZE * 20, FONT_SIZE, WHITE);
  DrawText("O: Box", startWidth + FONT_SIZE * 4, startHeight + FONT_SIZE * 22, FONT_SIZE, WHITE);
  DrawText("X: Box Thief", startWidth + FONT_SIZE * 4, startHeight + FONT_SIZE * 24, FONT_SIZE, WHITE);
  DrawText("Press any key to return to the main menu.", startWidth, startHeight + FONT_SIZE * 28, FONT_SIZE, WHITE);
}

void DrawScore(GameState state) {
  const char *score = TextFormat("Score: %u", state.score);
  int scoreLength = MeasureText(score, FONT_SIZE);
  DrawText(score, state.gameWidth - scoreLength, 0, FONT_SIZE, WHITE);
  DrawFPS(0, 0);
}

void DrawToScreen(GameState state, Texture2D texture) {
  float scale = fminf((float) GetScreenWidth() / state.gameWidth, (float) GetScreenHeight() / state.gameHeight);
  BeginDrawing();
  ClearBackground(BLACK);
  Rectangle textureRectangle = (Rectangle) {
    0.0f,
    0.0f,
    (float) texture.width,
    (float) -texture.height
  };
  Rectangle screenRectangle = (Rectangle) {
    (GetScreenWidth() - ((float) state.gameWidth * scale)) * 0.5f,
    (GetScreenHeight() - ((float) state.gameHeight * scale)) * 0.5f,
    state.gameWidth * scale,
    state.gameHeight * scale
  };
  DrawTexturePro(texture, textureRectangle, screenRectangle, (Vector2) { 0.0f, 0.0f }, 0.0f, WHITE);
  EndDrawing();
}

void HandleDraw(GameState state) {
  BeginTextureMode(state.renderTexture);
  ClearBackground(BLACK);
  DrawBoundary(state);
  switch (state.screen) {
    case TITLE:
      DrawTitle(state);
      break;
    case GAMEPLAY:
      DrawGameplay(state);
      break;
    case HELP:
      DrawHelp(state);
      break;
    default:
      break;
  }
  DrawScore(state);
  EndTextureMode();
  DrawToScreen(state, state.renderTexture.texture);
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
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(800, 800, "Avoidance");
  SetTargetFPS(60);
  int monitor = GetCurrentMonitor();
  state->gameWidth = GetMonitorWidth(monitor);
  state->gameHeight = GetMonitorHeight(monitor);
  SetWindowSize(state->gameWidth, state->gameHeight);
  state->renderTexture = LoadRenderTexture(state->gameWidth, state->gameHeight);
  SetTextureFilter(state->renderTexture.texture, TEXTURE_FILTER_BILINEAR);
  state->screen = TITLE;
  state->score = 0;
  state->positions = calloc((state->gameWidth * state->gameHeight) / FONT_SIZE, sizeof(Vector2));
  if (state->positions == NULL) {
    perror("Failed to initialize game state");
    exit(EXIT_FAILURE);
  }
  ToggleFullscreen();
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
