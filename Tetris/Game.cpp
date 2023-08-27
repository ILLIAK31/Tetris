#include "Game.hpp"

Game::Game(const int _width, const int _height,
	const int _tile_size, const int _screen_size,
	const float _vertical_boost,
	const sf::Time _horizontal_movement_interval,
	const sf::Time _vertical_movement_initial_interval,
	const sf::Time _min_vertical_movement_interval,
	const sf::Time _d_vertical_movement_interval_per_fall,
	const int _score_per_row) :
	window(),
	tiles(std::make_shared<Tiles_Matrix>(Tiles_Matrix(_width, _height))),
	tile_size(_tile_size),
	screen_size(_screen_size),
	vertical_boost(_vertical_boost),
	horizontal_movement_interval(_horizontal_movement_interval),
	vertical_movement_interval(_vertical_movement_initial_interval),
	min_vertical_movement_interval(_min_vertical_movement_interval),
	d_vertical_movement_interval_per_fall(_d_vertical_movement_interval_per_fall),
	score_per_row(_score_per_row),
	random(std::random_device{}()) 
{
	Icon.loadFromFile("Icon.png");
}

int Game::Get_Score() const
{
	return score;
}

void Game::Set_Score(const int value) 
{
	score = value;
	window.setTitle("Tetris. Score: " + std::to_string(score));
}

bool Game::Run()
{
	window.create(sf::VideoMode(
		tile_size * tiles->Width() * screen_size, 
		tile_size * tiles->Height() * screen_size),
		"Tetris");
	window.setKeyRepeatEnabled(false);
	window.setIcon(47, 47, Icon.getPixelsPtr());
	Start();
	Render();

	sf::Clock clock;
	while (window.isOpen())
	{
		ProcessInput();
		if (Update(clock.restart()))
			Render();
	}

	return game_over;
}

void Game::Start()
{
	// Default game state.
	game_over = false;
	Set_Score(0);
	horizontal_direction = 0;
	boost_active = rotation_requested = false;

	current_horizontal_movement_interval = horizontal_movement_interval;
	current_vertical_movement_interval = vertical_movement_interval;
	horizontal_movement_clock.restart();
	vertical_movement_clock.restart();

	tiles->Reset();

	SpawnTetromino();
}

void Game::ProcessInput()
{
	sf::Event Event;
	while (window.pollEvent(Event))
	{
		switch (Event.type)
		{
		case sf::Event::KeyPressed:
			if (Event.key.code == sf::Keyboard::Up && window.hasFocus()) 
				rotation_requested = true;
			break;
		case sf::Event::LostFocus:
			horizontal_direction = 0;
			boost_active = rotation_requested = false;
			break;
		case sf::Event::Closed:
			window.close();
			return;
		}
	}
	if (window.hasFocus())
	{
		// Left/right direction
		int new_direction = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			new_direction--;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			new_direction++;
		horizontal_direction = new_direction;

		// Vertical boost
		boost_active = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	}
}

bool Game::Update(const sf::Time delta_time)
{
	bool needs_render = false;

	// Vertical movement
	float vertical_s = vertical_movement_clock.getElapsedTime().asSeconds();
	float vertical_interval_s = boost_active ?
		vertical_movement_interval.asSeconds() / vertical_boost :
		current_vertical_movement_interval.asSeconds();
	if (vertical_s >= vertical_interval_s)
	{
		// Check whether our tetromino has landed
		if (!falling_tetromino.Try_Move(0, 1))
		{
			// Increase game speed
			current_vertical_movement_interval -= d_vertical_movement_interval_per_fall;
			// Restrict game speed
			if (current_vertical_movement_interval < min_vertical_movement_interval)
			{
				current_vertical_movement_interval = min_vertical_movement_interval;
			}

			// Remove rows
			RemoveRows();
			// Spawn a new tetromino
			SpawnTetromino();
		}
		// Either block was moved down or a new tetromino was spawned
		needs_render = true;

		vertical_movement_clock.restart();
	}
	// Horizontal movement
	if (horizontal_movement_clock.getElapsedTime() >= current_horizontal_movement_interval)
	{
		if (horizontal_direction != 0 && falling_tetromino.Try_Move(horizontal_direction, 0))
		{
			current_horizontal_movement_interval = horizontal_movement_interval;
			needs_render = true;
		}
		else
		{
			// Remove delay for the first key press
			current_horizontal_movement_interval = sf::milliseconds(0);
		}

		horizontal_movement_clock.restart();
	}
	// Rotation
	if (rotation_requested)
	{
		if (falling_tetromino.Try_Rotate())
		{
			needs_render = true;
		}
		rotation_requested = false;
	}

	return needs_render;
}

void Game::Render()
{
#pragma warning( push )
#pragma warning( disable : 4244) // conversion from 'int' to 'float', possible loss of data 

	window.clear();
	window.setSize(sf::Vector2u(
		tile_size * tiles->Width() * screen_size, tile_size * tiles->Height() * screen_size));
	window.setView(sf::View(sf::FloatRect(0, 0, tile_size * tiles->Width(), tile_size * tiles->Height())));
	sf::RectangleShape cell(sf::Vector2f(tile_size - 1, tile_size - 1));
	for (int col = 0; col < tiles->Width(); ++col)
		for (int row = 0; row < tiles->Height(); ++row)
		{
			cell.setFillColor(TileToColor((*tiles)[col][row]));
			cell.setPosition(tile_size * col, tile_size * row);
			window.draw(cell);
		}
	window.display();

#pragma warning(pop) // conversion from 'int' to 'float', possible loss of data 
}

void Game::SpawnTetromino()
{
	std::uniform_int_distribution<int> dist(1, 7);

	// Choose a random tetromino
	falling_tetromino = Tetromino::Create_Random(random, tiles);
	// Determine its starting position
	int min_x = INT_MAX, max_x = INT_MIN, min_y = INT_MAX;
	const auto& tetromino_state = falling_tetromino.Get_Current_State();
	for (auto point : tetromino_state)
	{
		if (point.x < min_x) min_x = point.x;
		if (point.x > max_x) max_x = point.x;
		if (point.y < min_y) min_y = point.y;
	}
	
	int tetromino_width = (max_x - min_x + 1);
	int x = (tiles->Width() - tetromino_width) / 2, y = -min_y;
	if (!falling_tetromino.Try_Place(x, y))
	{
		// Losing condition of the game has been met
		EndGame();
	}
}

void Game::RemoveRows()
{
	std::vector<int> rows;
	for (int row = tiles->Height() - 1; row >= 0; --row)
	{
		// Check whether row can be removed
		bool canBeRemoved = true;
		for (int col = 0; col < tiles->Width(); ++col)
		{
			if ((*tiles)[col][row] == Tile::Empty)
			{
				canBeRemoved = false;
				break;
			}
		}
		if (canBeRemoved)
		{
			// Remove row
			for (int col = 0; col < tiles->Width(); ++col)
				(*tiles)[col][row] = Tile::Empty;
			// Add score for row removal
			Set_Score(score + score_per_row);

			rows.push_back(row);
		}
	}
	// Move rows down
	for (int l = 0; l < rows.size(); ++l)
		for (int col = 0; col < tiles->Width(); ++col)
			for (int row = rows[0]; row > 0; --row)
				(*tiles)[col][row] = (*tiles)[col][row - 1];
}

void Game::EndGame()
{
	game_over = true;
	window.close();
}

Game::~Game() {}
