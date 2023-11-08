#include <SFML/Graphics.hpp>
#include "PuzzleGame.h"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400
#define WINDOW_CAPTION "15 puzzle game"
#define WINDOW_FPS 60

#define FONT "Oswald-VariableFont_wght.ttf"

#define CAPTION_COLOR Color(235, 91, 75)

#define MIX_NUMBER_MOVES 200

using namespace sf;

inline void refreshField(PuzzleGame& game, int numberMoves)
{
	game.init();
	for (int i = 0; i < numberMoves; i++)
		game.move((Direction)(rand() % 4));
}

int main()
{
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_CAPTION);
	window.setFramerateLimit(WINDOW_FPS);

	Image icon;
	icon.loadFromFile("icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	Font font;
	font.loadFromFile(FONT);

	Text text("F1 - new Game / Arrow Keys - Move Cells", font, 20);
	text.setFillColor(CAPTION_COLOR);
	text.setPosition(5.0f, 5.0f);

	PuzzleGame game;
	game.setPosition(50.0f, 50.0f);

	Event event;
	int move_counter = 0;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Left) 
					game.move(Direction::LEFT);

				else if (event.key.code == Keyboard::Right) 
					game.move(Direction::RIGHT);

				else if (event.key.code == Keyboard::Down) 
					game.move(Direction::DOWN);

				else if (event.key.code == Keyboard::Up) 
					game.move(Direction::UP);

				else if (event.key.code == Keyboard::F1)
					refreshField(game, MIX_NUMBER_MOVES);
			}
		}

		window.clear();
		window.draw(text);
		window.draw(game);
		window.display();
	}

	return 0;
}
