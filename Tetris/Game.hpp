#pragma once
#include <chrono>
#include <vector>
#include "Tile.hpp"
#include "Block.hpp"

constexpr unsigned char CELL = 8;
constexpr unsigned char COLUMNS = 10;
constexpr unsigned char ROWS = 20;
constexpr unsigned char SCREEN = 4;

class Game
{
public:
	Game();
	void Run();
	~Game();
private:
	sf::RenderWindow Window;
	sf::Image Icon;
	void Render();
	void Process();
	void Update();
	void RemoveRow();
	void EndGame();
	bool check_collision_y(int type) , check_collision_left(int type) , check_collision_right(int type) , check_collision(int type);
	int Position{1}, Position0{1}, Position_Start{}, Score{0};
	std::vector<std::vector<Tile>> matrix;
	std::vector<Block> blocks;
	bool status{true};
	std::chrono::high_resolution_clock::time_point start, end;
	std::chrono::milliseconds duration, duration0{0};
	int speed{700};
};