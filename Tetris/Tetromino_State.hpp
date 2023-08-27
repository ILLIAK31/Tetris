#pragma once
#include <iterator>
#include <vector>
#include <SFML/Graphics.hpp>

/// <summary>
/// Class which keeps tetromino points.
/// </summary>
class Tetromino_State
{
public:
	Tetromino_State();
	/// <summary>
	/// Create a tetromino state from 4 points
	/// </summary>
	Tetromino_State(const sf::Vector2i point0, const sf::Vector2i point1, const sf::Vector2i point2, const sf::Vector2i point3);
	/// <summary>
	/// Create a tetromino state based on another tetromino and offset.
	/// </summary>
	/// <param name="anchor">Tetromino state on which our new created tetromino will be based.</param>
	/// <param name="offset">Offset from the base tetromino.</param>
	Tetromino_State(const Tetromino_State& anchor, const sf::Vector2i offset);

	const sf::Vector2i operator[](const int index) const;
	std::vector<sf::Vector2i>::const_iterator begin() const;
	std::vector<sf::Vector2i>::const_iterator end() const;
private:
	std::vector<sf::Vector2i> points;
};

