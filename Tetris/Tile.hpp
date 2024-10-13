#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// An enum that represents a rendered tile on the screen.
/// </summary>
enum class Tile
{
	/// <summary>
	/// An empty tile.
	/// </summary>
	Empty = 0,
	/// <summary>
	/// A part of a box-shaped tetromino.
	/// </summary>
	BoxPart = 1,
	/// <summary>
	/// A part of an L-shaped tetromino.
	/// </summary>
	LPart = 2,
	/// <summary>
	/// A part of a reversed L-shaped tetromino.
	/// </summary>
	ReversedLPart = 3,
	/// <summary>
	/// A part of a straight tetromino.
	/// </summary>
	StraightPart = 4,
	/// <summary>
	/// A part of a left zig-zag tetromino.
	/// </summary>
	LeftZigZagPart = 5,
	/// <summary>
	/// A part of a T-shaped tetromino.
	/// </summary>
	TPart = 6,
	/// <summary>
	/// A part of a right zig-zag tetrominos.
	/// </summary>
	RightZigZagPart = 7
};

/// <summary>
/// Get a color of the tile.
/// </summary>
/// <param name="tile">Tile, whose color will be returned.</param>
/// <returns>A color of the tile.</returns>
sf::Color TileToColor(const Tile tile);
