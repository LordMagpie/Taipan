// Window.h

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Globals.h"

class Window
{
public:
	Window();
	~Window();
	SDL_Window* GetWindow() { return SDLWindow; }
	SDL_Surface* GetSurface() { return WindowSurface; }
	SDL_Renderer* GetRenderer() { return Renderer; }
	void RenderFrame();
	void RenderPresent();
	void DrawLine(int x1, int y1, int x2, int y2, SDL_Color Colour);
	void DrawRectangle(int x, int y, int w, int h, SDL_Color Colour);
	void FillRectangle(int x, int y, int w, int h, SDL_Color Colour);
	void OutlinedRectangle(int x, int y, int w, int h, SDL_Color Colour, SDL_Color OutlineColour);
	void RenderText(TTF_Font* Font, const char* Text, int x, int y, SDL_Color Colour);
	void RenderTextInverse(TTF_Font* Font, const char* Text, int x, int y, SDL_Color Colour, SDL_Color BackColour);
	void DrawBox(int x, int y, int w, int h, SDL_Color Colour);
	void DrawBoxWithTitle(const char* Title, int x, int y, int w, int h, SDL_Color Colour, SDL_Color BackColor);
	void DrawDialog(int x, int y, int w, int h);
	void DrawButton(const char* ButtonText, int x, int y);
	SDL_Surface* LoadImage(const char* Filename);
	void BlitToRenderer(SDL_Surface* surface, SDL_Rect SrcRect, SDL_Rect DestRect);
	TextSize GetTextSize(TTF_Font* Font, const char* Text);

private:
	SDL_Window* SDLWindow;
	SDL_Surface* WindowSurface;
	SDL_Renderer* Renderer;
};