#include <cstdlib>
#include <iostream>
#include <time.h>

#include "game.h"

using namespace std;



inline int mod(int a, int b)
{
    int c = a % b;
    if (c < 0)
        return c + b;
    else
        return c;
}


GameOfLife::GameOfLife(int w, int h)
{
    width  = w;
    height = h;
    generation = 0;

    // initialize random seed
    srand(time(NULL));

    populate();
}

void GameOfLife::nextGeneration()
{
    int neighbors = 0;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            neighbors = getNeighborCount(x, y);
            tmpWorld[x][y] = world[x][y];

            if (neighbors >= 2 && neighbors <= 3) {
                if (neighbors == 3) {
                    // birth of a new creature
                    tmpWorld[x][y] = MAX_HEALTH;
                }
            } else if (tmpWorld[x][y] == MAX_HEALTH) {
                // mark creature as dead
                tmpWorld[x][y] = tmpWorld[x][y] / 1.1;
            }
            // slow death of creatures
            if (tmpWorld[x][y] > 0 && tmpWorld[x][y] < MAX_HEALTH)
                tmpWorld[x][y] = tmpWorld[x][y] / 1.1;
        }
    }

    int** tmp = world;
    world = tmpWorld;
    tmpWorld = tmp;

    generation++;
}

int** GameOfLife::getWorld()
{
    return world;
}

long GameOfLife::numGenerations()
{
    return generation;
}

void GameOfLife::populate()
{
    world = (int**) malloc(width * sizeof(int*));
    tmpWorld = (int**) malloc(width * sizeof(int*));

    for (int x = 0; x < width; x++) {
        world[x] = (int*) malloc(height * sizeof(int));
        tmpWorld[x] = (int*) malloc(height * sizeof(int*));
        for (int y = 0; y < height; y++) {
            int randInt = rand() % 2;
            if (randInt == 1)
                world[x][y] = MAX_HEALTH;
            else
                world[x][y] = 0;
        }
    }
}

int GameOfLife::getNeighborCount(int x, int y)
{
    int count = 0;

    int xpn = mod((x + 1), width);
    int ypn = mod((y + 1), height);
    int xnn = mod((x - 1), width);
    int ynn = mod((y - 1), height);

    count += isAlive(x  , ypn);
    count += isAlive(xpn, ypn);
    count += isAlive(xpn, y);
    count += isAlive(xpn, ynn);
    count += isAlive(x  , ynn);
    count += isAlive(xnn, ynn);
    count += isAlive(xnn, y);
    count += isAlive(xnn, ypn);

    return count;
}


bool GameOfLife::isAlive(int x, int y)
{
    return world[x][y] == MAX_HEALTH;
}
