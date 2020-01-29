#ifndef GAME_H
#define GAME_H

#include <random>
#include <mutex>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
public:
  Game(std::size_t grid_width, std::size_t grid_height, std::size_t repositionDelay);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

private:
  Snake _snake;
  SDL_Point _food;

  std::random_device _dev;
  std::mt19937 _engine;
  std::uniform_int_distribution<int> _random_w;
  std::uniform_int_distribution<int> _random_h;

  std::mutex _mutex;
  bool _running;
  int _repositionDelay; // in ms

  int _score{0};
  void FoodRoute();
  void PlaceFood();
  void Update();
};

#endif
