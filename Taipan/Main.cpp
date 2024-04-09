// Main.cpp

#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Window.h"
#include "ColourNames.h"
#include "Globals.h"
#include "Game.h"

using std::cout, std::endl;

const int DesiredFPS = 15;

int main() {
	Window GameWindow;
	Game game(&GameWindow);
	SDL_Event event;
	SDL_Renderer* Renderer = GameWindow.GetRenderer();
	SDL_ShowCursor(SDL_DISABLE);

	int c{ 0 };
	int count{ 0 };
	bool RenderFlag = false;
	game.InitGame();

	Uint32 PreviousTime = SDL_GetTicks();

	while (true) {
		switch (game.GetGameState().CurrentState) {
		case GameStates::Title:
			game.TitleScreen();
			break;
		case GameStates::FirmNameQuestion:
			game.FirmNameScreen();
			game.gameState.CurrentState = GameStates::StartingStateQuestion;
			break;
		case GameStates::StartingStateQuestion:
			game.StartStateScreen();
			game.gameState.CurrentState = GameStates::MainWindow;
			break;
		case GameStates::MainWindow:
			game.Update();
			break;
		case GameStates::GameOver:
			break;
		default:
			break;
		}
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				SDL_Quit();
				return 0;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					switch (game.GetGameState().CurrentState) {
					case GameStates::Title:
						game.gameState.CurrentState = GameStates::FirmNameQuestion;
						break;
					/*case GameStates::StartingStateQuestion:
						game.gameState.CurrentState = GameStates::MainWindow;
						break;*/
					default:
						break;
					}
					break;
				case SDLK_SPACE:
					if (game.GetGameState().CurrentState == GameStates::MainWindow) {
						// Spacebar pressed, exit the program
						SDL_Quit();
						return 0;
					}
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}
		game.GetGameHelper().RenderPresent();

		Uint32 CurrentTime = SDL_GetTicks();
		Uint32 Delta = CurrentTime - PreviousTime;

		int Sleep = 1000 / DesiredFPS - Delta;
		if (Sleep > 0) {
			SDL_Delay(Sleep);
		}

		//game.Update();

		PreviousTime = CurrentTime;

		//GameWindow.RenderFrame();
	}
	
	SDL_ShowCursor(SDL_ENABLE);

	SDL_DestroyRenderer(Renderer);

	GameWindow.~Window();
	
	return 0;
}