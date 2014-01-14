#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H


class GameOfLife {
public:
    static const int MAX_HEALTH = 1000;

    GameOfLife(int w, int h);

    void nextGeneration();
    bool isAlive(int x, int y);

    int** getWorld();
    long numGenerations();

private:
    int height, width;
    long generation;
    int** world;
    int** tmpWorld;

    void populate();
    int getNeighborCount(int x, int y);
};

#endif
