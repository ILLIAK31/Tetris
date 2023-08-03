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

Game::Game() : Window(sf::VideoMode(CELL* COLUMNS* SCREEN, CELL* ROWS* SCREEN), "Tetris") , matrix(COLUMNS, std::vector<unsigned char>(ROWS)) 
{
	Icon.loadFromFile("Icon.png");
	Window.setIcon(47,47, Icon.getPixelsPtr());
	for (unsigned char col = 0; col < COLUMNS; ++col)
		for (unsigned char row = 0; row < ROWS; ++row)
			matrix[col][row] = 0;
	Window.setFramerateLimit(8.2);
	start = std::chrono::high_resolution_clock::now();
	//
	//Position_Start = 5;
	//
}

void Game::Run()
{
	while (Window.isOpen())
	{
		if (status == true)
		{
			std::mt19937 mt_engine(std::random_device{}());
			std::uniform_int_distribution<int> dist(1, 4);
			Position_Start = dist(mt_engine);
			status = false;
			if (Position_Start == 1)
			{
				Position = 1;
				if ((matrix[0][0] != 0) || (matrix[1][0] != 0) || (matrix[0][1] != 0) || (matrix[1][1] != 0))
				{
					std::cout << "GAME OVER!" << std::endl << "Score : " << Score << std::endl;
					Window.close();
				}
				Block block1(matrix, 1, 1), block2(matrix, 1, 2), block3(matrix, 1, 3), block4(matrix, 1, 4);
				blocks.push_back(block1);
				blocks.push_back(block2);
				blocks.push_back(block3);
				blocks.push_back(block4);
			}
			else if (Position_Start == 2)
			{
				Position = 1;
				if ((matrix[2][0] != 0) || (matrix[0][1] != 0) || (matrix[1][1] != 0) || (matrix[2][1] != 0))
				{
					std::cout << "GAME OVER!" << std::endl << "Score : " << Score << std::endl;
					Window.close();
				}
				Block block1(matrix,2,1), block2(matrix,2,2), block3(matrix, 2, 3), block4(matrix, 2, 4);
				blocks.push_back(block1);
				blocks.push_back(block2);
				blocks.push_back(block3);
				blocks.push_back(block4);
			}
			else if (Position_Start == 3)
			{
				Position = 1;
				if ((matrix[0][0] != 0) || (matrix[0][1] != 0) || (matrix[1][1] != 0) || (matrix[2][1] != 0))
				{
					std::cout << "GAME OVER!" << std::endl << "Score : " << Score << std::endl;
					Window.close();
				}
				Block block1(matrix, 3, 1), block2(matrix, 3, 2), block3(matrix, 3, 3), block4(matrix, 3, 4);
				blocks.push_back(block1);
				blocks.push_back(block2);
				blocks.push_back(block3);
				blocks.push_back(block4);
			}
			else if (Position_Start == 4)
			{
				Position = 1;
				if ((matrix[0][0] != 0) || (matrix[1][0] != 0) || (matrix[2][0] != 0) || (matrix[3][0] != 0))
				{
					std::cout << "GAME OVER!" << std::endl << "Score : " << Score << std::endl;
					Window.close();
				}
				Block block1(matrix, 4, 1), block2(matrix, 4, 2), block3(matrix, 4, 3), block4(matrix, 4, 4);
				blocks.push_back(block1);
				blocks.push_back(block2);
				blocks.push_back(block3);
				blocks.push_back(block4);
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
		if(status==true)
			Delete();
	}
}

void Game::Render()
{
	Window.clear();
	Window.setSize(sf::Vector2u(CELL*COLUMNS*SCREEN,CELL*ROWS*SCREEN));
	Window.setView(sf::View(sf::FloatRect(0, 0, CELL * COLUMNS, CELL * ROWS)));
	sf::RectangleShape cell(sf::Vector2f(CELL-1,CELL-1));
	for (unsigned char col = 0; col < COLUMNS; ++col)
		for (unsigned char row = 0; row < ROWS; ++row)
		{
			if (matrix[col][row] == 11)
			{
				cell.setFillColor(sf::Color::Yellow);
				cell.setPosition(CELL*col,CELL*row);
				Window.draw(cell);
			}
			else if (matrix[col][row] == 12)
			{
				cell.setFillColor(sf::Color(255, 165, 0));
				cell.setPosition(CELL * col, CELL * row);
				Window.draw(cell);
			}
			else if (matrix[col][row] == 13)
			{
				cell.setFillColor(sf::Color::Blue);
				cell.setPosition(CELL * col, CELL * row);
				Window.draw(cell);
			}
			else if (matrix[col][row] == 14)
			{
				cell.setFillColor(sf::Color(0,255,205));
				cell.setPosition(CELL * col, CELL * row);
				Window.draw(cell);
			}
			else
			{
				cell.setFillColor(sf::Color(35, 23, 97));
				cell.setPosition(CELL * col, CELL * row);
				Window.draw(cell);
			}
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
			matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = 0;
			matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 11;
			matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = 0;
			matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 11;
			matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = 0;
			matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 11;
			matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = 0;
			matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 11;
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (check_collision_right(1)))
		{
			matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = 0;
			matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 11;
			matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = 0;
			matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 11;
			matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = 0;
			matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 11;
			matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = 0;
			matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 11;
		}
		break;
	case 2:
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			if ((Position == 1)&&(check_collision_left(2)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 12;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 12;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 12;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 12;
			}
			else if ((Position == 2) && (check_collision_left(22)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 12;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 12;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 12;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 12;
			}
			else if ((Position == 3)&&(check_collision_left(23)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 12;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 12;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 12;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 12;
			}
			else if ((Position == 4)&&(check_collision_left(24)))
			{
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 12;
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 12;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 12;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 12;
			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		{
			if ((Position == 1)&& (check_collision_right(2)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 12;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 12;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 12;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 12;
			}
			else if ((Position == 2) && (check_collision_right(22)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 12;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 12;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 12;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 12;
			}
			else if ((Position == 3)&&(check_collision_right(23)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 12;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 12;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 12;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 12;
			}
			else if ((Position == 4) && (check_collision_right(24)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 12;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 12;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 12;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 12;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			++Position;
			if (Position > 4)
				Position = 1;
			if ((Position == 2) && (check_collision(21)))
			{
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()--] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 12;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()++] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 12;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()--] = 0;
				--blocks[3].Get_Y();
				--blocks[3].Get_X();
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 12;
			}
			else if ((Position == 3) && (check_collision(22)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()--] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 12;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()++] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 12;
			}
			else if ((Position == 4) && (check_collision(23)))
			{
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 12;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()--] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 12;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()--] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 12;
			}
			else if ((Position == 1) && (check_collision(2)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()++] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 12;
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 12;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()++] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 12;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()++] = 0;
				++blocks[2].Get_Y();
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 12;
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
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 13;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 13;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 13;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 13;
			}
			else if ((Position == 2) && (check_collision_left(32)))
			{
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 13;
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 13;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 13;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 13;
			}
			else if ((Position == 3) && (check_collision_left(33)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 13;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 13;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 13;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 13;
			}
			else if ((Position == 4) && (check_collision_left(34)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 13;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 13;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 13;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 13;	
			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		{
			if ((Position == 1) && (check_collision_right(3)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 13;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 13;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 13;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 13;
			}
			else if ((Position == 2) && (check_collision_right(32)))
			{
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 13;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 13;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 13;
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 13;
			}
			else if ((Position == 3) && (check_collision_right(33)))
			{
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 13;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 13;
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 13;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 13;
			}
			else if ((Position == 4) && (check_collision_right(34)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 13;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 13;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 13;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 13;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			++Position;
			if (Position > 4)
				Position = 1;
			if ((Position == 2) && (check_collision(31)))
			{
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()--] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 13;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()--] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 13;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()--] = 0;
				--blocks[2].Get_Y();
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 13;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = 0;
				--blocks[3].Get_X();
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 13;
			}
			else if ((Position == 3) && (check_collision(32)))
			{
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = 0;
				++blocks[3].Get_X();
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 13;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()++] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 13;
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()++] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 13;
			}
			else if ((Position == 4) && (check_collision(33)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()--] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 13;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()++] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 13;
			}
			else if ((Position == 1) && (check_collision(3)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 13;
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()++] = 0;
				--blocks[0].Get_X();
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 13;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()++] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 13;
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
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 14;
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 14;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 14;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 14;
			}
			else if ((Position == 2) && (check_collision_left(42)))
			{
				matrix[blocks[0].Get_X()--][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 14;
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 14;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 14;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 14;
			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		{
			if ((Position == 1) && (check_collision_right(4)))
			{
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 14;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 14;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 14;
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 14;
			}
			else if ((Position == 2) && (check_collision_right(42)))
			{
				matrix[blocks[0].Get_X()++][blocks[0].Get_Y()] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 14;
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 14;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 14;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 14;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			++Position;
			if (Position > 2)
				Position = 1;
			if ((Position == 2) && (check_collision(41)))
			{
				matrix[blocks[1].Get_X()--][blocks[1].Get_Y()++] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 14;
				matrix[blocks[2].Get_X()--][blocks[2].Get_Y()++] = 0;
				--blocks[2].Get_X();
				++blocks[2].Get_Y();
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 14;
				matrix[blocks[3].Get_X()--][blocks[3].Get_Y()++] = 0;
				--blocks[3].Get_X();
				++blocks[3].Get_Y();
				--blocks[3].Get_X();
				++blocks[3].Get_Y();
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 14;
			}
			else if ((Position == 1) && (check_collision(4)))
			{
				matrix[blocks[1].Get_X()++][blocks[1].Get_Y()--] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 14;
				matrix[blocks[2].Get_X()++][blocks[2].Get_Y()--] = 0;
				++blocks[2].Get_X();
				--blocks[2].Get_Y();
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 14;
				matrix[blocks[3].Get_X()++][blocks[3].Get_Y()--] = 0;
				++blocks[3].Get_X();
				--blocks[3].Get_Y();
				++blocks[3].Get_X();
				--blocks[3].Get_Y();
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 14;
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
		switch (Position_Start)
		{
		case 1:
			if ((blocks[2].Get_Y() + 1 <= 19) && (blocks[3].Get_Y() + 1 <= 19) && (status == false)&&(check_collision_y(1)))
			{
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 11;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 11;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 11;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 11;
			}
			else
			{
				if (speed > 200)
					speed -= 10;
				status = true;
				blocks.clear();
			}
			break;
		case 2:
			if ((blocks[1].Get_Y() + 1 <= 19) && (blocks[2].Get_Y() + 1 <= 19) && (blocks[3].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(2)) &&(Position==1))
			{
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 12;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 12;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 12;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 12;
				
			}
			else if ((blocks[0].Get_Y() + 1 <= 19) && (blocks[1].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(22)) && (Position == 2))
			{
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 12;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 12;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 12;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 12;
			}
			else if ((blocks[1].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(23)) && (Position == 3))
			{
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 12;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 12;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 12;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 12;
			}
			else if ((blocks[1].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(24)) && (Position == 4))
			{
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 12;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 12;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 12;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 12;
			}
			else
			{
				if(speed>200)
					speed -= 10;
				status = true;
				blocks.clear();
			}
			break;
		case 3:
			if ((blocks[1].Get_Y() + 1 <= 19) &&(blocks[2].Get_Y() + 1 <= 19) && (blocks[3].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(3)) && (Position == 1))
			{
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 13;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 13;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 13;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 13;
			}
			else if ((blocks[3].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(32)) && (Position == 2))
			{
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 13;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 13;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 13;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 13;
				
			}
			else if ((blocks[3].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(33)) && (Position == 3))
			{
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 13;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 13;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 13;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 13;
			}
			else if ((blocks[3].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(34)) && (Position == 4))
			{
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 13;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 13;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 13;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 13;
			}
			else
			{
				if (speed > 200)
					speed -= 10;
				status = true;
				blocks.clear();
			}
			break;
		case 4:
			if ((blocks[0].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(4)) && (Position == 1))
			{
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 14;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 14;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 14;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 14;
			}
			else if ((blocks[3].Get_Y() + 1 <= 19) && (status == false) && (check_collision_y(42)) && (Position == 2))
			{
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()++] = 0;
				matrix[blocks[3].Get_X()][blocks[3].Get_Y()] = 14;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()++] = 0;
				matrix[blocks[2].Get_X()][blocks[2].Get_Y()] = 14;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()++] = 0;
				matrix[blocks[1].Get_X()][blocks[1].Get_Y()] = 14;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()++] = 0;
				matrix[blocks[0].Get_X()][blocks[0].Get_Y()] = 14;
			}
			else
			{
				if (speed > 200)
					speed -= 10;
				status = true;
				blocks.clear();
			}
			break;
		}
	}

}

void Game::Delete()
{
	std::vector<int> rows;
	for(int row = 19; row >= 0; --row)
	{
		if ((matrix[0][row] != 0) && (matrix[1][row] != 0) && (matrix[2][row] != 0) && (matrix[3][row] != 0) && (matrix[4][row] != 0) && (matrix[5][row] != 0) && (matrix[6][row] != 0) && (matrix[7][row] != 0) && (matrix[8][row] != 0) && (matrix[9][row] != 0))
		{
			matrix[0][row] = matrix[1][row] = matrix[2][row] = matrix[3][row] = matrix[4][row] = matrix[5][row] = matrix[6][row] = matrix[7][row] = matrix[8][row] = matrix[9][row] = 0;
			rows.push_back(row);
			Score += 40;
		}
	}
	for (int l = 0; l < rows.size(); ++l)
	{
		for (int i = 0; i < 10; ++i)
			for (int j = rows[0]; j > 0; --j)
				matrix[i][j] = matrix[i][j - 1];
		matrix[0][0] = matrix[1][0] = matrix[2][0] = matrix[3][0] = matrix[4][0] = matrix[5][0] = matrix[6][0] = matrix[7][0] = matrix[8][0] = matrix[9][0] = 0;
	}
	rows.clear();
}

bool Game::check_collision_y(int type)
{
	if(type == 1)
		return ((matrix[blocks[2].Get_X()][blocks[2].Get_Y() + 1] == 0) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == 0)) ? true : false;
	else if(type == 2)
		return ((matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == 0) &&(matrix[blocks[2].Get_X()][blocks[2].Get_Y() + 1] == 0) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == 0)) ? true : false;
	else if(type == 22)
		return ((matrix[blocks[0].Get_X()][blocks[0].Get_Y() + 1] == 0) && (matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == 0)) ? true : false;
	else if(type == 23)
		return ((matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == 0)&&(matrix[blocks[0].Get_X()][blocks[0].Get_Y() + 1] == 0)&&(matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == 0)) ? true : false;
	else if(type == 24)
		return ((matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == 0) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() + 1] == 0)) ? true : false;
	else if(type == 3)
		return ((matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == 0) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() + 1] == 0) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == 0)) ? true : false;
	else if(type == 32)
		return ((matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == 0) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() + 1] == 0)) ? true : false;
	else if (type == 33)
		return ((matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == 0) && (matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == 0) && (matrix[blocks[0].Get_X()][blocks[0].Get_Y() + 1] == 0)) ? true : false;
	else if (type == 34)
		return ((matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == 0) && (matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == 0)) ? true : false;
	else if (type == 4)
		return ((matrix[blocks[0].Get_X()][blocks[0].Get_Y() + 1] == 0) && (matrix[blocks[1].Get_X()][blocks[1].Get_Y() + 1] == 0) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() + 1] == 0) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == 0)) ? true : false;
	else if (type == 42)
		return (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 1] == 0) ? true : false;
}

bool Game::check_collision_left(int type)
{
	if (type == 1)
	{
		if ((blocks[0].Get_X() - 1 >= 0) && (blocks[2].Get_X() - 1 >= 0))
			return ((matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == 0) && (matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 2)
	{
		if (blocks[1].Get_X() - 1 >= 0)
			return ((matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == 0)&& (matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 22)
	{
		if ((blocks[1].Get_X() - 1 >= 0)&& (blocks[2].Get_X() - 1 >= 0)&& (blocks[3].Get_X() - 1 >= 0))
			return ((matrix[blocks[3].Get_X() - 1][blocks[3].Get_Y()] == 0) && (matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == 0)&&(matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 23)
	{
		if ((blocks[2].Get_X() - 1 >= 0)&&(blocks[1].Get_X() - 1 >= 0))
			return ((matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == 0) && (matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 24)
	{
		if (blocks[2].Get_X() - 1 >= 0)
			return ((matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == 0) && (matrix[blocks[3].Get_X() - 1][blocks[3].Get_Y()] == 0) && (matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 3)
	{
		if (blocks[0].Get_X() - 1 >= 0)
			return ((matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == 0) && (matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 32)
	{
		if (blocks[0].Get_X() - 1 >= 0)
			return ((matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == 0) && (matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == 0) && (matrix[blocks[3].Get_X() - 1][blocks[3].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 33)
	{
		if (blocks[1].Get_X() - 1 >= 0)
			return ((matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == 0) && (matrix[blocks[3].Get_X() - 1][blocks[3].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 34)
	{
		if (blocks[1].Get_X() - 1 >= 0)
			return ((matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == 0) && (matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == 0) && (matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 4)
	{
		if (blocks[0].Get_X() - 1 >= 0)
			return (matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == 0) ? true : false;
		else
			return false;
	}
	else if (type == 42)
	{
		if (blocks[0].Get_X() - 1 >= 0)
			return ((matrix[blocks[0].Get_X() - 1][blocks[0].Get_Y()] == 0)&& (matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == 0)&& (matrix[blocks[2].Get_X() - 1][blocks[2].Get_Y()] == 0)&& (matrix[blocks[3].Get_X() - 1][blocks[3].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
}

bool Game::check_collision_right(int type)
{
	if (type == 1)
	{
		if ((blocks[1].Get_X() + 1 <= 9) && (blocks[3].Get_X() + 1 <= 9))
			return ((matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == 0) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 2)
	{
		if ((blocks[0].Get_X() + 1 <= 9) && (blocks[3].Get_X() + 1 <= 9))
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == 0) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 22)
	{
		if (blocks[0].Get_X() + 1 <= 9)
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == 0) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == 0) && (matrix[blocks[2].Get_X() + 1][blocks[2].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 22)
	{
		if ((blocks[0].Get_X() + 1 <= 9) && (blocks[3].Get_X() + 1 <= 9))
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == 0) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 23)
	{
		if (blocks[0].Get_X() + 1 <= 9)
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == 0) && (matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 24)
	{
		if ((blocks[0].Get_X() + 1 <= 9)&& (blocks[3].Get_X() + 1 <= 9)&& (blocks[1].Get_X() + 1 <= 9))
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == 0) && (matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == 0)&&(matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 3)
	{
		if (blocks[3].Get_X() + 1 <= 9)
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == 0) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 32)
	{
		if (blocks[2].Get_X() + 1 <= 9)
			return ((matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == 0) && (matrix[blocks[2].Get_X() + 1][blocks[2].Get_Y()] == 0) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 33)
	{
		if (blocks[2].Get_X() + 1 <= 9)
			return ((matrix[blocks[2].Get_X() + 1][blocks[2].Get_Y()] == 0) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 34)
	{
		if (blocks[2].Get_X() + 1 <= 9)
			return ((matrix[blocks[2].Get_X() + 1][blocks[2].Get_Y()] == 0) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == 0) && (matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
	else if (type == 4)
	{
		if (blocks[3].Get_X() + 1 <= 9)
			return (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == 0) ? true : false;
		else
			return false;
	}
	else if (type == 42)
	{
		if (blocks[3].Get_X() + 1 <= 9)
			return ((matrix[blocks[0].Get_X() + 1][blocks[0].Get_Y()] == 0) &&(matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == 0) && (matrix[blocks[2].Get_X() + 1][blocks[2].Get_Y()] == 0) &&(matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == 0)) ? true : false;
		else
			return false;
	}
}

bool Game::check_collision(int type)
{
	if (type == 2)
		return ((blocks[0].Get_X()+1>=0) && (matrix[blocks[0].Get_X()+1][blocks[0].Get_Y()+1] == 0) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y() + 1] == 0) && (matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == 0)) ? true : false;
	else if (type == 21)
		return ((blocks[1].Get_Y()-2>=0) && (matrix[blocks[1].Get_X()][blocks[1].Get_Y() - 2] == 0)) ? true : false;
	else if (type == 22)
		return ((blocks[2].Get_X()+2<=9)&&(matrix[blocks[3].Get_X()+1][blocks[3].Get_Y()+1]==0)&&(matrix[blocks[0].Get_X()+1][blocks[0].Get_Y()-1])==0) ? true : false;
	else if (type == 23)
		return ((blocks[2].Get_Y() - 1 >= 0) && (blocks[3].Get_Y() - 1 >= 0) && (matrix[blocks[1].Get_X() + 1][blocks[1].Get_Y()] == 0) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() - 1] == 0) && (matrix[blocks[0].Get_X()-1][blocks[0].Get_Y() - 1] == 0)) ? true : false;
	else if (type == 31)
		return ((blocks[0].Get_Y() - 1 >= 0) && (matrix[blocks[0].Get_X()][blocks[0].Get_Y()-1] == 0) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y() - 2] == 0)) ? true : false;
	else if (type == 32)
		return ((blocks[2].Get_X() + 1 <= 9) && (matrix[blocks[1].Get_X()+1][blocks[1].Get_Y()] == 0) && (matrix[blocks[3].Get_X()+2][blocks[3].Get_Y()] == 0) && (matrix[blocks[2].Get_X() + 1][blocks[2].Get_Y()+1] == 0)) ? true : false;
	else if (type == 33)
		return ((blocks[2].Get_Y() - 1 >= 0) && (matrix[blocks[2].Get_X()][blocks[2].Get_Y()-1] == 0) && (matrix[blocks[3].Get_X() + 1][blocks[3].Get_Y()] == 0)) ? true : false;
	else if (type == 3)
		return ((blocks[1].Get_X() - 1 >= 0) && (matrix[blocks[2].Get_X()-2][blocks[2].Get_Y()] == 0) && (matrix[blocks[1].Get_X() - 1][blocks[1].Get_Y()] == 0)) ? true : false;
	else if (type == 41)
		return ((blocks[3].Get_Y() + 3 <= 19) && (matrix[blocks[0].Get_X()][blocks[0].Get_Y()+1] == 0) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y()+2] == 0) && (matrix[blocks[3].Get_X()][blocks[3].Get_Y() + 3] == 0)) ? true : false;
	else if (type == 4)
		return ((blocks[0].Get_X() + 3 <= 9) && (matrix[blocks[0].Get_X()+1][blocks[0].Get_Y()] == 0) && (matrix[blocks[0].Get_X()+2][blocks[0].Get_Y()] == 0) && (matrix[blocks[0].Get_X()+3][blocks[0].Get_Y()] == 0)) ? true : false;
}

Game::~Game(){}