#include "Emulator.h"

using namespace Chip8Emulator;

Emulator emulator;

int main()
{
    emulator.EmulationLoop();
    return 0;
}

