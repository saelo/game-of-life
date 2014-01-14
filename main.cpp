#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <time.h>

#include "game.h"
#include "view.h"

using namespace std;


int screenWidth  = 1280;
int screenHeight = 800;
const bool fullscreen  = true;

long start  = 0;
long frames = 0;

GameOfLife* game = NULL;
View* view = NULL;


void resize(int w, int h)
{
    view->resize(w, h);
}

void renderFunction()
{
    game->nextGeneration();
    view->draw(game->getWorld());
    glutSwapBuffers();
    frames++;
}

void stats()
{
    long ticks = clock() - start;
    double seconds = ((double) ticks) / CLOCKS_PER_SEC;
    double fps = frames / seconds;
    cout << "fps: " << fps << endl;
    cout << game->numGenerations() << " generations" << endl;
}

void onKey(unsigned char k, int x, int y)
{
    stats();
    exit(0);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    view = new View();
    if (fullscreen) {
        screenWidth  = glutGet(GLUT_SCREEN_WIDTH);
        screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    }

    int worldWidth  = screenWidth / (View::CREATURE_SIZE + View::BORDER_SIZE);
    int worldHeight = screenHeight / (View::CREATURE_SIZE + View::BORDER_SIZE);

    cout << "------------------------------" << endl;
    cout << "Game of Life by saelo" << endl;
    cout << "------------------------------" << endl << endl;
    cout << "Screen Dimensions: " << screenWidth << " x " << screenHeight << endl;
    cout << "Creature Size: " << View::CREATURE_SIZE << endl;
    cout << "Living Space Dimensions: " << worldWidth << " x " << worldHeight << endl;

    game = new GameOfLife(worldWidth, worldHeight);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Game of Life C++");
    glutDisplayFunc(renderFunction);
    glutIdleFunc(renderFunction);
    glutKeyboardFunc(onKey);

    glutSetCursor(GLUT_CURSOR_NONE);

    if (fullscreen)
        glutFullScreen();

    view->init(screenWidth, screenHeight, worldWidth, worldHeight);

    start = clock();

    glutMainLoop();
    return 0;
}
