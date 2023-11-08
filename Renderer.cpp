#include "Renderer.h"

using std::to_string;

void Renderer::render(PuzzleGame game)
{
	states.transform *= getTransform();
	Color color = Color(200, 100, 200);

	RectangleShape shape(Vector2f(RENDER_FIELD_SIZE, RENDER_FIELD_SIZE));
	shape.setOutlineThickness(2.0f);
	shape.setOutlineColor(color);
	shape.setFillColor(Color::Transparent);
	target.draw(shape, states);

	shape.setSize(Vector2f(RENDER_CELL_SIZE, RENDER_CELL_SIZE));
	shape.setOutlineThickness(2.0f);
	shape.setOutlineColor(color);
	shape.setFillColor(Color::Transparent);

	Text text("", font, 46);

	for (unsigned int i = 0; i < FIELD_MATRIX_SIZE; i++)
	{
		shape.setOutlineColor(color);
		text.setFillColor(color);
		text.setString(to_string(field[i]));

		if (solved)
		{
			shape.setOutlineColor(Color::Cyan);
			text.setFillColor(Color::Cyan);
		}
		else if (field[i] == i + 1)
		{
			text.setFillColor(Color::Green);
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
