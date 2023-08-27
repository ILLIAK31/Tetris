#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.hpp"

/// <summary>
/// Class for keeping tiles.
/// </summary>
class Tiles_Matrix
{
public:
	Tiles_Matrix(const int width, const int height);

	int Width() const;
	int Height() const;

	void Reset();
	bool Check_Bounds(const sf::Vector2i point) const;

	std::vector<Tile>& operator[](const int column);
	const std::vector<Tile>& operator[](const int column) const;

	Tile& operator[](const sf::Vector2i point);
	const Tile operator[](const sf::Vector2i point) const;

	std::vector<std::vector<Tile>>::iterator begin();
	std::vector<std::vector<Tile>>::iterator end();
	std::vector<std::vector<Tile>>::const_iterator cbegin() const;
	std::vector<std::vector<Tile>>::const_iterator cend() const;

private:
	std::vector<std::vector<Tile>> tiles;
};

