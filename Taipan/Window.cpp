// Window.cpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Window.h"
#include "ColourNames.h"
#include "Globals.h"

using std::cout, std::endl;

Window::Window() {
	SDL_Init(SDL_INIT_VIDEO);

	int ImgFlags{ IMG_INIT_PNG /* | IMG_INIT_JPG*/ };
	int ImgInitialized{ IMG_Init(ImgFlags) };
	if (!ImgInitialized) {
		cout << "Failed to initialize SDL_image" << endl
			<< SDL_GetError() << endl;
	}
	if ((ImgInitialized & ImgFlags) != ImgFlags) {
		cout << "Initialization failed for one or more image types" << endl;
	}

	if ((TTF_Init())) {
		cout << "Failed to initialize SDL_ttf" << endl
			<< TTF_GetError() << endl;
	}

	SDLWindow = SDL_CreateWindow("Taipan", 50, 50, 1920, 1080, SDL_WINDOW_FULLSCREEN_DESKTOP);
	//SDLWindow = SDL_CreateWindow("SDL Testing", 50, 50, 1800, 950, 0);

	if (!(Renderer = SDL_CreateRenderer(SDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))) {
		cout << "Renderer initialization failed" << endl
			<< SDL_GetError() << endl;
	}
	
	SDL_SetRenderDrawColor(Renderer, 0, 0, 170, 255);
	SDL_RenderClear(Renderer);
	WindowSurface = SDL_GetWindowSurface(SDLWindow);

	SDL_RenderPresent(Renderer);
	SDL_FillRect(WindowSurface, nullptr, SDL_MapRGB(WindowSurface->format, 0, 0, 170));
	SDL_RenderClear(Renderer);
}

Window::~Window() {
	TTF_Quit();
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(SDLWindow);
}

void Window::RenderFrame() {
	SDL_UpdateWindowSurface(SDLWindow);
}

void Window::RenderPresent() {
	SDL_RenderPresent(Renderer);
}

void Window::DrawLine(int x1, int y1, int x2, int y2, SDL_Color Colour) {
	SDL_SetRenderDrawColor(Renderer, Colour.r, Colour.g, Colour.b, Colour.a);
	SDL_RenderDrawLine(Renderer, x1, y1, x2, y2);
	}

void Window::DrawRectangle(int x, int y, int w, int h, SDL_Color Colour) {
	SDL_Rect Rect = { x, y, w, h };
	SDL_SetRenderDrawColor(Renderer, Colour.r, Colour.g, Colour.b, Colour.a);
	SDL_RenderDrawRect(Renderer, &Rect);}

void Window::FillRectangle(int x, int y, int w, int h, SDL_Color Colour) {
	SDL_Rect Rect = { x, y, w, h };
	SDL_SetRenderDrawColor(Renderer, Colour.r, Colour.g, Colour.b, Colour.a);
	SDL_RenderFillRect(Renderer, &Rect);
}

void Window::OutlinedRectangle(int x, int y, int w, int h, SDL_Color Colour, SDL_Color OutlineColour) {
	FillRectangle(x, y, w, h, Colour);
	DrawRectangle(x, y, w, h, OutlineColour);
	DrawRectangle(x - 1, y - 1, w + 2, h + 2, OutlineColour);
	DrawRectangle(x + 1, y + 1, w - 2, h - 2, OutlineColour);
}

void Window::RenderText(TTF_Font* Font, const char* Text, Vector2 pos, SDL_Color Colour) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(Font, Text, Colour);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Renderer, textSurface);
	SDL_Rect textRect = { pos.x, pos.y, textSurface->w, textSurface->h };
	SDL_RenderCopy(Renderer, textTexture, nullptr, &textRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void Window::RenderTextInverse(TTF_Font* Font, const char* Text, Vector2 pos, SDL_Color Colour, SDL_Color BackColour) {
	SDL_Surface* textSurface = TTF_RenderText_Shaded(Font, Text, Colour, BackColour);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Renderer, textSurface);
	SDL_Rect textRect = { pos.x, pos.y, textSurface->w, textSurface->h };
	SDL_RenderCopy(Renderer, textTexture, nullptr, &textRect);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void Window::DrawBox(int x, int y, int w, int h, SDL_Color Colour) {
	DrawRectangle(x, y, w, h, Colour);
	DrawRectangle(x + 1, y + 1, w - 2, h - 2, Colour);
	DrawRectangle(x + 2, y + 2, w - 4, h - 4, Colour);

	DrawRectangle(x + 5, y + 5, w - 10, h - 10, Colour);
	DrawRectangle(x + 6, y + 6, w - 12, h - 12, Colour);
	DrawRectangle(x + 7, y + 7, w - 14, h - 14, Colour);
}

void Window::DrawBoxWithTitle(const char* Title, int x, int y, int w, int h, SDL_Color Colour, SDL_Color BackColor) {
	TTF_Font* Font{ TTF_OpenFont(FontFilename.c_str(), FH2)};
	DrawBox(x, y, w, h, Colour);
	RenderTextInverse(Font, Title, { x + 12, y - 20 }, Colour, BackColor);
}

void Window::DrawDialog(int x, int y, int w, int h) {
	// Draw the shadow (offset by 20 pixels)
	SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);
	FillRectangle(x + 20, y + 20, w, h, { 0, 0, 0, 96 }); // Semi-transparent black

	// Reset the blending mode to normal
	SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_NONE);

	// Draw the second rectangle (fully opaque)
	FillRectangle(x, y, w, h, dosColors[GREEN]);
	DrawBoxWithTitle("Dialog", x + 4, y + 24, w - 8, h - 28, dosColors[WHITE], dosColors[GREEN]);

	DrawButton("Ok", x + w - 80, y + h - 80);
}

void Window::DrawButton(const char* ButtonText, int x, int y) {
	// Calculate text dimensions
	TTF_Font* font{ TTF_OpenFont(FontFilename.c_str(), FT1) };
	int textWidth, textHeight;
	TTF_SizeText(font, ButtonText, &textWidth, &textHeight);

	// Set button dimensions
	int buttonWidth = textWidth + 20; // Add some padding
	int buttonHeight = textHeight + 10; // Add some padding

	// Draw button background
	FillRectangle(x, y, buttonWidth, buttonHeight, dosColors[CYAN]);
	DrawRectangle(x, y, buttonWidth, buttonHeight, dosColors[WHITE]);
	DrawRectangle(x + 1, y + 1, buttonWidth - 2, buttonHeight - 2, dosColors[WHITE]);
	DrawRectangle(x + 2, y + 2, buttonWidth - 4, buttonHeight - 4, dosColors[WHITE]);

	// Render button text
	RenderText(font, ButtonText, { x + 10, y + 5 }, dosColors[WHITE]);
}

SDL_Surface* Window::LoadImage(const char* Filename) {
	SDL_Surface* Surface = IMG_Load(Filename);
	if (!Surface) {
		cout << "Failed to load image " << endl
			<< SDL_GetError() << endl;
	}
	return Surface;
}

void Window::BlitToRenderer(SDL_Surface* surface, SDL_Rect SrcRect, SDL_Rect DestRect) {
	SDL_Texture* ImageTexture{ SDL_CreateTextureFromSurface(Renderer, surface) };
	
	if (SrcRect.w == 0 && SrcRect.h == 0) {
		SDL_RenderCopy(Renderer, ImageTexture, NULL, &DestRect);
	}
	else {
		SDL_RenderCopy(Renderer, ImageTexture, &SrcRect, &DestRect);
	}
	
	SDL_DestroyTexture(ImageTexture);
}

TextSize Window::GetTextSize(TTF_Font* Font, const char* Text) {
	TextSize ts;
	TTF_SizeText(Font, Text, &ts.width, &ts.height);
	return ts;
}