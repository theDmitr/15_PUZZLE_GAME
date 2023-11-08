#pragma once
#include <SFML/Graphics.hpp>

#define FIELD_SIZE 4
#define FIELD_MATRIX_SIZE FIELD_SIZE * FIELD_SIZE

#define RENDER_FIELD_SIZE 300
#define RENDER_CELL_SIZE 70

using namespace sf;

enum class Direction
{
	LEFT, RIGHT, UP, DOWN
};

class PuzzleGame : public Drawable, public Transformable
{
protected:
	int field[FIELD_MATRIX_SIZE];
	int empty_cell_index;
	bool solved;
	Font font;
public:
	PuzzleGame();
	void init();
	bool update();
	void move(Direction direction);
	virtual void draw(RenderTarget& target, RenderStates states) const;
};
