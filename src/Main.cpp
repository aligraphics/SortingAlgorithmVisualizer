#include "Renderer.hpp"

#include <ctime>

int main()
{
    srand(time(0));
    Renderer renderer(1600, 900, "Sorting Algorithm Visualizer");
    renderer.InitWindow();
    renderer.Loop();
    return 0;
}