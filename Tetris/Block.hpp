#pragma once

class Block
{
public:
	Block() = default;
	Block(std::vector<std::vector<unsigned char>> &matrix,int num,int num2);
	int& Get_X();
	int& Get_Y();
	~Block();
private:
	int X{}, Y{};
};