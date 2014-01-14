#ifndef VIEW_H
#define VIEW_H

class View {
public:
    static const int CREATURE_SIZE = 1;
    static const int BORDER_SIZE = 1;

    void init(int screenW, int screenH, int worldWidth, int worldHeight);
    void resize(int width, int height);
    void draw(int** world);

private:
    int worldWidth, worldHeight;
};

#endif
