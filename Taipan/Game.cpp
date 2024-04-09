// Game.cpp

#define ULL unsigned long long
#define LL long long
#define DEBUG

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include "Game.h"
#include "Globals.h"
#include "ColourNames.h"
#include "StructsAndEnums.h"

using std::string, std::to_string, std::cout, std::endl, std::vector, std::tolower;

TextSize textsize{ NULL };
string FirmName;
ULL HoldTotal;
unsigned int Guns;
ULL HoldOpium, HoldSilk, HoldArms, HoldGeneral;
LL HoldFree;
ULL WarehouseOpium, WarehouseSilk, WarehouseArms, WarehouseGeneral;
ULL WarehouseTotal, WarehouseFree, WarehouseUsed;
unsigned int Location;
unsigned int Month, Year;
ULL Cash, Bank, Debt;
int ShipStatus;
string LocationNames[8] = { "Hong Mong", "Shanghai", "Nagasaki", "saigon", "Manila", "Singapore", "Batavia", "At Sea" };
string Months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
string ShipStatusText[6] = { "Critical", "Poor", "  Fair", "  Good", "Prime", "Perfect" };
string FontFilename;
int FH1;
int FH2;
int FT1;

Game::Game(Window* window) : GameWindow(window), gameHelper(window) {
	GameWindow = window;
	gameState.CurrentState = GameStates::Title;
	FontFilename = "DomoaregatoNormal-q2Jr.ttf";
	bool FontFileExists = std::filesystem::exists(FontFilename);
	if (!FontFileExists) {
		cout << "Font file does not exist in the path provided" << endl;
	}
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

Game::~Game() {
	SDL_DestroyRenderer(GameWindow->GetRenderer());
	TTF_CloseFont(FontH1);
	TTF_CloseFont(FontH2);
	TTF_CloseFont(FontT1);
}

// Function to Initialize game and global variables
void Game::InitGame() {
	FirmName = "Cloud Logistics, Hong Kong";
	HoldTotal = 60;
	Guns = 0;
	HoldOpium = 0; HoldSilk = 0; HoldArms = 0; HoldGeneral = 0;
	HoldFree = HoldTotal - Guns * 10 - HoldOpium - HoldSilk - HoldArms - HoldGeneral;
	WarehouseOpium = 0; WarehouseSilk = 0; WarehouseArms = 0; WarehouseGeneral = 0;
	WarehouseTotal = 10000;
	WarehouseFree = WarehouseTotal - WarehouseOpium - WarehouseSilk - WarehouseArms - WarehouseGeneral;
	WarehouseUsed = WarehouseTotal - WarehouseFree;
	Location = 0;
	Month = 0; Year = 1860;
	Cash = 0; Bank = 0; Debt = 0;
	ShipStatus = 100;
}

// Function to update game display
void Game::Update() {
	textsize = gameHelper.GetTextSize(FontT1, "ok");
	int x; int y; int w;
	float h = (float)textsize.height;
	h *= 1.1f;
	int tx, ty;
	string Label;
	//SDL_SetRenderDrawColor(GameWindow->GetRenderer(), dosColors[BLACK].r, dosColors[BLACK].g, dosColors[BLACK].b, 255);
	gameHelper.RenderClear(dosColors[BLACK]);
	
	// Firm Name banner
	x = 10; y = 10; TextAlignment ta{ TextHAlignment::Centre, TextVAlignment::Top };
	Label = "Firm: " + FirmName;
	gameHelper.DrawBox(x, y, GameWindow->GetSurface()->w - 20, 96, dosColors[WHITE]);
	textsize = gameHelper.GetTextSize(FontH2, Label);
	tx = GameWindow->GetSurface()->w/ 2; ty = y + 15;
	gameHelper.RenderText(FontH2, Label, tx, ty, ta, dosColors[WHITE]);

	// Warehouse box
	x = 10; y = 136; ta.HAlign = TextHAlignment::Left;
	gameHelper.DrawBoxWithTitle("Hong Kong Warehouse", x, y, 1000, 240, dosColors[WHITE], dosColors[BLACK]);
	gameHelper.RenderText(FontT1, "In Use:", x + 820, y + h * 2 - 30, ta, dosColors[YELLOW]);
	gameHelper.RenderText(FontT1, "Vacant:", x + 820, y + h * 4 - 30, ta, dosColors[YELLOW]);
	gameHelper.RenderText(FontT1, "Opium", x + 60, y + h * 2 - 30, ta, dosColors[GREEN]);
	gameHelper.RenderText(FontT1, "Silk", x + 60, y + h * 3 - 30, ta, dosColors[GREEN]);
	gameHelper.RenderText(FontT1, "Arms", x + 60, y + h * 4 - 30, ta, dosColors[GREEN]);
	gameHelper.RenderText(FontT1, "General", x + 60, y + h * 5 - 30,ta , dosColors[GREEN]);
	
	ta.HAlign = TextHAlignment::Right;
	gameHelper.RenderText(FontT1, gameHelper.InsertCommas(WarehouseOpium), x + 500, y + h * 2 - 30, ta, dosColors[MAGENTA]);
	gameHelper.RenderText(FontT1, gameHelper.InsertCommas(WarehouseSilk), x + 500, y + h * 3 - 30, ta, dosColors[MAGENTA]);
	gameHelper.RenderText(FontT1, gameHelper.InsertCommas(WarehouseArms), x+500, y + h * 4 - 30, ta, dosColors[MAGENTA]);
	gameHelper.RenderText(FontT1, gameHelper.InsertCommas(WarehouseGeneral), x + 500, y + h * 5 - 30, ta, dosColors[MAGENTA]);

	WarehouseFree = WarehouseTotal - WarehouseOpium - WarehouseSilk - WarehouseArms - WarehouseGeneral;
	WarehouseUsed = WarehouseTotal - WarehouseFree;

	gameHelper.RenderText(FontT1, gameHelper.InsertCommas(WarehouseUsed), x + 940, y + h * 3 - 30, ta, dosColors[LIGHT_RED]);
	gameHelper.RenderText(FontT1, gameHelper.InsertCommas(WarehouseFree), x + 940, y + h * 5 - 30, ta, dosColors[LIGHT_RED]);

	// Ship box
	x = 10; y = 416;
	gameHelper.DrawBoxWithTitle("Ship", x, y, 1000, 280, dosColors[WHITE], dosColors[BLACK]);

	ta.HAlign = TextHAlignment::Left;
	gameHelper.RenderText(FontT1, "Hold:", x + 20, y + h * 2 - 30, ta, dosColors[YELLOW]);
	gameHelper.RenderText(FontT1, "Guns:", x + 720, y + h * 2 - 30, ta, dosColors[YELLOW]);

	ta.HAlign = TextHAlignment::Right;
	HoldFree = HoldTotal - Guns * 10 - HoldOpium - HoldSilk - HoldArms - HoldGeneral;
	if (HoldFree < 0) {
		Label = "Overloaded!";
		textsize = gameHelper.GetTextSize(FontT1, Label);
		tx = x + 500 - textsize.width;
		gameHelper.RenderTextInverse(FontT1, Label, tx, y + h * 2 - 30, dosColors[BLUE], dosColors[LIGHT_RED]);
	}
	else {
		gameHelper.RenderText(FontT1, gameHelper.InsertCommas(HoldFree), x + 500, y + h * 2 - 30, ta, dosColors[LIGHT_RED]);
	}

	gameHelper.RenderText(FontT1, gameHelper.InsertCommas(Guns), x + 980, y + h * 2 - 30, ta, dosColors[LIGHT_RED]);

	ta.HAlign = TextHAlignment::Left;
	gameHelper.RenderText(FontT1, "Opium", x + 60, y + h * 3 - 30, ta, dosColors[GREEN]);
	gameHelper.RenderText(FontT1, "Silk", x + 60, y + h * 4 - 30, ta, dosColors[GREEN]);
	gameHelper.RenderText(FontT1, "Arms", x + 60, y + h * 5 - 30, ta, dosColors[GREEN]);
	gameHelper.RenderText(FontT1, "General", x + 60, y + h * 6 - 30, ta, dosColors[GREEN]);

	ta.HAlign = TextHAlignment::Right;
	gameHelper.RenderText(FontT1, gameHelper.InsertCommas(HoldOpium), x + 500, y + h * 3 - 30, ta, dosColors[MAGENTA]);
	gameHelper.RenderText(FontT1, gameHelper.InsertCommas(HoldSilk), x + 500, y + h * 4 - 30, ta, dosColors[MAGENTA]);
	gameHelper.RenderText(FontT1, gameHelper.InsertCommas(HoldArms), x + 500, y + h * 5 - 30, ta, dosColors[MAGENTA]);
	gameHelper.RenderText(FontT1, gameHelper.InsertCommas(HoldGeneral), x + 500, y + h * 6 - 30, ta, dosColors[MAGENTA]);

	// Status box
	x = 1020; y = 136; w = GameWindow->GetSurface()->w - x - 10;
	gameHelper.DrawBoxWithTitle("Status", x, y, w, 560, dosColors[WHITE], dosColors[BLACK]);

	ta.HAlign = TextHAlignment::Centre;
	tx = x + w / 2;
	gameHelper.RenderText(FontT1, "Date", tx, y + h * 1, ta, dosColors[WHITE]);

	Label = "15 ";
	Label += Months[Month];
	Label += ", ";
	Label += to_string(Year);
	gameHelper.RenderText(FontT1, Label, tx, y + h * 2, ta, dosColors[LIGHT_CYAN]);
	gameHelper.RenderText(FontT1, "Location", tx, y + h * 4, ta, dosColors[WHITE]);
	gameHelper.RenderText(FontT1, LocationNames[Location], tx, y + h * 5, ta, dosColors[LIGHT_CYAN]);
	gameHelper.RenderText(FontT1, "Debt", tx, y + h * 7, ta, dosColors[WHITE]);

	Label = "$";
	Label += gameHelper.InsertCommas(Debt);
	textsize = gameHelper.GetTextSize(FontT1, Label);
	tx = x + (w - textsize.width) / 2;
	gameHelper.RenderTextInverse(FontT1, Label, tx, y + h * 8, dosColors[BLACK],dosColors[LIGHT_CYAN]);

	gameHelper.RenderText(FontT1, "Ship Status", tx, y + h * 10, ta, dosColors[WHITE]);

	Label = ShipStatusText[ShipStatus / 20];
	Label += " : ";
	Label += to_string(ShipStatus);
	Label += "%";
	gameHelper.RenderText(FontT1, Label, tx, y + h * 11, ta, dosColors[LIGHT_CYAN]);

	// Money Section
	ta.HAlign = TextHAlignment::Left;
	x = 10; y = 710;
	gameHelper.RenderText(FontT1, "Cash", x, y, ta, dosColors[LIGHT_MAGENTA]);
	gameHelper.RenderText(FontT1, "Bank", x + 900, y, ta, dosColors[LIGHT_MAGENTA]);
	ta.HAlign = TextHAlignment::Right;
	gameHelper.RenderText(FontT1, "$" + gameHelper.InsertCommas(Cash), x + 400, y, ta, dosColors[LIGHT_GREEN]);
	gameHelper.RenderText(FontT1, "$" + gameHelper.InsertCommas(Bank), x + 1300, y, ta, dosColors[LIGHT_GREEN]);

	w = GameWindow->GetSurface()->w - 20;
	gameHelper.DrawThickHorizontalLine(x, y + h + 4, w, 3, dosColors[WHITE]);
}

void Game::TitleScreen() {
	int x, y, w, h;
	string Label;
	textsize = gameHelper.GetTextSize(FontT1, "_");
	h = textsize.height;

	//SDL_SetRenderDrawColor(GameWindow->GetRenderer(), dosColors[BLACK].r, dosColors[BLACK].g, dosColors[BLACK].b, 255);
	gameHelper.RenderClear(dosColors[BLACK]);

	SDL_Surface* Image{ gameHelper.LoadImage("junk1.png") };
	int width{ Image->w }; int height{ Image->h };	// Original width and height of the image
	float ImageScale = 1.7f;	// change this to increase/decrease size of the image on screen
	SDL_Rect DestRect{ 50, 200, width * ImageScale, height * ImageScale };	// This will maintain aspect
	SDL_Rect SrcRect{ NULL };												// ratio while resizing the image

	SDL_SetRenderDrawBlendMode(GameWindow->GetRenderer(), SDL_BLENDMODE_BLEND);
	gameHelper.BlitToRenderer(Image, SrcRect, DestRect);
	SDL_SetRenderDrawBlendMode(GameWindow->GetRenderer(), SDL_BLENDMODE_NONE);

	SDL_FreeSurface(Image);
	x = 50 + width * ImageScale / 2; y = 10; TextAlignment ta{ TextHAlignment::Centre, TextVAlignment::Top };

	gameHelper.RenderText(FontH1, "T   A   I   P   A   N   !", x, y, ta, dosColors[WHITE]);
	gameHelper.DrawThickHorizontalLine(x, y + 90, width, 6, dosColors[WHITE]);
	gameHelper.RenderText(FontT1, "A gane based on the China", x, y + 100 + h * 0, ta, dosColors[WHITE]);
	gameHelper.RenderText(FontT1, "trade of the 1860's", x, y + 100 + h * 1, ta, dosColors[WHITE]);

	x = 50 + (width * ImageScale) + 20; y = 30; width = GameWindow->GetSurface()->w - x;
	x += width / 2;

	gameHelper.RenderText(FontT1, "Programmed by:", x, y + h * 0, ta, dosColors[WHITE]);
	gameHelper.RenderText(FontT1, "Robert Konieczny", x, y + h * 1, ta, dosColors[WHITE]);

	int w1 = 300;	// Length of line
	gameHelper.DrawThickHorizontalLine(x - w1 / 2, y + h * 2 + 12, w1, 3, dosColors[WHITE]);
	gameHelper.DrawThickHorizontalLine(x - w1 / 2, y + h * 2 + 18, w1, 3, dosColors[WHITE]);

	gameHelper.RenderText(FontT1, "Copyright", x, y + h * 3, ta, dosColors[WHITE]);
	gameHelper.RenderText(FontT1, "(C)2024 by", x, y + h * 4, ta, dosColors[WHITE]);
	gameHelper.RenderText(FontT1, "Brooke Games", x, y + h * 5, ta, dosColors[WHITE]);

	gameHelper.DrawThickHorizontalLine(x - w1 / 2, y + h * 6 + 12, w1, 3, dosColors[WHITE]);
	gameHelper.DrawThickHorizontalLine(x - w1 / 2, y + h * 6 + 18, w1, 3, dosColors[WHITE]);

	gameHelper.RenderText(FontT1, "Press the", x, y + h * 7, ta, dosColors[WHITE]);

	int w3, w2;
	textsize = gameHelper.GetTextSize(FontT1, "'ESC'");
	w2 = textsize.width;

	Label = "'ESC' key";
	textsize = gameHelper.GetTextSize(FontT1, Label);
	w3 = textsize.width - w2; w = textsize.width;
	int tx = x - w3 - 6;
	gameHelper.RenderText(FontT1, Label, x, y + h * 8, ta, dosColors[WHITE]);

	gameHelper.RenderText(FontT1, "to start.", x, y + h * 9, ta, dosColors[WHITE]);

	Label = "'ESC'";
	ta.HAlign = TextHAlignment::Left;
	gameHelper.RenderTextFlash(FontT1, Label, tx, y + h * 8, ta, 1000, dosColors[WHITE], dosColors[BLACK]);
}

void Game::FirmNameScreen() {
	string Label;
	int x, y, w, h;
	
	gameHelper.RenderClear(dosColors[BLACK]);

	Label = "Please enter a name for your firm? (Max 24 characters)";
	textsize = gameHelper.GetTextSize(FontH1, Label);
	w = textsize.width; h = textsize.height;
	x = (GameWindow->GetSurface()->w - w) / 2;
	y = (GameWindow->GetSurface()->h - h) / 2;
	TextAlignment ta{ TextHAlignment::Left, TextVAlignment::Top };
	gameHelper.RenderText(FontH1, Label, x, y, ta, dosColors[WHITE]);

	gameHelper.RenderPresent();

	string UserInput = gameHelper.GetUserInput(x, y, h);
	
	if (!UserInput.empty()) {
		FirmName = UserInput + ", Hong Kong";
	}
}

void Game::StartStateScreen() {
	int x, y, h;
	string Label;
	textsize = gameHelper.GetTextSize(FontH2, "_");
	h = textsize.height;
	gameHelper.RenderClear(dosColors[BLACK]);

	x = 300; y = GameWindow->GetSurface()->h / 2; TextAlignment ta{ TextHAlignment::Left, TextVAlignment::Centre };

	gameHelper.RenderText(FontH2, "Do you want to start...", x, y - h * 3.5f, ta, dosColors[WHITE]);
	gameHelper.RenderText(FontH2, "1) With cash (and a debt)", x + 100, y - h * 1.5f, ta, dosColors[WHITE]);
	gameHelper.RenderText(FontH2, ">> or <<", x + 300, y + h * 0.5f, ta, dosColors[WHITE]);
	gameHelper.RenderText(FontH2, "2) With five guns and no cash", x + 100, y + h * 2.5f, ta, dosColors[WHITE]);
	gameHelper.RenderText(FontH2, "(But no debt!)", x + 300, y + h * 3.5f, ta, dosColors[WHITE]);

	gameHelper.RenderPresent();

	switch (gameHelper.GetUserMenuChoice("12")) {
	case '1':
		Cash = 400; Debt = 5000; Guns = 0;
		break;
	case '2':
		Cash = 0; Debt = 0; Guns = 5;
		break;
	default:
		break;
	}
}