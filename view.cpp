#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include "view.h"

using namespace std;


void View::init(int screenW, int screenH, int worldW, int worldH)
{
    worldWidth   = worldW;
    worldHeight  = worldH;

    glClearColor(0.0, 0.0, 0.0, 0.0);

    // enable transparency
    glEnable(GL_BLEND);

    // the type of transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    resize(screenW, screenH);
}


void View::resize(int width, int height)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -6.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void View::draw(int** world)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0, 0.0, 3.0);

    glBegin(GL_QUADS);
    for (int column = 0; column < worldWidth; column++) {
        for (int row = 0; row < worldHeight; row++) {
            int health = world[column][row];
            if (health > 1) {
                float healthStatus = (float) health / 1000.0;
                // the color depends on the health status
                glColor4f(1.0, 0.5, 0.0, healthStatus);

                int x = column * (CREATURE_SIZE + BORDER_SIZE);
                int y = row * (CREATURE_SIZE + BORDER_SIZE);
                glVertex3f(x                , y                , 0.0);
                glVertex3f(x + CREATURE_SIZE, y                , 0.0);
                glVertex3f(x + CREATURE_SIZE, y + CREATURE_SIZE, 0.0);
                glVertex3f(x                , y + CREATURE_SIZE, 0.0);
            }
        }
    }
    glEnd();
}
