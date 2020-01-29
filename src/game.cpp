#include "game.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, std::size_t repositionDelay)
  : _snake(grid_width, grid_height), _repositionDelay(repositionDelay),
    _engine(_dev()),
    _random_w(0, static_cast<int>(grid_width)),
    _random_h(0, static_cast<int>(grid_height)) {
}

void Game::FoodRoute() {
  int x, y;

  std::lock_guard<std::mutex> lockGuard(_mutex);

  // Unleash the fly
  // Loop until unoccupied cell is found
  while (true) {
    x = _random_w(_engine);
    y = _random_h(_engine);
    
      if (x > _food.x) {
	x = _food.x + 1;
      } else if (x < _food.x) {
	x = _food.x - 1;
      } else {
	x = _food.x;
      }

      if (y > _food.y) {
	y = _food.y + 1;
      } else if (y < _food.y) {
	y = _food.y - 1;
      } else {
	y = _food.y;
      }      

    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!_snake.SnakeCell(x, y)) {
      _food.x = x;
      _food.y = y;
      return;
    }
  }
}
  
void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {

  // Initial food (fly) placement
  PlaceFood();

  // Separate thread handles movement of food (fly)
  std::thread t([this]() {
		  while (_running) {
		    std::this_thread::sleep_for(std::chrono::milliseconds(_repositionDelay));
		    FoodRoute();
		  }
		});

  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  Uint32 frame_count = 0;
  _running = true;

  while (_running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(_running, _snake);
    Update();
    renderer.Render(_snake, _food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(_score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  t.join();
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = _random_w(_engine);
    y = _random_h(_engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!_snake.SnakeCell(x, y)) {
      _food.x = x;
      _food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!_snake._alive) return;

  _snake.Update();

  int new_x = static_cast<int>(_snake._head_x);
  int new_y = static_cast<int>(_snake._head_y);

  // Check if there's food over here
  if (_food.x == new_x && _food.y == new_y) {
    _score++;
    PlaceFood();
    // Grow snake and increase speed.
    _snake.GrowBody();
    _snake._speed += 0.02;
  }
}

int Game::GetScore() const { return _score; }
int Game::GetSize() const { return _snake._size; }
