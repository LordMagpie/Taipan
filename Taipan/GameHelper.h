// GemeHelper.h

#pragma once

#include "Window.h"
#include "StructsAndEnums.h"

class GameHelper {
private:
	Window* GameWindow;
	TTF_Font* FontH1{ nullptr };
	TTF_Font* FontH2{ nullptr };
	TTF_Font* FontT1{ nullptr };
	TextSize ts;

public:
	GameHelper(Window* Windowptr);

	// Helper Functions
	char GetUserMenuChoice(string ValidChoices);
	bool IsValidChoice(const string& userInput, const string& validChoices);
	string InsertCommas(ULL n);
	void RenderFrame();
	void RenderPresent();
	void DrawLine(int x1, int y1, int x2, int y2, SDL_Color Colour);
	void DrawRectangle(int x, int y, int w, int h, SDL_Color Colour);
	void FillRectangle(int x, int y, int w, int h, SDL_Color Colour);
	void OutlinedRectangle(int x, int y, int w, int h, SDL_Color Colour, SDL_Color OutlineColour);;
	Vector2 HandleAlignment(Vector2 pos, Vector2 size, TextAlignment ta);
	void RenderText(TTF_Font* Font, string Text, Vector2 pos, TextAlignment ta, SDL_Color Colour);
	void RenderTextInverse(TTF_Font* Font, string Text, int x, int y, TextAlignment ta, SDL_Color Colour, SDL_Color BackColour);
	void RenderTextFlash(TTF_Font* Font, string Text, int x, int y, TextAlignment ta, int period, SDL_Color Colour, SDL_Color InverseColor);
	void DrawBox(int x, int y, int w, int h, SDL_Color Colour);
	void DrawBoxWithTitle(string Title, int x, int y, int w, int h, SDL_Color Colour, SDL_Color BackColour);
	void DrawDialog(int x, int y, int w, int h);
	void DrawButton(string ButtonText, int x, int y);
	void DrawThickHorizontalLine(int x, int y, int w, int t, SDL_Color colour);
	SDL_Surface* LoadImage(string Filename);
	void BlitToRenderer(SDL_Surface* surface, SDL_Rect SrcRect, SDL_Rect DestRect);
	TextSize GetTextSize(TTF_Font* Font, string Text);
	void RenderClear(SDL_Color Colour);
	string GetUserInput(int x, int y, int height);
	int InStr(const string& istring, const string& tofind);
};