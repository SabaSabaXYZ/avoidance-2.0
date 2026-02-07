#ifndef RENDER_H
#define RENDER_H

#include "types.h"

void DrawTextCentre(const char *text, int posY, Color color, int gameWidth);
void DrawBoundary(GameState state);
void DrawTitle(GameState state);
void DrawGameplay(GameState state);
void DrawHelp(GameState state);
void DrawScore(GameState state);
void DrawToScreen(GameState state, Texture2D texture);
void HandleDraw(GameState state);

#endif
