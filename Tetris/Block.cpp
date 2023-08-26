#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include "Game.hpp"
#include <iostream>

Block::Block(Tile tile, int num)
{
	switch (tile)
	{
	case Tile::BoxPart:
		if (num == 1)
			this->X = this->Y = 0;
		else if (num == 2)
		{
			this->X = 1;
			this->Y = 0;
		}
		else if (num == 3)
		{
			this->X = 0;
			this->Y = 1;
		}
		else
			this->X = this->Y = 1;
		break;

	case Tile::LPart:
		if (num == 1)
		{
			this->X = 2;
			this->Y = 0;
		}
		else if (num == 2)
		{
			this->X = 0;
			this->Y = 1;
		}
		else if (num == 3)
		{
			this->X = 1;
			this->Y = 1;
		}
		else
		{
			this->X = 2;
			this->Y = 1;
		}
		break;

	case Tile::ReversedLPart:
		if (num == 1)
			this->X = this->Y = 0;
		else if (num == 2)
		{
			this->X = 0;
			this->Y = 1;
		}
		else if (num == 3)
			this->X = this->Y = 1;
		else if (num == 4)
		{
			this->X = 2;
			this->Y = 1;
		}
		break;

	case Tile::StraightPart:
		this->Y = 0;
		if (num == 1)
			this->X = 0;
		else if (num == 2)
			this->X = 1;
		else if (num == 3)
			this->X = 2;
		else if (num == 4)
			this->X = 3;
		break;

	case Tile::LeftZigZagPart:
		if (num == 1)
			this->X = this->Y = 0;
		else if (num == 2)
		{
			this->X = 1;
			this->Y = 0;
		}
		else if (num == 3)
		{
			this->X = 1;
			this->Y = 1;
		}
		else if (num == 4)
		{
			this->X = 2;
			this->Y = 1;
		}
		break;

	case Tile::TPart:
		this->Y = 1;
		if (num == 1)
		{
			this->X = 1;
			this->Y = 0;
		}
		else if (num == 2)
			this->X = 0;
		else if (num == 3)
			this->X = 1;
		else if (num == 4)
			this->X = 2;
		break;

	case Tile::RightZigZagPart:
		this->Y = 1;
		if (num == 1)
		{
			this->X = 1;
			this->Y = 0;
		}
		else if (num == 2)
		{
			this->X = 2;
			this->Y = 0;
		}
		else if (num == 3)
			this->X = 0;
		else if (num == 4)
			this->X = 1;
		break;

	default:
		throw std::invalid_argument("invalid tile");
	}
}

int& Block::Get_X()
{
	return this->X;
}

int& Block::Get_Y()
{
	return this->Y;
}

Block::~Block() {}
