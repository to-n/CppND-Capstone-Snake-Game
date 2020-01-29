# CPPND: Capstone - Snake vs. the Coffee-Drinking Fly

This was forked from is the starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

## Game Description
In this variation on the classic Snake game, the "apple" is now a coffee-drinking fly.

On game start, at the command line prompt, enter the amount of coffee the fly will drink.

At the game window that appears, enjoy trying to catch a wired AF fly using the arrow keys.

To exit, press Ctrl+C at the command line prompt, or simply close the game window.

## Program Structure
main.cpp instantiates Renderer (draws the graphics based on game state), Controller (interprets user input to manipulate game state), and Game (stores game state), leveraging the SDL library.

## Project Rubric Points Addressed
* Loops, Functions, I/O
  * The project demonstrates an understanding of C++ functions and control structures.
    * See main() and Game::FoodRoute() for examples.
  * The project accepts user input and processes the input.
    * See main() for user menu.
* Memory Management
  * The project follows the Rule of 5.
    * See Renderer class constructors and destructor.
  * The project uses smart pointers instead of raw pointers.
    * SDL object pointers in Renderer class were converted to shared pointers.
* Concurrency
  * The project uses multithreading.
    * Main thread is in main(), and a separate thread created in Game::Run manages the movement of the fly.
  * A mutex or lock is used in the project.
    * In the thread that manages fly movement, a lock is used to protect Game instance member variables shared across threads.
    
## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.