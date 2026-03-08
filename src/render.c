#include "render.h"
#include <raymath.h>

static void DrawTextCentre(const GameState *const state, const char *text, const int posY, const Color color, const uint32_t screenWidth) {
  const int textWidth = MeasureText(text, state->fontSize);
  DrawText(text, (screenWidth - textWidth) / 2, posY, state->fontSize, color);
}

static void DrawBoundary(const GameState *const state) {
  DrawRectangleLinesEx(state->gameBoundary, 1.0f, state->theme[state->selectedTheme].borderColour);
}

static void DrawTitle(const GameState *const state) {
  const Theme theme = state->theme[state->selectedTheme];
  const int startHeight = state->screenHeight / 2 - 6 * state->fontSize;
  DrawTextCentre(state, "==Avoidance 2.0==", startHeight, theme.foregroundColour, state->screenWidth);
  DrawTextCentre(state, "Move: W/A/S/D or Arrow Keys", startHeight + state->fontSize * 2, theme.foregroundColour, state->screenWidth);
  DrawTextCentre(state, "Help: H", startHeight + state->fontSize * 4, theme.foregroundColour, state->screenWidth);
  DrawTextCentre(state, "Play: P", startHeight + state->fontSize * 6, theme.foregroundColour, state->screenWidth);
  DrawTextCentre(state, "Stop Game: Q", startHeight + state->fontSize * 8, theme.foregroundColour, state->screenWidth);
  DrawTextCentre(state, "Toggle Theme: T", startHeight + state->fontSize * 10, theme.foregroundColour, state->screenWidth);
#ifndef TARGET_WEB
  DrawTextCentre(state, "Quit: Esc", startHeight + state->fontSize * 12, theme.foregroundColour, state->screenWidth);
#else
  DrawTextCentre(state, "Exit Fullscreen: Esc", startHeight + state->fontSize * 12, theme.foregroundColour, state->screenWidth);
#endif
}

static void DrawGameplay(const GameState *const state) {
  const Theme theme = state->theme[state->selectedTheme];
  const Font font = GetFontDefault();
  DrawTextEx(font,BOX_CHARACTER, state->positions[BOX_ID], state->fontSize, 0.0f, theme.boxColour);
  DrawTextEx(font,PLAYER_CHARACTER, state->positions[PLAYER_ID], state->fontSize, 0.0f, theme.playerColour);
  for (uint16_t i = ENEMY_START_ID; i < state->characterCount; ++i) {
    DrawTextEx(font,ENEMY_CHARACTER, state->positions[i], state->fontSize, 0.0f, theme.enemyColour);
  }
}

static void DrawHelp(const GameState *const state) {
  const Theme theme = state->theme[state->selectedTheme];
  const int startWidth = state->screenWidth / 5;
  const int startHeight = state->screenHeight / 2 - 14 * state->fontSize;
  DrawText("Use W, A, S, and D to move up, left, down, and right respectively.", startWidth, startHeight, state->fontSize, theme.foregroundColour);
  DrawText("Press Q during an active game to return to the main menu.", startWidth, startHeight + state->fontSize * 2, state->fontSize, theme.foregroundColour);
#ifndef TARGET_WEB
  DrawText("Press Esc to terminate the application.", startWidth, startHeight + state->fontSize * 4, state->fontSize, theme.foregroundColour);
#else
  DrawText("Press Esc to exit fullscreen mode.", startWidth, startHeight + state->fontSize * 4, state->fontSize, theme.foregroundColour);
#endif
  DrawText("OBJECTIVE:", startWidth, startHeight + state->fontSize * 8, state->fontSize, theme.foregroundColour);
  DrawText("Push the box around the screen, making sure that it is not pushed off the edge.", startWidth, startHeight + state->fontSize * 12, state->fontSize, theme.foregroundColour);
  DrawText("Box thieves will appear sporadically to steal the box.", startWidth, startHeight + state->fontSize * 14, state->fontSize, theme.foregroundColour);
  DrawText("Your objective is to keep the box on-screen for as long as possible.", startWidth, startHeight + state->fontSize * 16, state->fontSize, theme.foregroundColour);
  DrawText("P: Player", startWidth + state->fontSize * 4, startHeight + state->fontSize * 20, state->fontSize, theme.foregroundColour);
  DrawText("O: Box", startWidth + state->fontSize * 4, startHeight + state->fontSize * 22, state->fontSize, theme.foregroundColour);
  DrawText("X: Box Thief", startWidth + state->fontSize * 4, startHeight + state->fontSize * 24, state->fontSize, theme.foregroundColour);
  DrawText("Press any key to return to the main menu.", startWidth, startHeight + state->fontSize * 28, state->fontSize, theme.foregroundColour);
}

// Adapted from Raylib source code.
static void DrawFramesPerSecond(const GameState *const state, const int posX, const int posY) {
    Color color = LIME;
    const int fps = GetFPS();
    if ((fps < 30) && (fps >= 15)) {
      color = ORANGE;
    }
    else if (fps < 15) {
      color = RED;
    }
    DrawText(TextFormat("%2i FPS", fps), posX, posY, state->fontSize, color);
}

static void DrawScore(const GameState *const state) {
  const Theme theme = state->theme[state->selectedTheme];
  const char *score = TextFormat("Score: %lu Level: %u", state->score, state->characterCount - 2);
  const int scoreLength = MeasureText(score, state->fontSize);
  DrawText(score, state->screenWidth - scoreLength, 0, state->fontSize, theme.foregroundColour);
  DrawFramesPerSecond(state, 0, 0);
}

static void DrawToScreen(const GameState *const state, Texture2D texture) {
  const float scale = fminf((float) GetScreenWidth() / state->screenWidth, (float) GetScreenHeight() / state->screenHeight);
  BeginDrawing();
  ClearBackground(BLACK);
  const Rectangle textureRectangle = {
    .x = 0.0f,
    .y = 0.0f,
    .width = (float) texture.width,
    .height = (float) -texture.height
  };
  const Rectangle screenRectangle = {
    .x = (GetScreenWidth() - ((float) state->screenWidth * scale)) * 0.5f,
    .y = (GetScreenHeight() - ((float) state->screenHeight * scale)) * 0.5f,
    .width = state->screenWidth * scale,
    .height = state->screenHeight * scale
  };
  static const Vector2 origin = {
    .x = 0.0f,
    .y = 0.0f
  };
  DrawTexturePro(texture, textureRectangle, screenRectangle, origin, 0.0f, WHITE);
  EndDrawing();
}

void HandleDraw(const GameState *const state) {
  const Theme theme = state->theme[state->selectedTheme];
  BeginTextureMode(state->renderTexture);
  ClearBackground(theme.backgroundColour);
  DrawBoundary(state);
  switch (state->screen) {
    case TITLE:
      DrawTitle(state);
      break;
    case GAMEPLAY:
      DrawGameplay(state);
      break;
    case HELP:
      DrawHelp(state);
      break;
  }
  DrawScore(state);
  EndTextureMode();
  DrawToScreen(state, state->renderTexture.texture);
}
