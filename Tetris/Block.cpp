#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include "Game.hpp"
#include <iostream>

Block::Block(std::vector<std::vector<unsigned char>> &matrix,int num,int num2)
{
	if (num == 1)
	{
		if (num2 == 1)
			this->X = this->Y = 0;
		else if (num2 == 2)
		{
			this->X = 1;
			this->Y = 0;
		}
		else if (num2 == 3)
		{
			this->X = 0;
			this->Y = 1;
		}
		else
			this->X = this->Y = 1;
		matrix[this->X][this->Y] = 11;
	}
	else if (num == 2)
	{
		if (num2 == 1)
		{
			this->X = 2;
			this->Y = 0;
		}
		else if (num2 == 2)
		{
			this->X = 0;
			this->Y = 1;
		}
		else if (num2 == 3)
		{
			this->X = 1;
			this->Y = 1;
		}
		else
		{
			this->X = 2;
			this->Y = 1;
		}
		matrix[this->X][this->Y] = 12;
	}
	else if (num == 3)
	{
		if (num2 == 1)
			this->X = this->Y = 0;
		else if (num2 == 2)
		{
			this->X = 0;
			this->Y = 1;
		}
		else if (num2 == 3)
			this->X = this->Y = 1;
		else if (num2 == 4)
		{
			this->X = 2;
			this->Y = 1;
		}
		matrix[this->X][this->Y] = 13;
	}
	else if (num == 4)
	{
		this->Y = 0;
		if (num2 == 1)
			this->X = 0;
		else if (num2 == 2)
			this->X = 1;
		else if (num2 == 3)
			this->X = 2;
		else if (num2 == 4)
			this->X = 3;
		matrix[this->X][this->Y] = 14;
	}
	else if (num == 5)
	{
		if (num2 == 1)
			this->X = this->Y = 0;
		else if (num2 == 2)
		{
			this->X = 1;
			this->Y = 0;
		}
		else if (num2 == 3)
		{
			this->X = 1;
			this->Y = 1;
		}
		else if (num2 == 4)
		{
			this->X = 2;
			this->Y = 1;
		}
		matrix[this->X][this->Y] = 15;
	}
	else if (num == 6)
	{
		this->Y = 1;
		if (num2 == 1)
		{
			this->X = 1;
			this->Y = 0;
		}
		else if (num2 == 2)
			this->X = 0;
		else if (num2 == 3)
			this->X = 1;
		else if (num2 == 4)
			this->X = 2;
		matrix[this->X][this->Y] = 16;
	}
	else if (num == 7)
	{
		this->Y = 1;
		if (num2 == 1)
		{
			this->X = 1;
			this->Y = 0;
		}
		else if (num2 == 2)
		{
			this->X = 2;
			this->Y = 0;
		}
		else if (num2 == 3)
			this->X = 0;
		else if (num2 == 4)
			this->X = 1;
		matrix[this->X][this->Y] = 17;
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

Block::~Block(){}
