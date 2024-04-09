// GameStates.h

#pragma once

enum class GameStates {
	Title,
	FirmNameQuestion,
	StartingStateQuestion,
	MainWindow,
	GameOver
};

enum class TextVAlignment {
	Top,
	Centre,
	Bottom
};

enum class TextHAlignment {
	Left,
	Centre,
	Right
};

struct GameState {
	GameStates CurrentState;
};

struct TextAlignment {
	TextHAlignment HAlign;
	TextVAlignment VAlign;
};