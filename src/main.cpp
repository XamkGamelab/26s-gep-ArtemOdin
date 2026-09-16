#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "game.hpp"

int main(int argc, char** argv)
{
    //std::cout << "GEP 26S" << std::endl;

    gep::game g{};

    auto init_succesful = g.init();

    if (init_succesful)
    {
        g.run();
    }
    

    g.shutdown();
    

    return 0;
}