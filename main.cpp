/*
 * Main.cpp
 *
 *  Created on: Jun 14, 2012
 *      Author: Samuel Groß <dev@samuel-gross.de>
 */

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <time.h>

#include "gofl.h"

using namespace std;


int screenWidth  = 1280;
int screenHeight = 800;
const bool fullscreen  = true;

const int creatureSize = 1;
const int borderSize   = 1;

long start  = 0;
long frames = 0;

GameOfLife* gol = NULL;
View* view = NULL;


void resize(int w, int h) {
    view->resize(w, h);
}

void renderFunction() {
    gol->calcNextGeneration();
    glutSwapBuffers();
    frames++;
}

void printFPS() {
    long ticks = clock() - start;
    double seconds = ((double) ticks) / CLOCKS_PER_SEC;
    double fps = frames / seconds;
    cout << "fps: " << fps << endl;
}

void key(unsigned char k, int x, int y) {
    printFPS();
    exit(0);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);

    view = new View();
    if (fullscreen) {
        screenWidth  = glutGet(GLUT_SCREEN_WIDTH);
        screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    }

    int worldWidth  = screenWidth / (creatureSize + borderSize);
    int worldHeight = screenHeight / (creatureSize + borderSize);

    cout << "\n------------------------------" << endl;
    cout << "Game of Life by saelo" << endl;
    cout << "------------------------------\n" << endl;
    cout << "Screen Dimensions: " << screenWidth << " x " << screenHeight << endl;
    cout << "Creature Size: " << creatureSize << endl;
    cout << "Living Space Dimensions: " << worldWidth << " x " << worldHeight << endl;

    gol = new GameOfLife(worldWidth, worldHeight);
    gol->addView(view);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Game of Life C++");
    glutDisplayFunc(renderFunction);
    glutIdleFunc(renderFunction);
    glutKeyboardFunc(key);

    glutSetCursor(GLUT_CURSOR_NONE);

    if (fullscreen) {
        glutFullScreen();
    }

    view->init(screenWidth, screenHeight, worldWidth, worldHeight, creatureSize, borderSize);

    start = clock();

    glutMainLoop();
    return 0;
}


