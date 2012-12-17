/*
 * GameOfLife.cpp
 *
 *  Created on: Jun 13, 2012
 *      Author: Samuel Groß
 */

#include <cstdlib>
#include <iostream>
#include <time.h>

#include "gofl.h"

using namespace std;


const int GameOfLife::MAX_HEALTH = 1000;


inline int mod(int a, int b) {
    int c = a % b;
    if (c < 0) {
        return c + b;
    }
    else {
        return c;
    }
}



GameOfLife::GameOfLife(int w, int h) {
    this->width  = w;
    this->height = h;

    // initialize random seed
    srand(time(NULL));

    this->populate();

}

void GameOfLife::run() {
    this->running = true;
    while (running) {
        calcNextGeneration();
    }
}

void GameOfLife::calcNextGeneration() {
    int neighbors = 0;
    for (int x = 0; x < this->width; x++) {
        for (int y = 0; y < this->height; y++) {
            neighbors = getNeighborCount(x, y);
            this->tmpWorld[x][y] = this->world[x][y];

            if (neighbors >= 2 && neighbors <= 3) {
                if (neighbors == 3) {
                    // birth of a new creature
                    this->tmpWorld[x][y] = this->MAX_HEALTH;
                }
            } else if (this->tmpWorld[x][y] == this->MAX_HEALTH) {    
                // mark creature as dead
                this->tmpWorld[x][y] = this->tmpWorld[x][y] / 1.1;
            }
            // slow death of creatures
            if (this->tmpWorld[x][y] > 0 && this->tmpWorld[x][y] < this->MAX_HEALTH) {    // delete
                this->tmpWorld[x][y] = this->tmpWorld[x][y] / 1.1;
            }
        }
    }

    int** tmp = this->world;
    this->world = this->tmpWorld;
    this->tmpWorld = tmp;

    this->generations++;

    if (this->view != NULL) {
        this->view->update(this->world);
    }
}

void GameOfLife::addView(View* v) {
    this->view = v;
}

int** GameOfLife::getWorld() {
    return this->world;
}

void GameOfLife::populate() {
    this->world = (int**) malloc(this->width * sizeof(int*));
    this->tmpWorld = (int**) malloc(this->width * sizeof(int*));

    for (int x = 0; x < this->width; x++) {
        this->world[x] = (int*) malloc(this->height * sizeof(int));
        this->tmpWorld[x] = (int*) malloc(this->height * sizeof(int*));
        for (int y = 0; y < this->height; y++) {
            int randInt = rand() % 2;
            if (randInt == 1) {
                this->world[x][y] = this->MAX_HEALTH;
            }
            else {
                this->world[x][y] = 0;
            }
        }
    }
}

inline int GameOfLife::getNeighborCount(int x, int y) {
    int count = 0;

    int xpn = mod((x + 1), this->width);
    int ypn = mod((y + 1), this->height);
    int xnn = mod((x - 1), this->width);
    int ynn = mod((y - 1), this->height);

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


inline bool GameOfLife::isAlive(int x, int y) {
    return this->world[x][y] == this->MAX_HEALTH;
}



