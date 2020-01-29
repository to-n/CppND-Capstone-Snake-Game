#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
  : _screen_width(screen_width),
    _screen_height(screen_height),
    _grid_width(grid_width),
    _grid_height(grid_height) {

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  _sdl_window = std::shared_ptr<SDL_Window>(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
							    SDL_WINDOWPOS_CENTERED, _screen_width,
							    _screen_height, SDL_WINDOW_SHOWN),
					   [](SDL_Window* sdlw){SDL_DestroyWindow(sdlw);});

  if (nullptr == _sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  _sdl_renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(_sdl_window.get(), -1, SDL_RENDERER_ACCELERATED),
					       [](SDL_Renderer* sdlr){SDL_DestroyRenderer(sdlr);});
  if (nullptr == _sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

}

Renderer::Renderer(Renderer& source) :
  _screen_width(source._screen_width),
  _screen_height(source._screen_height),
  _grid_width(source._grid_width),
  _grid_height(source._grid_height) {

  // Create window
  _sdl_window = std::shared_ptr<SDL_Window>(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
							    SDL_WINDOWPOS_CENTERED, _screen_width,
							    _screen_height, SDL_WINDOW_SHOWN),
					   [](SDL_Window* sdlw){SDL_DestroyWindow(sdlw);});

  // Create renderer
  _sdl_renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(_sdl_window.get(), -1, SDL_RENDERER_ACCELERATED),
					       [](SDL_Renderer* sdlr){SDL_DestroyRenderer(sdlr);});
  if (nullptr == _sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  } 

}

Renderer& Renderer::operator=(Renderer& source) {

  _screen_width = source._screen_width;
  _screen_height = source._screen_height;
  _grid_width = source._grid_width;
  _grid_height = source._grid_height;  

  // Create window
  _sdl_window = std::shared_ptr<SDL_Window>(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
							    SDL_WINDOWPOS_CENTERED, _screen_width,
							    _screen_height, SDL_WINDOW_SHOWN),
					   [](SDL_Window* sdlw){SDL_DestroyWindow(sdlw);});

  // Create renderer
  _sdl_renderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer(_sdl_window.get(), -1, SDL_RENDERER_ACCELERATED),
					       [](SDL_Renderer* sdlr){SDL_DestroyRenderer(sdlr);});
  if (nullptr == _sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  return *this;
}

Renderer::Renderer(Renderer&& source) {

  _screen_width = source._screen_width;
  source._screen_width = 0;

  _screen_height = source._screen_height;
  source._screen_height = 0;

  _grid_width = source._grid_width;
  source._grid_width = 0;

  _grid_height = source._grid_height;
  source._grid_height = 0;    
  
  _sdl_window = std::move(source._sdl_window);
  source._sdl_window = nullptr;

  _sdl_renderer = std::move(source._sdl_renderer);
  source._sdl_renderer = nullptr;  

}

Renderer& Renderer::operator=(Renderer&& source) {

  if (this == &source) {
    return *this;
  }
  
  _screen_width = source._screen_width;
  source._screen_width = 0;

  _screen_height = source._screen_height;
  source._screen_height = 0;

  _grid_width = source._grid_width;
  source._grid_width = 0;

  _grid_height = source._grid_height;
  source._grid_height = 0;    
  
  _sdl_window = std::move(source._sdl_window);
  source._sdl_window = nullptr;

  _sdl_renderer = std::move(source._sdl_renderer);
  source._sdl_renderer = nullptr;

  return *this;
}

Renderer::~Renderer() {
  SDL_DestroyWindow(_sdl_window.get());
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {

  SDL_Rect block;
  block.w = _screen_width / _grid_width;
  block.h = _screen_height / _grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(_sdl_renderer.get(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_sdl_renderer.get());

  // Render food
  SDL_SetRenderDrawColor(_sdl_renderer.get(), 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(_sdl_renderer.get(), &block);

  // Render snake's body
  SDL_SetRenderDrawColor(_sdl_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake._body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(_sdl_renderer.get(), &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake._head_x) * block.w;
  block.y = static_cast<int>(snake._head_y) * block.h;
  if (snake._alive) {
    SDL_SetRenderDrawColor(_sdl_renderer.get(), 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(_sdl_renderer.get(), 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(_sdl_renderer.get(), &block);

  // Update Screen
  SDL_RenderPresent(_sdl_renderer.get());

}

void Renderer::UpdateWindowTitle(int score, int fps) {

  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(_sdl_window.get(), title.c_str());

}
