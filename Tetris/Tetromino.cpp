#include "Tetromino.hpp"

Tetromino::Tetromino() {}

Tetromino::Tetromino(const std::shared_ptr<Tiles_Matrix>& _tiles,
	const std::vector<Tetromino_State>& _rotation_states,
	const Tile _tile) :
	tiles(_tiles),
	tile(_tile),
	rotation_states(_rotation_states) {}

bool Tetromino::Try_Move(const int d_x, const int d_y)
{
	return Try_Place(position.x + d_x, position.y + d_y);
}

bool Tetromino::Try_Place(const int x, const int y)
{
	sf::Vector2i target_position = { x, y };
	Tetromino_State new_state(Get_Current_State(), target_position);
	// Check collisions 
	if (Check_Collision(new_state))
		return false;

	// Clear previous tiles
	Draw(Tile::Empty);
	// Set new position
	is_placed = true;
	position = target_position;
	// Draw new tiles
	Draw(tile);

	return true;
}

bool Tetromino::Try_Rotate()
{
	auto new_rotation_state = (rotation_state + 1);
	// Prevent rotation state from going out of range
	if (new_rotation_state >= rotation_states.size())
		new_rotation_state = 0;
	// Check whether new state collides with anything
	Tetromino_State state(rotation_states[new_rotation_state], position);
	if (Check_Collision(state))
	{
		return false;
	}

	// Clear previous tiles
	Draw(Tile::Empty);
	// Set new rotation
	rotation_state = new_rotation_state;
	// Draw new tiles
	Draw(tile);

	return true;
}

const Tetromino_State& Tetromino::Get_Current_State() const
{
	return rotation_states[rotation_state];
}

void Tetromino::Draw(const Tile fill)
{
	if (!is_placed) 
		return; // We are not supposed to draw a tetromino which wasn't placed yet
	for (const auto& offset : Get_Current_State())
	{
		sf::Vector2i point = position + offset;
		(*tiles)[point] = fill;
	}
}

bool Tetromino::Check_Collision(const Tetromino_State& points) const
{
	for (const auto& point : points)
	{
		// Check whether point is not out of bounds
		if (!tiles->Check_Bounds(point))
			return true;

		// Check whether point intersects with already placed tetromino points
		bool tetrominoPart = false;
		for (const auto& offset : Get_Current_State())
		{
			if (point == position + offset)
			{
				tetrominoPart = true;
				break;
			}
		}

		if (tetrominoPart)
			continue; // We don't need to check collision because point belongs to the tetromino

		// Check whether point is on an empty tile
		if ((*tiles)[point.x][point.y] != Tile::Empty)
			return true; // Collision found 
	}
	// No collision was found
	return false;
}

Tetromino Tetromino::Create_Random(std::mt19937& random, const std::shared_ptr<Tiles_Matrix>& tiles)
{
	std::uniform_int_distribution<int> dist((int)Tile::BoxPart, (int)Tile::RightZigZagPart);
	Tile randomTile = (Tile)dist(random);

	std::vector<Tetromino_State> rotation_states;
	switch (randomTile)
	{
	case Tile::BoxPart:
		rotation_states =
		{
			{ {0, 0}, {0, 1}, {1, 0}, {1, 1} }
		};
		break;
	case Tile::LPart:
		rotation_states =
		{
			{ {1, 0}, {-1, 1}, {0, 1}, {1, 1} },
			{ {0, 1}, {-1, -1}, {-1, 0}, {-1, 1} },
			{ {-1, 1}, {1, 0}, {0, 0}, {-1, 0} },
			{ {-1, -1}, {0, -1}, {0, 0}, {0, 1} }
		};
		break;
	case Tile::ReversedLPart:
		rotation_states =
		{
			{ {-1, 0}, {-1, 1}, {0, 1}, {1, 1} },
			{ {0, -1}, {-1, -1}, {-1, 0}, {-1, 1} },
			{ {1, 1}, {1, 0}, {0, 0}, {-1, 0} },
			{ {0, 1}, {1, 1}, {1, 0}, {1, -1} }
		};
		break;
	case Tile::StraightPart:
		rotation_states =
		{
			{ {0, 0}, {1, 0}, {2, 0}, {3, 0} },
			{ {0, 0}, {0, 1}, {0, 2}, {0, 3} }
		};
		break;
	case Tile::LeftZigZagPart:
		rotation_states =
		{
			{ {-1, 0}, {0, 0}, {0, 1}, {1, 1} },
			{ {0, -1}, {0, 0}, {-1, 0}, {-1, 1} }
		};
		break;
	case Tile::TPart:
		rotation_states =
		{
			{ {0, 0}, {-1, 1}, {0, 1}, {1, 1} },
			{ {0, 0}, {-1, -1}, {-1, 0}, {-1, 1} },
			{ {0, 0}, {1, -1}, {0, -1}, {-1, -1} },
			{ {0, 0}, {1, 1}, {1, 0}, {1, -1} }
		};
		break;
	case Tile::RightZigZagPart:
		rotation_states =
		{
			{ {-1, 1}, {0, 1}, {0, 0}, {1, 0} },
			{ {-1, -1}, {-1, 0}, {0, 0}, {0, 1} }
		};
		break;
	}

	return { tiles, rotation_states, randomTile };
}
