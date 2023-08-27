#pragma once
#include <memory>
#include <random>
#include <vector>
#include "Tetromino_State.hpp"
#include "Tile.hpp"
#include "Tiles_Matrix.hpp"

/// <summary>
/// Class for moving, rotating and 'drawing' a tetromino.
/// </summary>
class Tetromino
{
public:
	Tetromino();

	/// <summary>
	/// Try to move a tetromino. Collisions and bounds will be checked.
	/// </summary>
	/// <param name="d_x">X offset.</param>
	/// <param name="d_y">Y offset</param>
	/// <returns>
	/// true if tetromino was succesfully moved;
	/// false if tetromino can't be moved.
	/// </returns>
	bool Try_Move(const int d_x, const int d_y);
	/// <summary>
	/// Try to place a tetromino. Collisions and bounds will be checked.
	/// </summary>
	/// <param name="x">New x-position of the tetromino.</param>
	/// <param name="y">New y-position of the tetromino.</param>
	/// <returns>
	/// true if tetromino was succesfully placed;
	/// false if tetromino can't be placed.
	/// </returns>
	bool Try_Place(const int x, const int y);
	/// <summary>
	/// Try to rotate a tetromino(clockwise). Collisions and bounds will be checked.
	/// </summary>
	/// <returns>
	/// true if tetromino was succesfully rotated;
	/// false if tetromino can't be rotated.
	/// </returns>
	bool Try_Rotate();

	/// <summary>
	/// Get a current rotation state of a Tetromino.
	/// </summary>
	const Tetromino_State& Get_Current_State() const;

	/// <summary>
	/// Create a random tetromino.
	/// </summary>
	/// <param name="random">Random engine used for generation.</param>
	/// <param name="matrix">Matrix, on which tetromino will be placed</param>
	/// <returns>
	/// One of the 7 possible tetrominos choosen randomly.
	/// </returns>
	static Tetromino Create_Random(std::mt19937& random, const std::shared_ptr<Tiles_Matrix>& matrix);

private:
	Tetromino(const std::shared_ptr<Tiles_Matrix>& _matrix,
		const std::vector<Tetromino_State>& _rotation_states,
		const Tile _tile);

	/// <summary>
	/// Draw a current state of the tetromino on the matrix.
	/// </summary>
	/// <param name="fill">Tile which will be used for drawing.</param>
	void Draw(const Tile fill);
	/// <summary>
	/// Check whether given state of the tetromino collides with anything and is in matrix bounds.
	/// </summary>
	/// <param name="fill">Tile which will be used for drawing.</param>
	/// <returns>
	/// true if state collides with anything or is not in the matrix bounds;
	/// false otherwise.
	/// </returns>
	bool Check_Collision(const Tetromino_State& points) const;

	Tile tile;
	std::shared_ptr<Tiles_Matrix> tiles;

	bool is_placed{ false };
	sf::Vector2i position;
	
	int rotation_state{ 0 };
	std::vector<Tetromino_State> rotation_states;
};
