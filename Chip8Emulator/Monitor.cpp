#include "Monitor.h"

using namespace sf;

namespace Chip8Emulator
{
    Monitor& Monitor::Instance()
    {
        static Monitor instance;
        return instance;
    }

    void Monitor::ScreenInitialisation()
    {
        window.create(VideoMode(WIDTH, HEIGHT, 32), "Chip8 Emulator");

        square[0] = RectangleShape(Vector2f(DIMPIXEL, DIMPIXEL));
        square[0].setFillColor(Color::Black);

        square[1] = RectangleShape(Vector2f(DIMPIXEL, DIMPIXEL));
        square[1].setFillColor(Color::White);
    }

    void Monitor::PixelInitialisation()
    {
        Uint8 x = 0, y = 0;

        for (x = 0; x < l; x++)
        {
            for (y = 0; y < L; y++)
            {
                pixel[x][y].position.x = x * DIMPIXEL;
                pixel[x][y].position.y = y * DIMPIXEL;
                pixel[x][y].color = BLACK;
            }
        }

    }

    void Monitor::DrawPixel(Uint8 x, Uint8 y)
    {
        RectangleShape pendingSquare(square[pixel[x][y].color]);
        pendingSquare.setPosition(pixel[x][y].position.x, pixel[x][y].position.y);
        window.draw(pendingSquare);
    }

    void Monitor::ScreenUpdate()
    {
        Uint8 x = 0, y = 0;

        for (x = 0; x < l; x++)
        {
            for (y = 0; y < L; y++)
            {
                DrawPixel(x, y);
            }
        }
        window.display();
    }

    void Monitor::ClearScreen()
    {
        Uint8 x = 0, y = 0;
        for (x = 0; x < l; x++)
        {
            for (y = 0; y < L; y++)
            {
                pixel[x][y].color = BLACK;
            }
        }
        window.clear();
    }
}