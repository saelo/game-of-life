/*
 * GameOfLife.h
 *
 *  Created on: Jun 13, 2012
 *      Author: Samuel Groß
 */

#ifndef GAMEOFLIFE_H_
#define GAMEOFLIFE_H_

#include "view.h"

/*
 * This class implements the core logic for the game of life.
 */
class GameOfLife
{
public:
    static const int MAX_HEALTH;

    GameOfLife(int w, int h);

    void run();
    void calcNextGeneration();

    void addView(View* v);
    int** getWorld();

private:
    int height;
    int width;
    bool running;
    int generations;
    int** world;
    int** tmpWorld;
    View* view;

    void populate();
    int getNeighborCount(int x, int y);
    inline bool isAlive(int x, int y);
};


#endif /* GAMEOFLIFE_H_ */
