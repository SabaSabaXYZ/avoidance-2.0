#include "render.h"
#include <raymath.h>

static void DrawTextCentre(const char *text, int posY, Color color, int screenWidth) {
  const int textWidth = MeasureText(text, FONT_SIZE);
  DrawText(text, (screenWidth - textWidth) / 2, posY, FONT_SIZE, color);
}

static void DrawBoundary(GameState state) {
  DrawRectangleLinesEx(state.gameBoundary, 1.0f, RED);
}

static void DrawTitle(GameState state) {
  const int startHeight = state.screenHeight / 2 - 5 * FONT_SIZE;
  DrawTextCentre("==Avoidance 2.0==", startHeight, WHITE, state.screenWidth);
  DrawTextCentre("Move: W/A/S/D", startHeight + FONT_SIZE * 2, WHITE, state.screenWidth);
  DrawTextCentre("Help: H", startHeight + FONT_SIZE * 4, WHITE, state.screenWidth);
  DrawTextCentre("Play: P", startHeight + FONT_SIZE * 6, WHITE, state.screenWidth);
  DrawTextCentre("Stop Game: Q", startHeight + FONT_SIZE * 8, WHITE, state.screenWidth);
  DrawTextCentre("Quit: Esc", startHeight + FONT_SIZE * 10, WHITE, state.screenWidth);
}

static void DrawGameplay(GameState state) {
  const Font font = GetFontDefault();
  DrawTextEx(font, "P", state.positions[PLAYER_ID], FONT_SIZE, 0.0f, SKYBLUE);
  DrawTextEx(font, "O", state.positions[BOX_ID], FONT_SIZE, 0.0f, GREEN);
  for (unsigned int i = ENEMY_START_ID; i < state.character_count; ++i) {
    DrawTextEx(font, "X", state.positions[i], FONT_SIZE, 0.0f, PINK);
  }
}

static void DrawHelp(GameState state) {
  const int startWidth = state.screenWidth / 4;
  const int startHeight = state.screenHeight / 2 - 14 * FONT_SIZE;
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

static void DrawScore(GameState state) {
  const char *score = TextFormat("Score: %lu", state.score);
  int scoreLength = MeasureText(score, FONT_SIZE);
  DrawText(score, state.screenWidth - scoreLength, 0, FONT_SIZE, WHITE);
  DrawFPS(0, 0);
}

static void DrawToScreen(GameState state, Texture2D texture) {
  float scale = fminf((float) GetScreenWidth() / state.screenWidth, (float) GetScreenHeight() / state.screenHeight);
  BeginDrawing();
  ClearBackground(BLACK);
  Rectangle textureRectangle = (Rectangle) {
    0.0f,
    0.0f,
    (float) texture.width,
    (float) -texture.height
  };
  Rectangle screenRectangle = (Rectangle) {
    (GetScreenWidth() - ((float) state.screenWidth * scale)) * 0.5f,
    (GetScreenHeight() - ((float) state.screenHeight * scale)) * 0.5f,
    state.screenWidth * scale,
    state.screenHeight * scale
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
