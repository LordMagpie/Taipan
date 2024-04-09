// Game.h
// Helper functions for Taipan game

#pragma once

#include <SDL2/SDL_ttf.h>
#include <string>
#include "GameHelper.h"
#include "StructsAndEnums.h"
#include "Window.h"

using std::string;

class Game {
private:
	Window* GameWindow;
	GameHelper gameHelper;
	TTF_Font* FontH1{ nullptr };
	TTF_Font* FontH2{ nullptr };
	TTF_Font* FontT1{ nullptr };
	
public:
	GameState gameState;

	Game(Window* window);
	~Game();

	GameState GetGameState() { return gameState; }
	GameHelper GetGameHelper() { return gameHelper; }

	// GameState Main Functions
	void InitGame();
	void Update();
	void TitleScreen();
	void FirmNameScreen();
	void StartStateScreen();

	// Helper functions
};