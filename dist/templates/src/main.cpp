#include <Tank/System/Game.hpp>
#include "MainWorld.hpp"

int main()
{
    tank::Game::initialize({800,600});
    tank::Game::makeWorld<MainWorld>();
    tank::Game::run();
}

