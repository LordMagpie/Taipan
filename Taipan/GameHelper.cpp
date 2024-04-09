// cpp

#include <vector>
#include <iostream>
#include "GameHelper.h"
#include "ColourNames.h"

using std::to_string, std::vector, std::cout, std::endl;

GameHelper::GameHelper(Window* Windowptr) : GameWindow(Windowptr) {
	FontFilename = "DomoaregatoNormal-q2Jr.ttf";
	ts = { 0, 0 };
	FH1 = 60;
	FH2 = 48;
	FT1 = 36;
	FontH1 = TTF_OpenFont(FontFilename.c_str(), FH1);
	FontH2 = TTF_OpenFont(FontFilename.c_str(), FH2);
	FontT1 = TTF_OpenFont(FontFilename.c_str(), FT1);
	if (!FontH1 || !FontH2 || !FontT1) {
		cout << "Failed to load font" << endl
			<< TTF_GetError() << endl;
	}
}

// Function to receive users response to a menu and check for validity,
// and return the valid response
char GameHelper::GetUserMenuChoice(string ValidChoices) {
	SDL_Event event;
	bool QuestionAnswered{ false };
	string UserResponse{ NULL };
	char typedChar{};

	while (!QuestionAnswered) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym >= SDLK_SPACE && event.key.keysym.sym <= SDLK_z) {
					typedChar = static_cast<char>(event.key.keysym.sym);
					UserResponse = typedChar;
				}
			}
		}
		if (IsValidChoice(UserResponse, ValidChoices)) QuestionAnswered = true;
	}
	return typedChar;
}

bool GameHelper::IsValidChoice(const string& userInput, const string& validChoices) {
	// Convert validChoices to lowercase
	string lowercaseValidChoices;
	for (char c : validChoices) {
		lowercaseValidChoices += tolower(c);
	}

	// Convert userInput to lowercase for comparison
	string lowercaseUserInput;
	for (char c : userInput) {
		lowercaseUserInput += tolower(c);
	}

	// Check if lowercaseUserInput is a valid choice
	return lowercaseValidChoices.find(lowercaseUserInput) != string::npos;
}

// Function to turn a number into a string with commas at every third digit
string GameHelper::InsertCommas(ULL n) {
	string ans = "";

	string num = to_string(n);

	int count = 0;

	for (int i = num.size() - 1; i >= 0; i--) {
		count++;
		ans.push_back(num[i]);

		if (count == 3) {
			ans.push_back(',');
			count = 0;
		}
	}

	reverse(ans.begin(), ans.end());

	if (ans.size() % 4 == 0) {
		ans.erase(ans.begin());
	}

	return ans;
}

void GameHelper::RenderFrame() {
	GameWindow->RenderFrame();
}

void GameHelper::RenderPresent() {
	GameWindow->RenderPresent();
}

void GameHelper::DrawLine(int x1, int y1, int x2, int y2, SDL_Color Colour) {
	GameWindow->DrawLine(x1, y1, x2, y2, Colour);
}

void GameHelper::DrawRectangle(int x, int y, int w, int h, SDL_Color Colour) {
	GameWindow->DrawRectangle(x, y, w, h, Colour);
}

void GameHelper::FillRectangle(int x, int y, int w, int h, SDL_Color Colour) {
	GameWindow->FillRectangle(x, y, w, h, Colour);
}

void GameHelper::OutlinedRectangle(int x, int y, int w, int h, SDL_Color Colour, SDL_Color OutlineColour) {
	GameWindow->OutlinedRectangle(x, y, w, h, Colour, OutlineColour);
}

void GameHelper::RenderText(TTF_Font* Font, string Text, int x, int y, TextAlignment ta, SDL_Color Colour) {
	TextSize ts{ GetTextSize(Font, Text) };
	int tx, ty, w{ ts.width }, h{ ts.height };
	
	switch (ta.HAlign) {
	case TextHAlignment::Left:
		tx = x;
		break;
	case TextHAlignment::Centre:
		tx = x - w / 2;
		break;
	case TextHAlignment::Right:
		tx = x - w;
		break;
	default:
		tx = x;
		break;
	}

	switch (ta.VAlign) {
	case TextVAlignment::Top:
		ty = y;
		break;
	case TextVAlignment::Centre:
		ty = y - h / 2;
		break;
	case TextVAlignment::Bottom:
		ty = y - h;
		break;
	default:
		ty = y;
		break;
	}
	
	GameWindow->RenderText(Font, Text.c_str(), tx, ty, Colour);
}

void GameHelper::RenderTextInverse(TTF_Font* Font, string Text, int x, int y, SDL_Color Colour, SDL_Color BackColour) {
	GameWindow->RenderTextInverse(Font, Text.c_str(), x, y, Colour, BackColour);
}

// Function to render text with background and foreground colours
// inverting based on the time period given in milliseconds, the period 
// controls the length of time that a full cycle takes
void GameHelper::RenderTextFlash(TTF_Font* Font, string Text, int x, int y, TextAlignment ta, int period, SDL_Color Colour, SDL_Color InverseColor) {
	static bool Flag{ true };	 // Flag to toggle inverting colours
	static Uint32 PastTime{ SDL_GetTicks() };	// Start time of current cycle
	Uint32 CurrentTime{ SDL_GetTicks() };	// Actual time of this frame
	Uint32 Delta{ CurrentTime - PastTime };	// Time difference between current time and past time

	if (Delta > period / 2) { Flag = !Flag; PastTime = CurrentTime; }	// Has half the period elapsed
	// If so toggle flag

	if (Flag) {
		RenderText(Font, Text, x, y, ta, Colour);	// Render Colour on InversColour
	}
	else {
		RenderTextInverse(Font, Text, x, y, InverseColor, Colour);	// Render InverseColour on Colour
	}
}

void GameHelper::DrawBox(int x, int y, int w, int h, SDL_Color Colour) {
	GameWindow->DrawBox(x, y, w, h, Colour);
}

void GameHelper::DrawBoxWithTitle(string Title, int x, int y, int w, int h, SDL_Color Colour, SDL_Color BackColour) {
	GameWindow->DrawBoxWithTitle(Title.c_str(), x, y, w, h, Colour, BackColour);
}

void GameHelper::DrawDialog(int x, int y, int w, int h) {
	GameWindow->DrawDialog(x, y, w, h);
}

void GameHelper::DrawButton(string ButtonText, int x, int y) {
	GameWindow->DrawButton(ButtonText.c_str(), x, y);
}

void GameHelper::DrawThickHorizontalLine(int x, int y, int w, int t, SDL_Color Colour) {
	for (int i = y; i < y + t; i++) {
		DrawLine(x, i, x + w, i, Colour);
	}
}

SDL_Surface* GameHelper::LoadImage(string Filename) {
	return GameWindow->LoadImage(Filename.c_str());
}

void GameHelper::BlitToRenderer(SDL_Surface* surface, SDL_Rect SrcRect, SDL_Rect DestRect) {
	GameWindow->BlitToRenderer(surface, SrcRect, DestRect);
}

TextSize GameHelper::GetTextSize(TTF_Font* Font, string Text) {
	return GameWindow->GetTextSize(Font, Text.c_str());
}

void GameHelper::RenderClear(SDL_Color Colour) {
	SDL_SetRenderDrawColor(GameWindow->GetRenderer(), Colour.r, Colour.g, Colour.b, 255);
	SDL_RenderClear(GameWindow->GetRenderer());
}

string GameHelper::GetUserInput(int x, int y, int height) {
	// Event loop to capture user input
	SDL_Event event;
	bool inputComplete = false;
	string userInput;
	int tx = x, ty = y + height * 2;
	string TypedString;
	vector<int> width; int count{ 0 };
	static Uint32 PastTime{ SDL_GetTicks() };
	Uint32 CurrentTime{ PastTime };
	int Delta(CurrentTime - PastTime);
	static bool Flag{ true };
	TextAlignment ta{ TextHAlignment::Left, TextVAlignment::Top };
	while (!inputComplete) {
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_RETURN) {
					// User pressed Enter, input is complete
					inputComplete = true;
				}
				else if (event.key.keysym.sym == SDLK_BACKSPACE && !userInput.empty()) {
					// Handle backspace (remove last character)
					userInput.pop_back();
					tx -= width.back();
					//RenderText(FontH2, TypedString, tx, ty, dosColors[BLACK]);
					FillRectangle(tx, ty, 100, height, dosColors[BLACK]);
					width.pop_back();
					RenderPresent();
				}
				else {
					// Append printable characters to userInput
					if (event.key.keysym.sym >= SDLK_SPACE && event.key.keysym.sym <= SDLK_z) {
						// Check if Shift is pressed
						bool shiftPressed = (SDL_GetModState() & KMOD_SHIFT) != 0;
						char typedChar = static_cast<char>(event.key.keysym.sym);

						// Convert to uppercase if Shift is pressed
						if (shiftPressed && typedChar >= 'a' && typedChar <= 'z') {
							typedChar -= ('a' - 'A');
						}
						userInput += typedChar;
						TypedString = typedChar;
						ts = GetTextSize(FontH2, TypedString);
						width.push_back(ts.width); height = ts.height;
						count++;
						FillRectangle(tx, ty, 100, height + 5, dosColors[BLACK]);
						RenderText(FontH2, TypedString, tx, ty, ta, dosColors[WHITE]);
						RenderPresent();
						tx += width.back();
					}
				}
			}
		}

		// Flashing text cursor Logic
		ts = GetTextSize(FontH2, "_");
		int CursorWidth{ ts.width };
		CurrentTime = SDL_GetTicks();
		Delta = CurrentTime - PastTime;
		if (Delta > 500) {
			Flag = !Flag;
			PastTime = CurrentTime;
		}
		if (Flag) {
			FillRectangle(tx, ty + height * 0.85f, CursorWidth, height * 0.15f, dosColors[WHITE]);
			//RenderText(FontH2, "_", tx, ty, dosColors[WHITE]);
		}
		else {
			FillRectangle(tx, ty, CursorWidth, height, dosColors[BLACK]);
		}
		RenderPresent();
	}
#ifdef DEBUG
	cout << "User input: " << userInput << endl; // Debug print
#endif
	return userInput;
}

int GameHelper::InStr(const string& istring, const string& tofind) {
	size_t position = istring.find(tofind);
	if (position != string::npos) {
		return static_cast<int>(position); // 0-based index
	}
	else {
		return -1; // Not found
	}
}