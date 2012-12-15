/*
 * View.h
 *
 *  Created on: Jun 14, 2012
 *      Author: Samuel Groß
 */

#ifndef VIEW_H
#define VIEW_H

class View
{
public:
    View();
    virtual ~View();

    void init(int screenW, int screenH, int worldWidth, int worldHeight, int creatureSize, int borderSize);
    void resize(int width, int height);
    void draw();
    void update(int** world);

private:
    int** world;
    int worldWidth;
    int worldHeight;
    int creatureSize;
    int borderSize;

};

#endif 
