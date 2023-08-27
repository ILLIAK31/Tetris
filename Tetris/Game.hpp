#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include "Tetromino.hpp"
#include "Tiles_Matrix.hpp"

class Game
{
public:
	/// <summary>
	/// Create a game.
	/// </summary>
	/// <param name="_width">Width of the tiles grid.</param>
	/// <param name="_height">Height of the tiles grid.</param>
	/// <param name="_tile_size">Size of the tile.</param>
	/// <param name="_screen_size">Additional modifier for the screen size.</param>
	/// <param name="_vertical_boost">Boost from holding DOWN button.</param>
	/// <param name="_horizontal_movement_interval">Interval which is used when updating horizontal position.</param>
	/// <param name="_vertical_movement_initial_interval">Interval which is used when updating vertical position.</param>
	/// <param name="_min_vertical_movement_interval">Minimal vertical interval.</param>
	/// <param name="_d_vertical_movement_interval_per_fall">Value that is substracted from the vertical movement interval when tetromino falls.</param>
	/// <param name="_score_per_row">Score that is added when one row is removed.</param>
	Game(const int _width = 10, const int _height = 20, 
		const int _tile_size = 9, const int _screen_size = 4,
		const float _vertical_boost = 10.f,
		const sf::Time _horizontal_movement_interval = sf::milliseconds(125),
		const sf::Time _vertical_movement_initial_interval = sf::milliseconds(700),
		const sf::Time _min_vertical_movement_interval = sf::milliseconds(700),
		const sf::Time _d_vertical_movement_interval_per_fall = sf::milliseconds(10),
		const int _score_per_row = 40
		);

	/// <summary>
	/// Start the game.
	/// </summary>
	/// <returns>
	/// true if game was ended by losing; false otherwise.
	/// </returns>
	bool Run();
	
	int Get_Score() const;

	~Game();
private:
	sf::RenderWindow window;
	sf::Image Icon;
	
	void Set_Score(const int value);

	/// <summary>
	/// Method that is called when game is started. 
	/// Responsible for the initialization of the game.
	/// </summary>
	void Start();
	/// <summary>
	/// Method that is called each frame. Responsible for input reading.
	/// </summary>
	void ProcessInput();
	/// <summary>
	/// Method that is called each frame. Responsible for game logic.
	/// </summary>
	/// <param name="delta_time">
	/// Interval from the last frame to the current one.
	/// </param>
	/// <returns>
	/// true if the frame should be re-rendered;
	/// false otherwise.
	/// </returns>
	bool Update(const sf::Time delta_time);
	/// <summary>
	/// Method that is responsible for the rendering of the game grid.
	/// </summary>
	void Render();
	/// <summary>
	/// Method that ends game by losing.
	/// </summary>
	void EndGame();

	void SpawnTetromino();
	void RemoveRows();

	int score{0};
	std::shared_ptr<Tiles_Matrix> tiles;
	Tetromino falling_tetromino;
	std::mt19937 random;

	sf::Clock horizontal_movement_clock;
	sf::Clock vertical_movement_clock;

	sf::Time horizontal_movement_interval;
	sf::Time current_horizontal_movement_interval;

	sf::Time vertical_movement_interval;
	sf::Time current_vertical_movement_interval;
	sf::Time min_vertical_movement_interval;
	sf::Time d_vertical_movement_interval_per_fall;

	bool game_over{ false };

	bool rotation_requested{ false };
	bool boost_active;
	int horizontal_direction{ 0 };

	int tile_size, screen_size;
	int score_per_row;

	float vertical_boost;
};
