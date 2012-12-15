/*
 * View.cpp
 *
 *  Created on: Jun 14, 2012
 *      Author: Samuel Groß
 */

#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>

#include "view.h"

using namespace std;

View::View() {
    // TODO Auto-generated constructor stub
}

View::~View() {
    // TODO Auto-generated destructor stub
}

void View::init(int screenW, int screenH, int worldW, int worldH, int creatureSize, int borderSize) {
    this->creatureSize = creatureSize;
    this->borderSize   = borderSize;
    this->worldWidth   = worldW;
    this->worldHeight  = worldH;

    glClearColor(0.0, 0.0, 0.0, 0.0);
    // enable transparency
    glEnable(GL_BLEND);
    // the type of transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    this->resize(screenW, screenH);
}


void View::resize(int width, int height) {
    if (height == 0) {
        height = 1;
    }
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -6.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void View::draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0, 0.0, 3.0);

    glBegin(GL_QUADS);
    for (int column = 0; column < this->worldWidth; column++) {
        for (int row = 0; row < this->worldHeight; row++) {
            int health = this->world[column][row];
            if (health > 1) {
                float healthStatus = (float) health / 1000.0;
                // the color depends on the health status
                glColor4f(1.0, 0.5, 0.0, healthStatus);

                int x = column * (this->creatureSize + this->borderSize);
                int y = row * (this->creatureSize + this->borderSize);
                glVertex3f(x                     , y                     , 0.0);
                glVertex3f(x + this->creatureSize, y                     , 0.0);
                glVertex3f(x + this->creatureSize, y + this->creatureSize, 0.0);
                glVertex3f(x                     , y + this->creatureSize, 0.0);
            }
        }
    }
    glEnd();
}


void View::update(int** world) {
    this->world = world;
    draw();
}
