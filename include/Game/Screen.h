#ifndef SCREEN_H
#define SCREEN_H

class Screen {
public:
    static const int WIDTH = 480;
    static const int HEIGHT = 800;

    static const int getWidth() { return WIDTH; }
    static const int getHeight() { return HEIGHT; }
};

#endif // SCREEN_H