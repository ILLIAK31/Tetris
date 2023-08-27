#include "Tile.hpp"

sf::Color TileToColor(const Tile tile)
{
	switch (tile)
	{
	case Tile::BoxPart: return sf::Color::Yellow;
	case Tile::LPart: return sf::Color(255, 165, 0); // Orange
	case Tile::ReversedLPart: return sf::Color::Blue;
	case Tile::StraightPart: return sf::Color(0, 255, 205); // Cyan/Light blue
	case Tile::LeftZigZagPart: return sf::Color::Red;
	case Tile::TPart: return sf::Color(205, 0, 255); // Purple
	case Tile::RightZigZagPart: return sf::Color::Green;

	// Tile::Empty
	default: return sf::Color(35, 23, 97);
	}
}
