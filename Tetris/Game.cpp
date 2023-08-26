#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include "Game.hpp"
#include "Block.hpp"
#include <vector>
#include <thread>
#include <algorithm>
#include <iterator>
#include <iostream>

Game::Game() : Window(sf::VideoMode(CELL* COLUMNS* SCREEN, CELL* ROWS* SCREEN), "Tetris"), matrix(COLUMNS, std::vector<Tile>(ROWS)), duration(0)
{
	Icon.loadFromFile("Icon.png");
	Window.setIcon(47, 47, Icon.getPixelsPtr());
	for (unsigned char col = 0; col < COLUMNS; ++col)
		for (unsigned char row = 0; row < ROWS; ++row)
			matrix[col][row] = Tile::Empty;
	Window.setFramerateLimit(8.2);
	start = std::chrono::high_resolution_clock::now();
}

void Game::Run()
{
	while (Window.isOpen())
	{
		if (status == true)
		{
			std::mt19937 mt_engine(std::random_device{}());
			std::uniform_int_distribution<int> dist(1, 7);
			status = false;
			Position = 1;

			// Choose a random tetromino
			Position_Start = dist(mt_engine);
			// Determine tile type of the tetromino
			Tile tetrominoTile = (Tile)Position_Start;
			// Add blocks of the tetromino to the vector
			for (int i = 1; i <= 4; ++i)
			{
				Block block(tetrominoTile, i);
				blocks.push_back(block);

				// Check whether we can spawn the block
				if (matrix[block.Get_X()][block.Get_Y()] != Tile::Empty)
				{
					// Losing condition of the game has been met
					EndGame();
					return;
				}
			}
			// Update the matrix
			for (auto& block : blocks)
			{
				matrix[block.Get_X()][block.Get_Y()] = tetrominoTile;
			}
		}
		Render();
		if (status == false)
			Process();
		end = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		if (duration.count() >= speed + duration0.count())
		{
			duration0 = duration;
			Update();
		}
		if (status == true)
			Delete();
	}
}

void Game::Render()
{
	Window.clear();
	Window.setSize(sf::Vector2u(CELL * COLUMNS * SCREEN, CELL * ROWS * SCREEN));
	Window.setView(sf::View(sf::FloatRect(0, 0, CELL * COLUMNS, CELL * ROWS)));
	sf::RectangleShape cell(sf::Vector2f(CELL - 1, CELL - 1));
	for (unsigned char col = 0; col < COLUMNS; ++col)
		for (unsigned char row = 0; row < ROWS; ++row)
		{
			cell.setFillColor(TileToColor(matrix[col][row]));
			cell.setPosition(CELL * col, CELL * row);
			Window.draw(cell);
		}
	Window.display();
}

void Game::Process()
{
	sf::Event Event;
	while (Window.pollEvent(Event))
		if (Event.type == sf::Event::Closed)
			Window.close();
	switch (Position_Start)
	{
	case 1:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (check_collision_left(1)))
		{
			matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
			matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::BoxPart;
			matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
			matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::BoxPart;
			matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
			matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::BoxPart;
			matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
			matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::BoxPart;
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (check_collision_right(1)))
		{
			matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
			matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::BoxPart;
			matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
			matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::BoxPart;
			matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
			matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::BoxPart;
			matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
			matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::BoxPart;
		}
		break;
	case 2:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			if ((Position == 1) && (check_collision_left(2)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LPart;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LPart;
			}
			else if ((Position == 2) && (check_collision_left(22)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LPart;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LPart;
			}
			else if ((Position == 3) && (check_collision_left(23)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LPart;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LPart;
			}
			else if ((Position == 4) && (check_collision_left(24)))
			{
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LPart;
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LPart;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LPart;
			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		{
			if ((Position == 1) && (check_collision_right(2)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LPart;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LPart;
			}
			else if ((Position == 2) && (check_collision_right(22)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LPart;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LPart;
			}
			else if ((Position == 3) && (check_collision_right(23)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LPart;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LPart;
			}
			else if ((Position == 4) && (check_collision_right(24)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LPart;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LPart;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			++Position;
			if (Position > 4)
				Position = 1;
			if ((Position == 2) && (check_collision(21)))
			{
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()--] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LPart;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()--] = Tile::Empty;
				--blocks[3].Get_Y();
				--blocks[3].Get_X();
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LPart;
			}
			else if ((Position == 3) && (check_collision(22)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()--] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LPart;
			}
			else if ((Position == 4) && (check_collision(23)))
			{
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()--] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LPart;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()--] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LPart;
			}
			else if ((Position == 1) && (check_collision(2)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LPart;
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()++] = Tile::Empty;
				++blocks[2].Get_Y();
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LPart;
			}
			else
			{
				--Position;
				if (Position == 0)
					Position = 4;
			}
		}
		break;
	case 3:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			if ((Position == 1) && (check_collision_left(3)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::ReversedLPart;
			}
			else if ((Position == 2) && (check_collision_left(32)))
			{
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::ReversedLPart;
			}
			else if ((Position == 3) && (check_collision_left(33)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::ReversedLPart;
			}
			else if ((Position == 4) && (check_collision_left(34)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::ReversedLPart;
			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		{
			if ((Position == 1) && (check_collision_right(3)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::ReversedLPart;
			}
			else if ((Position == 2) && (check_collision_right(32)))
			{
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::ReversedLPart;
			}
			else if ((Position == 3) && (check_collision_right(33)))
			{
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::ReversedLPart;
			}
			else if ((Position == 4) && (check_collision_right(34)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::ReversedLPart;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			++Position;
			if (Position > 4)
				Position = 1;
			if ((Position == 2) && (check_collision(31)))
			{
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()--] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()--] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()--] = Tile::Empty;
				--blocks[2].Get_Y();
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				--blocks[3].Get_X();
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::ReversedLPart;
			}
			else if ((Position == 3) && (check_collision(32)))
			{
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				++blocks[3].Get_X();
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::ReversedLPart;
			}
			else if ((Position == 4) && (check_collision(33)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()--] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::ReversedLPart;
			}
			else if ((Position == 1) && (check_collision(3)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()++] = Tile::Empty;
				--blocks[0].Get_X();
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::ReversedLPart;
			}
			else
			{
				--Position;
				if (Position == 0)
					Position = 4;
			}
		}
		break;
	case 4:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			if ((Position == 1) && (check_collision_left(4)))
			{
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::StraightPart;
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::StraightPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::StraightPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::StraightPart;
			}
			else if ((Position == 2) && (check_collision_left(42)))
			{
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::StraightPart;
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::StraightPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::StraightPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::StraightPart;
			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		{
			if ((Position == 1) && (check_collision_right(4)))
			{
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::StraightPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::StraightPart;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::StraightPart;
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::StraightPart;
			}
			else if ((Position == 2) && (check_collision_right(42)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::StraightPart;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::StraightPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::StraightPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::StraightPart;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			++Position;
			if (Position > 2)
				Position = 1;
			if ((Position == 2) && (check_collision(41)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::StraightPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()++] = Tile::Empty;
				--blocks[2].Get_X();
				++blocks[2].Get_Y();
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::StraightPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()++] = Tile::Empty;
				--blocks[3].Get_X();
				++blocks[3].Get_Y();
				--blocks[3].Get_X();
				++blocks[3].Get_Y();
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::StraightPart;
			}
			else if ((Position == 1) && (check_collision(4)))
			{
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()--] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::StraightPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()--] = Tile::Empty;
				++blocks[2].Get_X();
				--blocks[2].Get_Y();
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::StraightPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()--] = Tile::Empty;
				++blocks[3].Get_X();
				--blocks[3].Get_Y();
				++blocks[3].Get_X();
				--blocks[3].Get_Y();
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::StraightPart;
			}
			else
			{
				--Position;
				if (Position == 0)
					Position = 2;
			}
		}
		break;
	case 5:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			if ((Position == 1) && (check_collision_left(5)))
			{
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LeftZigZagPart;
			}
			else if ((Position == 2) && (check_collision_left(52)))
			{
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LeftZigZagPart;
			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		{
			if ((Position == 1) && (check_collision_right(5)))
			{
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LeftZigZagPart;
			}
			else if ((Position == 2) && (check_collision_right(52)))
			{
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LeftZigZagPart;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			++Position;
			if (Position > 2)
				Position = 1;
			if ((Position == 2) && (check_collision(51)))
			{
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()--] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()--] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LeftZigZagPart;
			}
			else if ((Position == 1) && (check_collision(5)))
			{
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LeftZigZagPart;
			}
			else
			{
				--Position;
				if (Position == 0)
					Position = 2;
			}
		}
		break;
	case 6:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			if ((Position == 1) && (check_collision_left(6)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::TPart;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::TPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::TPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::TPart;
			}
			else if ((Position == 2) && (check_collision_left(62)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::TPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::TPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::TPart;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::TPart;
			}
			else if ((Position == 3) && (check_collision_left(63)))
			{
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::TPart;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::TPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::TPart;
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::TPart;
			}
			else if ((Position == 4) && (check_collision_left(64)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::TPart;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::TPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::TPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::TPart;
			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		{
			if ((Position == 1) && (check_collision_right(6)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::TPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::TPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::TPart;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::TPart;
			}
			else if ((Position == 2) && (check_collision_right(62)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::TPart;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::TPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::TPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::TPart;
			}
			else if ((Position == 3) && (check_collision_right(63)))
			{
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::TPart;
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::TPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::TPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::TPart;
			}
			else if ((Position == 4) && (check_collision_right(64)))
			{
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::TPart;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::TPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::TPart;
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::TPart;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			++Position;
			if (Position > 4)
				Position = 1;
			if ((Position == 2) && (check_collision(61)))
			{
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()--] = Tile::Empty;
				--blocks[1].Get_Y();
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::TPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()--] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::TPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				--blocks[3].Get_X();
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::TPart;
			}
			else if ((Position == 3) && (check_collision(62)))
			{
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				++blocks[1].Get_X();
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::TPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()--] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::TPart;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()--] = Tile::Empty;
				--blocks[3].Get_Y();
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::TPart;

			}
			else if ((Position == 4) && (check_collision(63)))
			{
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				++blocks[1].Get_Y();
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::TPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::TPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				++blocks[3].Get_X();
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::TPart;
			}
			else if ((Position == 1) && (check_collision(6)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				--blocks[1].Get_X();
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::TPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::TPart;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				++blocks[3].Get_Y();
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::TPart;
			}
			else
			{
				--Position;
				if (Position == 0)
					Position = 4;
			}
		}
		break;
	case 7:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			if ((Position == 1) && (check_collision_left(7)))
			{
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::RightZigZagPart;
			}
			else if ((Position == 2) && (check_collision_left(72)))
			{
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::RightZigZagPart;
			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		{
			if ((Position == 1) && (check_collision_right(7)))
			{
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::RightZigZagPart;
			}
			else if ((Position == 2) && (check_collision_right(72)))
			{
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::RightZigZagPart;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			++Position;
			if (Position > 2)
				Position = 1;
			if ((Position == 2) && (check_collision(71)))
			{
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()--] = Tile::Empty;
				--blocks[2].Get_Y();
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::RightZigZagPart;
			}
			else if ((Position == 1) && (check_collision(7)))
			{
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				++blocks[2].Get_Y();
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::RightZigZagPart;

			}
			else
			{
				--Position;
				if (Position == 0)
					Position = 2;
			}
		}
		break;
	}
}

void Game::Update()
{
	if (blocks.size() != 0)
	{
		if (Position_Start == 1)
		{
			if ((blocks[2].Get_Y() + 1 <= 19) && (blocks[3].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(1)))
			{
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::BoxPart;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::BoxPart;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::BoxPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::BoxPart;
			}
			else
			{
				if (speed > 200)
					speed -= 10;
				status = true;
				blocks.clear();
			}
		}
		else if (Position_Start == 2)
		{
			if ((blocks[1].Get_Y() + 1 <= 19) && (blocks[2].Get_Y() + 1 <= 19) && (blocks[3].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(2)) && (Position == 1))
			{
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LPart;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LPart;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LPart;

			}
			else if ((blocks[0].Get_Y() + 1 <= 19) && (blocks[1].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(22)) && (Position == 2))
			{
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LPart;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LPart;
			}
			else if ((blocks[1].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(23)) && (Position == 3))
			{
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LPart;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LPart;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LPart;
			}
			else if ((blocks[1].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(24)) && (Position == 4))
			{
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LPart;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LPart;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LPart;
			}
			else
			{
				if (speed > 200)
					speed -= 10;
				status = true;
				blocks.clear();
			}
		}
		else if (Position_Start == 3)
		{
			if ((blocks[1].Get_Y() + 1 <= 19) && (blocks[2].Get_Y() + 1 <= 19) && (blocks[3].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(3)) && (Position == 1))
			{
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::ReversedLPart;
			}
			else if ((blocks[3].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(32)) && (Position == 2))
			{
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::ReversedLPart;

			}
			else if ((blocks[3].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(33)) && (Position == 3))
			{
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::ReversedLPart;
			}
			else if ((blocks[3].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(34)) && (Position == 4))
			{
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::ReversedLPart;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::ReversedLPart;
			}
			else
			{
				if (speed > 200)
					speed -= 10;
				status = true;
				blocks.clear();
			}
		}
		else if (Position_Start == 4)
		{
			if ((blocks[0].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(4)) && (Position == 1))
			{
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::StraightPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::StraightPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::StraightPart;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::StraightPart;
			}
			else if ((blocks[3].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(42)) && (Position == 2))
			{
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::StraightPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::StraightPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::StraightPart;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::StraightPart;
			}
			else
			{
				if (speed > 200)
					speed -= 10;
				status = true;
				blocks.clear();
			}
		}
		else if (Position_Start == 5)
		{
			if ((blocks[2].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(5)) && (Position == 1))
			{
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LeftZigZagPart;
			}
			else if ((blocks[2].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(52)) && (Position == 2))
			{
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::LeftZigZagPart;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::LeftZigZagPart;
			}
			else
			{
				if (speed > 200)
					speed -= 10;
				status = true;
				blocks.clear();
			}
		}
		else if (Position_Start == 6)
		{
			if ((Position == 1) && (blocks[1].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(6)))
			{
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::TPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::TPart;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::TPart;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::TPart;
			}
			else if ((Position == 2) && (blocks[3].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(62)))
			{
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::TPart;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::TPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::TPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::TPart;
			}
			else if ((Position == 3) && (blocks[0].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(63)))
			{
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::TPart;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::TPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::TPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::TPart;
			}
			else if ((Position == 4) && (blocks[1].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(64)))
			{
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::TPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::TPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::TPart;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::TPart;
			}
			else
			{
				if (speed > 200)
					speed -= 10;
				status = true;
				blocks.clear();
			}
		}
		else if (Position_Start == 7)
		{
			if ((blocks[2].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(7)) && (Position == 1))
			{
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::RightZigZagPart;
			}
			else if ((blocks[3].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(72)) && (Position == 2))
			{
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = Tile::Empty;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = Tile::Empty;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = Tile::Empty;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = Tile::RightZigZagPart;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = Tile::Empty;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = Tile::RightZigZagPart;
			}
			else
			{
				if (speed > 200)
					speed -= 10;
				status = true;
				blocks.clear();
			}
		}
	}

}

void Game::Delete()
{
	std::vector<int> rows;
	for (int row = 19; row >= 0; --row)
	{
		if ((matrix[0][row] != Tile::Empty) && (matrix[1][row] != Tile::Empty) && (matrix[2][row] != Tile::Empty) && (matrix[3][row] != Tile::Empty) && (matrix[4][row] != Tile::Empty) && (matrix[5][row] != Tile::Empty) && (matrix[6][row] != Tile::Empty) && (matrix[7][row] != Tile::Empty) && (matrix[8][row] != Tile::Empty) && (matrix[9][row] != Tile::Empty))
		{
			matrix[0][row] = matrix[1][row] = matrix[2][row] = matrix[3][row] = matrix[4][row] = matrix[5][row] = matrix[6][row] = matrix[7][row] = matrix[8][row] = matrix[9][row] = Tile::Empty;
			rows.push_back(row);
			Score += 40;
		}
	}
	for (int l = 0; l < rows.size(); ++l)
	{
		for (int i = 0; i < 10; ++i)
			for (int j = rows[0]; j > 0; --j)
				matrix[i][j] = matrix[i][j - 1];
		matrix[0][0] = matrix[1][0] = matrix[2][0] = matrix[3][0] = matrix[4][0] = matrix[5][0] = matrix[6][0] = matrix[7][0] = matrix[8][0] = matrix[9][0] = Tile::Empty;
	}
	rows.clear();
}

void Game::EndGame()
{
	std::cout << "GAME OVER!" << std::endl << "Score : " << Score << std::endl;
	Window.close();
	system("pause");
}

bool Game::check_collision_y(int type)
{
	if (type == 1)
		return ((matrix[blocks[2].Get_X()][blocks[2].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 2)
		return ((matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 22)
		return ((matrix[blocks[0].Get_X()][blocks[0].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 23)
		return ((matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[0].Get_X()][blocks[0].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 24)
		return ((matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 3)
		return ((matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 32)
		return ((matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 33)
		return ((matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[0].Get_X()][blocks[0].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 34)
		return ((matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 4)
		return ((matrix[blocks[0].Get_X()][blocks[0].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 42)
		return (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == Tile::Empty) ? true : false;
	else if (type == 5)
		return ((matrix[blocks[0].Get_X()][blocks[0].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 52)
		return ((matrix[blocks[2].Get_X()][blocks[2].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 6)
		return ((matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 62)
		return ((matrix[blocks[0].Get_X()][blocks[0].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 63)
		return ((matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[0].Get_X()][blocks[0].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 64)
		return ((matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[0].Get_X()][blocks[0].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 7)
		return ((matrix[blocks[2].Get_X()][blocks[2].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 72)
		return ((matrix[blocks[0].Get_X()][blocks[0].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == Tile::Empty)) ? true : false;
}

bool Game::check_collision_left(int type)
{
	if (type == 1)
	{
		if ((blocks[0].Get_X() - 1 >= 0) && (blocks[2].Get_X() - 1 >= 0))
			return ((matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 2)
	{
		if (blocks[1].Get_X() - 1 >= 0)
			return ((matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 22)
	{
		if ((blocks[1].Get_X() - 1 >= 0) && (blocks[2].Get_X() - 1 >= 0) && (blocks[3].Get_X() - 1 >= 0))
			return ((matrix[blocks[3].Get_X() - 1][blocks[3].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 23)
	{
		if ((blocks[2].Get_X() - 1 >= 0) && (blocks[1].Get_X() - 1 >= 0))
			return ((matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 24)
	{
		if (blocks[2].Get_X() - 1 >= 0)
			return ((matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() - 1][blocks[3].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 3)
	{
		if (blocks[0].Get_X() - 1 >= 0)
			return ((matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 32)
	{
		if (blocks[0].Get_X() - 1 >= 0)
			return ((matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() - 1][blocks[3].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 33)
	{
		if (blocks[1].Get_X() - 1 >= 0)
			return ((matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() - 1][blocks[3].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 34)
	{
		if (blocks[1].Get_X() - 1 >= 0)
			return ((matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == Tile::Empty) && (matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 4)
	{
		if (blocks[0].Get_X() - 1 >= 0)
			return (matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == Tile::Empty) ? true : false;
		else
			return false;
	}
	else if (type == 42)
	{
		if (blocks[0].Get_X() - 1 >= 0)
			return ((matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() - 1][blocks[3].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 5)
	{
		if (blocks[0].Get_X() - 1 >= 0)
			return ((matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 52)
	{
		if (blocks[0].Get_X() - 1 >= 0)
			return ((matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 6)
	{
		if (blocks[1].Get_X() - 1 >= 0)
			return ((matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 62)
	{
		if (blocks[1].Get_X() - 1 >= 0)
			return ((matrix[blocks[3].Get_X() - 1][blocks[3].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 63)
	{
		if (blocks[3].Get_X() - 1 >= 0)
			return ((matrix[blocks[3].Get_X() - 1][blocks[3].Get_Y()] == Tile::Empty) && (matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 64)
	{
		if (blocks[0].Get_X() - 1 >= 0)
			return ((matrix[blocks[3].Get_X() - 1][blocks[3].Get_Y()] == Tile::Empty) && (matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 7)
	{
		if (blocks[2].Get_X() - 1 >= 0)
			return ((matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == Tile::Empty) && (matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 72)
	{
		if (blocks[2].Get_X() - 1 >= 0)
			return ((matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == Tile::Empty) && (matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() - 1][blocks[3].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
}

bool Game::check_collision_right(int type)
{
	if (type == 1)
	{
		if ((blocks[1].Get_X() + 1 <= 9) && (blocks[3].Get_X() + 1 <= 9))
			return ((matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 2)
	{
		if ((blocks[0].Get_X() + 1 <= 9) && (blocks[3].Get_X() + 1 <= 9))
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 22)
	{
		if (blocks[0].Get_X() + 1 <= 9)
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() + 1][blocks[2].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 22)
	{
		if ((blocks[0].Get_X() + 1 <= 9) && (blocks[3].Get_X() + 1 <= 9))
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 23)
	{
		if (blocks[0].Get_X() + 1 <= 9)
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 24)
	{
		if ((blocks[0].Get_X() + 1 <= 9) && (blocks[3].Get_X() + 1 <= 9) && (blocks[1].Get_X() + 1 <= 9))
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 3)
	{
		if (blocks[3].Get_X() + 1 <= 9)
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 32)
	{
		if (blocks[2].Get_X() + 1 <= 9)
			return ((matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() + 1][blocks[2].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 33)
	{
		if (blocks[2].Get_X() + 1 <= 9)
			return ((matrix[blocks[2].Get_X() + 1][blocks[2].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 34)
	{
		if (blocks[2].Get_X() + 1 <= 9)
			return ((matrix[blocks[2].Get_X() + 1][blocks[2].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty) && (matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 4)
	{
		if (blocks[3].Get_X() + 1 <= 9)
			return (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty) ? true : false;
		else
			return false;
	}
	else if (type == 42)
	{
		if (blocks[3].Get_X() + 1 <= 9)
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() + 1][blocks[2].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 5)
	{
		if (blocks[3].Get_X() + 1 <= 9)
			return ((matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 52)
	{
		if (blocks[3].Get_X() + 1 <= 9)
			return ((matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() + 1][blocks[2].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 6)
	{
		if (blocks[3].Get_X() + 1 <= 9)
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 62)
	{
		if (blocks[0].Get_X() + 1 <= 9)
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 63)
	{
		if (blocks[1].Get_X() + 1 <= 9)
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 64)
	{
		if (blocks[1].Get_X() + 1 <= 9)
			return ((matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() + 1][blocks[2].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 7)
	{
		if (blocks[1].Get_X() + 1 <= 9)
			return ((matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
	else if (type == 72)
	{
		if (blocks[1].Get_X() + 1 <= 9)
			return ((matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() + 1][blocks[2].Get_Y()] == Tile::Empty)) ? true : false;
		else
			return false;
	}
}

bool Game::check_collision(int type)
{
	if (type == 2)
		return ((blocks[0].Get_X() + 1 <= 9) && (matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == Tile::Empty)) ? true : false;
	else if (type == 21)
		return ((blocks[1].Get_Y() - 2 >= 0) && (matrix[blocks[1].Get_X()][blocks[1].Get_Y() - 2] == Tile::Empty)) ? true : false;
	else if (type == 22)
		return ((blocks[2].Get_X() + 2 <= 9) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y() - 1]) == Tile::Empty) ? true : false;
	else if (type == 23)
		return ((blocks[2].Get_Y() - 1 >= 0) && (blocks[3].Get_Y() - 1 >= 0) && (matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() - 1] == Tile::Empty) && (matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y() - 1] == Tile::Empty)) ? true : false;
	else if (type == 31)
		return ((blocks[0].Get_Y() - 1 >= 0) && (matrix[blocks[0].Get_X()][blocks[0].Get_Y() - 1] == Tile::Empty) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() - 2] == Tile::Empty)) ? true : false;
	else if (type == 32)
		return ((blocks[2].Get_X() + 1 <= 9) && (matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[3].Get_X() + 2][blocks[3].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() + 1][blocks[2].Get_Y() + 1] == Tile::Empty)) ? true : false;
	else if (type == 33)
		return ((blocks[0].Get_Y() - 1 >= 0) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() - 1] == Tile::Empty) && (matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y() - 1] == Tile::Empty)) ? true : false;
	else if (type == 3)
		return ((blocks[1].Get_X() - 1 >= 0) && (matrix[blocks[2].Get_X() - 2][blocks[2].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == Tile::Empty)) ? true : false;
	else if (type == 41)
		return ((blocks[3].Get_Y() + 3 <= 19) && (matrix[blocks[0].Get_X()][blocks[0].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[0].Get_X()][blocks[0].Get_Y() + 2] == Tile::Empty) && (matrix[blocks[0].Get_X()][blocks[0].Get_Y() + 3] == Tile::Empty)) ? true : false;
	else if (type == 4)
		return ((blocks[0].Get_X() + 3 <= 9) && (matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[0].Get_X() + 2][blocks[0].Get_Y()] == Tile::Empty) && (matrix[blocks[0].Get_X() + 3][blocks[0].Get_Y()] == Tile::Empty)) ? true : false;
	else if (type == 51)
		return ((blocks[1].Get_Y() - 1 >= 0) && (matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X()][blocks[1].Get_Y() - 1] == Tile::Empty)) ? true : false;
	else if (type == 5)
		return ((blocks[1].Get_X() + 1 <= 9) && (matrix[blocks[2].Get_X() + 1][blocks[2].Get_Y()] == Tile::Empty) && (matrix[blocks[2].Get_X() + 2][blocks[2].Get_Y()] == Tile::Empty)) ? true : false;
	else if (type == 61)
		return ((blocks[0].Get_Y() - 1 >= 0) && (matrix[blocks[1].Get_X()][blocks[1].Get_Y() - 1] == Tile::Empty) && (matrix[blocks[1].Get_X()][blocks[1].Get_Y() - 2] == Tile::Empty)) ? true : false;
	else if (type == 62)
		return ((blocks[0].Get_X() + 1 <= 9) && (matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() + 2][blocks[1].Get_Y()] == Tile::Empty)) ? true : false;
	else if (type == 63)
		return ((blocks[0].Get_Y() + 1 <= 19) && (matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == Tile::Empty) && (matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 2] == Tile::Empty)) ? true : false;
	else if (type == 6)
		return ((blocks[0].Get_X() - 1 >= 0) && (matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() - 2][blocks[1].Get_Y()] == Tile::Empty)) ? true : false;
	else if (type == 71)
		return ((blocks[0].Get_Y() - 1 >= 0) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() - 1] == Tile::Empty) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() - 2] == Tile::Empty)) ? true : false;
	else if (type == 7)
		return ((blocks[1].Get_X() + 1 <= 9) && (matrix[blocks[3].Get_X() - 1][blocks[3].Get_Y()] == Tile::Empty) && (matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == Tile::Empty)) ? true : false;
}

Game::~Game() {}