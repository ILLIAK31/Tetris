#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <iostream>

int main()
{
	Game game;
	if (game.Run())
	{
		std::cout << "GAME OVER!" << std::endl << "Score : " << game.Get_Score() << std::endl;
		system("pause");
	}
	return 0;
}