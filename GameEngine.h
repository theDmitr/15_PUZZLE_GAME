#pragma once
#include <SFML/Graphics.hpp>
#include "PuzzleGame.h"

using namespace sf;

class GameEngine
{
private:
	Window* window;
	PuzzleGame* game;

public:
	void init(Window* window, PuzzleGame* game);
	void run();
	void update();
	void render();
};

