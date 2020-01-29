#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  int repositionDelay = -1;
  
  std::cout << "Welcome to Snake vs. the Coffee-Drinking Fly" << std::endl;
  while (true) {

    std::cout << "How much coffee will the fly drink? (0 to 1000): " << std::endl;  
    std::cin >> repositionDelay;
    if (repositionDelay >= 0 && repositionDelay <= 1000) {
      // Caffiene scale is maps to "opposite" of repositionDelay scale
      // 0 -> 1000, 1000 -> 0
      repositionDelay = repositionDelay * -1 + 1000;
      break;
    }
  }  

  std::cout << "Happy Fly-Catching!" << std::endl;
  
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, repositionDelay);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}
