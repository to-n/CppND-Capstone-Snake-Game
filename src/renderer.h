#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);

  // Copy Constructor
  Renderer(Renderer& source);

  // Copy Assignment Constructor
  Renderer& operator=(Renderer& source);

  // Move Constructor
  Renderer(Renderer&& source);

  // Move Assignment Operator
  Renderer& operator=(Renderer&& source); 
  
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);

 private:
  std::shared_ptr<SDL_Window> _sdl_window;
  std::shared_ptr<SDL_Renderer> _sdl_renderer;

  std::size_t _screen_width;
  std::size_t _screen_height;
  std::size_t _grid_width;
  std::size_t _grid_height;
};

#endif
