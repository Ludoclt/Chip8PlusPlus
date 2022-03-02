#include "Emulator.h"
#include <iostream>
#include <fstream>

using namespace sf;

namespace Chip8Emulator
{
	void Emulator::EmulationLoop()
	{
        Uint8 counter = 0;
        bool started = false;
        std::string gameName;

        std::cout << "Please enter the rom name or path : ";
        std::cin >> gameName;

        CPU::Instance().CPUInitialisation();
        Monitor::Instance().ScreenInitialisation();
        Monitor::Instance().PixelInitialisation();
        CPU::Instance().LoadFont();

        if (!buffer.loadFromFile("beep.wav"))
        {
            fprintf(stderr, "An error occurred while loading the audio file");
            exit(1);
        }
        sound.setBuffer(buffer);

        started = LoadGame(gameName.c_str());

        if (started)
        {
            while (Monitor::Instance().window.isOpen())
            {
                while (!paused)
                {
                    EventListener();

                    for (counter = 0; counter < CPUSPEED; counter++)
                    {
                        paused = CPU::Instance().OpcodeInterpretation(CPU::Instance().GetOpcode());
                    }

                    if (CPU::Instance().soundCounter != 0)
                    {
                        sound.play();
                        CPU::Instance().soundCounter = 0;
                    }

                    Monitor::Instance().ScreenUpdate();
                    CPU::Instance().CountDown();
                    PauseListener();
                    sleep(milliseconds(FPS));
                }
                PauseListener();
            }
        }
	}

    bool Emulator::LoadGame(const char* gameName)
    {
        std::ifstream game;
        game.open(gameName, std::fstream::in | std::fstream::binary);

        if (game.is_open())
        {
            game.read((char*)&CPU::Instance().memory[STARTADRESS], sizeof(Uint8) * (MEMORYSIZE - STARTADRESS));
            game.close();
            return true;
        }
        else
        {
            fprintf(stderr, "An error occurred while opening the rom");
            return false;
        }
    }

    void Emulator::EventListener()
    {
        while (Monitor::Instance().window.pollEvent(Monitor::Instance().event))
        {
            if (Monitor::Instance().event.type == Event::Closed)
            {
                Monitor::Instance().window.close();
                exit(0);
            }

            if (Monitor::Instance().event.type == Event::KeyPressed)
            {
                switch (Monitor::Instance().event.key.code)
                {
                case Keyboard::Numpad8:
                    CPU::Instance().keys[0x2] = 1;
                    break;
                case Keyboard::Numpad4:
                    CPU::Instance().keys[0x4] = 1;
                    break;
                case Keyboard::Numpad6:
                    CPU::Instance().keys[0x6] = 1;
                    break;
                case Keyboard::Numpad2:
                    CPU::Instance().keys[0x8] = 1;
                    break;
                case Keyboard::Escape:
                    CPU::Instance().Reset();
                default:
                    break;
                }
            }

            if (Monitor::Instance().event.type == Event::KeyReleased)
            {
                switch (Monitor::Instance().event.key.code)
                {
                case Keyboard::Numpad8:
                    CPU::Instance().keys[0x2] = 0;
                    break;
                case Keyboard::Numpad4:
                    CPU::Instance().keys[0x4] = 0;
                    break;
                case Keyboard::Numpad6:
                    CPU::Instance().keys[0x6] = 0;
                    break;
                case Keyboard::Numpad2:
                    CPU::Instance().keys[0x8] = 0;
                    break;
                default:
                    break;
                }
            }
        }
    }

    void Emulator::PauseListener()
    {
        while (Monitor::Instance().window.pollEvent(Monitor::Instance().event))
        {
            if (Monitor::Instance().event.type == Event::KeyPressed)
            {
                if (Monitor::Instance().event.key.code == Keyboard::Space)
                {
                    paused = !paused;
                }
            }
        }
    }
}

