#pragma once
#include "Tile.hpp"

class Block
{
public:
	Block() = default;
	Block(Tile tile, int num);
	int& Get_X();
	int& Get_Y();
	~Block();
private:
	int X{}, Y{};
};