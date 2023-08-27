#include "Tetromino_State.hpp"

Tetromino_State::Tetromino_State() {}

Tetromino_State::Tetromino_State(const sf::Vector2i point0, const sf::Vector2i point1, const sf::Vector2i point2, const sf::Vector2i point3) :
	points(4)
{
	points[0] = point0;
	points[1] = point1;
	points[2] = point2;
	points[3] = point3;
}

Tetromino_State::Tetromino_State(const Tetromino_State& anchor, const sf::Vector2i offset) :
	points(4)
{
	for (int i = 0; i < points.size(); ++i)
	{
		points[i] = anchor[i] + offset;
	}
}

const sf::Vector2i Tetromino_State::operator[](const int index) const
{
	return points[index];
}

std::vector<sf::Vector2i>::const_iterator Tetromino_State::begin() const 
{
	return points.cbegin();
}

std::vector<sf::Vector2i>::const_iterator Tetromino_State::end() const
{
	return points.cend();
}
