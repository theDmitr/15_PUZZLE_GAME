#include "PuzzleGame.h"

#define FONT "Oswald-VariableFont_wght.ttf"

#define SOLVED_COLOR Color(207, 160, 19)
#define RIGHT_COLOR Color(75, 150, 235)
#define UNRIGHT_COLOR Color(75, 235, 160)
#define TRANSPARENT_COLOR Color(Color::Transparent)

using std::to_string;

PuzzleGame::PuzzleGame()
{
	font.loadFromFile(FONT);
	init();
}

void PuzzleGame::init()
{
	for (int i = 0; i < FIELD_MATRIX_SIZE - 1; i++)
		field[i] = i + 1;

	empty_cell_index = FIELD_MATRIX_SIZE - 1;
	field[empty_cell_index] = 0;
	solved = true;
}

bool PuzzleGame::update()
{
	for (unsigned int i = 0; i < FIELD_MATRIX_SIZE; i++)
		if (field[i] != i + 1 && field[i] != 0)
			return false;
	return true;
}

void PuzzleGame::move(Direction direction)
{
	int row = empty_cell_index / FIELD_SIZE;
	int colunm = empty_cell_index % FIELD_SIZE;

	int move_cell_index = -1;

	if (direction == Direction::LEFT && colunm < (FIELD_SIZE - 1)) 
		move_cell_index = empty_cell_index + 1;

	else if (direction == Direction::RIGHT && colunm > 0) 
		move_cell_index = empty_cell_index - 1;

	else if (direction == Direction::DOWN && row > 0) 
		move_cell_index = empty_cell_index - FIELD_SIZE;

	else if (direction == Direction::UP && row < (FIELD_SIZE - 1)) 
		move_cell_index = empty_cell_index + FIELD_SIZE;

	if (empty_cell_index >= 0 && move_cell_index >= 0)
	{
		int temp = field[empty_cell_index];
		field[empty_cell_index] = field[move_cell_index];
		field[move_cell_index] = temp;
		empty_cell_index = move_cell_index;
	}

	solved = update();
}
void PuzzleGame::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();

	RectangleShape shape(Vector2f(RENDER_FIELD_SIZE, RENDER_FIELD_SIZE));
	shape.setOutlineThickness(2.0f);
	shape.setOutlineColor(solved ? SOLVED_COLOR : UNRIGHT_COLOR);
	shape.setFillColor(TRANSPARENT_COLOR);
	target.draw(shape, states);

	shape.setSize(Vector2f(RENDER_CELL_SIZE, RENDER_CELL_SIZE));
	shape.setOutlineThickness(2.0f);
	shape.setOutlineColor(UNRIGHT_COLOR);
	shape.setFillColor(TRANSPARENT_COLOR);

	Text text("", font, 46);

	for (unsigned int i = 0; i < FIELD_MATRIX_SIZE; i++)
	{
		shape.setOutlineColor(UNRIGHT_COLOR);
		text.setFillColor(UNRIGHT_COLOR);
		text.setString(to_string(field[i]));

		if (solved)
		{
			shape.setOutlineColor(SOLVED_COLOR);
			text.setFillColor(SOLVED_COLOR);
		}
		else if (field[i] == i + 1)
		{
			text.setFillColor(RIGHT_COLOR);
		}

		if (field[i] != 0)
		{
			Vector2f position(i % FIELD_SIZE * RENDER_CELL_SIZE + 10.0f, i / FIELD_SIZE * RENDER_CELL_SIZE + 10.0f);
			shape.setPosition(position);
			text.setPosition(position.x + (field[i] < 10 ? 25.0f : 16.0f), position.y + 10.0f);
			target.draw(shape, states);
			target.draw(text, states);
		}
	}
}
