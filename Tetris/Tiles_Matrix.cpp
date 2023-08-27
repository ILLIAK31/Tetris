#include "Tiles_Matrix.hpp"

Tiles_Matrix::Tiles_Matrix(const int width, const int height)  :
	tiles(width, std::vector<Tile>(height)) {}

int Tiles_Matrix::Width() const
{
	return tiles.size();
}

int Tiles_Matrix::Height() const
{
	return !tiles.empty() ? tiles[0].size() : 0;
}

void Tiles_Matrix::Reset()
{
	for (int i = 0; i < tiles.size(); ++i)
		for (int j = 0; j < tiles[i].size(); ++j)
			tiles[i][j] = Tile::Empty;
}

bool Tiles_Matrix::Check_Bounds(const sf::Vector2i point) const
{
	return point.x >= 0 && point.y >= 0 && point.x < Width() && point.y < Height();
}

std::vector<Tile>& Tiles_Matrix::operator[](const int column)
{
	return tiles[column];
}
const std::vector<Tile>& Tiles_Matrix::operator[](const int column) const
{
	return tiles[column];
}

Tile& Tiles_Matrix::operator[](const sf::Vector2i point)
{
	return tiles[point.x][point.y];
}
const Tile Tiles_Matrix::operator[](const sf::Vector2i point) const
{
	return tiles[point.x][point.y];
}

std::vector<std::vector<Tile>>::iterator Tiles_Matrix::begin()
{
	return tiles.begin();
}
std::vector<std::vector<Tile>>::iterator Tiles_Matrix::end()
{
	return tiles.end();
}
std::vector<std::vector<Tile>>::const_iterator Tiles_Matrix::cbegin() const
{
	return tiles.cbegin();
}
std::vector<std::vector<Tile>>::const_iterator Tiles_Matrix::cend() const
{
	return tiles.cend();
}
