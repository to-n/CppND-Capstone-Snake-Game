#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : _grid_width(grid_width),
        _grid_height(grid_height),
        _head_x(grid_width / 2),
        _head_y(grid_height / 2)
        {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction _direction = Direction::kUp;

  float _speed{0.1f};
  int _size{1};
  bool _alive{true};
  float _head_x;
  float _head_y;
  std::vector<SDL_Point> _body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool _growing{false};
  int _grid_width;
  int _grid_height;
};

#endif
