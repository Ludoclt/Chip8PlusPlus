#include "CPU.h"
#include "Monitor.h"
#include <iostream>

using namespace sf;

namespace Chip8Emulator
{
    CPU& CPU::Instance()
    {
        static CPU instance;
        return instance;
    }

    void CPU::CPUInitialisation()
	{
		Uint16 i = 0;

		for (i = 0; i < MEMORYSIZE; i++)
		{
			memory[i] = 0;
		}

		for (i = 0; i < 16; i++)
		{
			V[i] = 0;
			jump[i] = 0;
		}

		pc = STARTADRESS;
		jumpcount = 0;
		gameCounter = 0;
		soundCounter = 0;
		I = 0;

        JumpInitialisation();
	}

	void CPU::JumpInitialisation()
	{
		jp.mask[0] = 0x0000; jp.id[0] = 0x0FFF;          /* 0NNN */
		jp.mask[1] = 0xFFFF; jp.id[1] = 0x00E0;          /* 00E0 */
		jp.mask[2] = 0xFFFF; jp.id[2] = 0x00EE;          /* 00EE */
		jp.mask[3] = 0xF000; jp.id[3] = 0x1000;          /* 1NNN */
		jp.mask[4] = 0xF000; jp.id[4] = 0x2000;          /* 2NNN */
		jp.mask[5] = 0xF000; jp.id[5] = 0x3000;          /* 3XNN */
		jp.mask[6] = 0xF000; jp.id[6] = 0x4000;          /* 4XNN */
		jp.mask[7] = 0xF00F; jp.id[7] = 0x5000;          /* 5XY0 */
		jp.mask[8] = 0xF000; jp.id[8] = 0x6000;          /* 6XNN */
		jp.mask[9] = 0xF000; jp.id[9] = 0x7000;          /* 7XNN */
		jp.mask[10] = 0xF00F; jp.id[10] = 0x8000;          /* 8XY0 */
		jp.mask[11] = 0xF00F; jp.id[11] = 0x8001;          /* 8XY1 */
		jp.mask[12] = 0xF00F; jp.id[12] = 0x8002;          /* 8XY2 */
		jp.mask[13] = 0xF00F; jp.id[13] = 0x8003;          /* BXY3 */
		jp.mask[14] = 0xF00F; jp.id[14] = 0x8004;          /* 8XY4 */
		jp.mask[15] = 0xF00F; jp.id[15] = 0x8005;          /* 8XY5 */
		jp.mask[16] = 0xF00F; jp.id[16] = 0x8006;          /* 8XY6 */
		jp.mask[17] = 0xF00F; jp.id[17] = 0x8007;          /* 8XY7 */
		jp.mask[18] = 0xF00F; jp.id[18] = 0x800E;          /* 8XYE */
		jp.mask[19] = 0xF00F; jp.id[19] = 0x9000;          /* 9XY0 */
		jp.mask[20] = 0xF000; jp.id[20] = 0xA000;          /* ANNN */
		jp.mask[21] = 0xF000; jp.id[21] = 0xB000;          /* BNNN */
		jp.mask[22] = 0xF000; jp.id[22] = 0xC000;          /* CXNN */
		jp.mask[23] = 0xF000; jp.id[23] = 0xD000;          /* DXYN */
		jp.mask[24] = 0xF0FF; jp.id[24] = 0xE09E;          /* EX9E */
		jp.mask[25] = 0xF0FF; jp.id[25] = 0xE0A1;          /* EXA1 */
		jp.mask[26] = 0xF0FF; jp.id[26] = 0xF007;          /* FX07 */
		jp.mask[27] = 0xF0FF; jp.id[27] = 0xF00A;          /* FX0A */
		jp.mask[28] = 0xF0FF; jp.id[28] = 0xF015;          /* FX15 */
		jp.mask[29] = 0xF0FF; jp.id[29] = 0xF018;          /* FX18 */
		jp.mask[30] = 0xF0FF; jp.id[30] = 0xF01E;          /* FX1E */
		jp.mask[31] = 0xF0FF; jp.id[31] = 0xF029;          /* FX29 */
		jp.mask[32] = 0xF0FF; jp.id[32] = 0xF033;          /* FX33 */
		jp.mask[33] = 0xF0FF; jp.id[33] = 0xF055;          /* FX55 */
		jp.mask[34] = 0xF0FF; jp.id[34] = 0xF065;          /* FX65 */
	}

    void CPU::LoadFont()
    {
        memory[0] = 0xF0; memory[1] = 0x90; memory[2] = 0x90; memory[3] = 0x90; memory[4] = 0xF0; //O 

        memory[5] = 0x20; memory[6] = 0x60; memory[7] = 0x20; memory[8] = 0x20; memory[9] = 0x70; //1 

        memory[10] = 0xF0; memory[11] = 0x10; memory[12] = 0xF0; memory[13] = 0x80; memory[14] = 0xF0; //2 

        memory[15] = 0xF0; memory[16] = 0x10; memory[17] = 0xF0; memory[18] = 0x10; memory[19] = 0xF0; //3 

        memory[20] = 0x90; memory[21] = 0x90; memory[22] = 0xF0; memory[23] = 0x10; memory[24] = 0x10; //4 

        memory[25] = 0xF0; memory[26] = 0x80; memory[27] = 0xF0; memory[28] = 0x10; memory[29] = 0xF0; //5 

        memory[30] = 0xF0; memory[31] = 0x80; memory[32] = 0xF0; memory[33] = 0x90; memory[34] = 0xF0; //6 

        memory[35] = 0xF0; memory[36] = 0x10; memory[37] = 0x20; memory[38] = 0x40; memory[39] = 0x40; //7 

        memory[40] = 0xF0; memory[41] = 0x90; memory[42] = 0xF0; memory[43] = 0x90; memory[44] = 0xF0; //8 

        memory[45] = 0xF0; memory[46] = 0x90; memory[47] = 0xF0; memory[48] = 0x10; memory[49] = 0xF0; //9 

        memory[50] = 0xF0; memory[51] = 0x90; memory[52] = 0xF0; memory[53] = 0x90; memory[54] = 0x90; //A 

        memory[55] = 0xE0; memory[56] = 0x90; memory[57] = 0xE0; memory[58] = 0x90; memory[59] = 0xE0; //B 

        memory[60] = 0xF0; memory[61] = 0x80; memory[62] = 0x80; memory[63] = 0x80; memory[64] = 0xF0; //C 

        memory[65] = 0xE0; memory[66] = 0x90; memory[67] = 0x90; memory[68] = 0x90; memory[69] = 0xE0; //D 

        memory[70] = 0xF0; memory[71] = 0x80; memory[72] = 0xF0; memory[73] = 0x80; memory[74] = 0xF0; //E 

        memory[75] = 0xF0; memory[76] = 0x80; memory[77] = 0xF0; memory[78] = 0x80; memory[79] = 0x80; //F
    }

    Uint16 CPU::GetOpcode()
    {
        return (memory[pc] << 8) + memory[pc + 1];
    }

	Uint8 CPU::GetAction(Uint16 opcode)
	{
		Uint8 action;
		Uint16 result;

		for (action = 0; action < OPCODECOUNT; action++)
		{
			result = (jp.mask[action] & opcode);

			if (result == jp.id[action])
			{
				break;
			}
		}
		return action;
	}

    void CPU::DrawScreen(Uint8 b1, Uint8 b2, Uint8 b3)
    {
        Uint8 x = 0, y = 0, k = 0, coding = 0, j = 0, gap = 0;
        V[0xF] = 0;

        for (k = 0; k < b1; k++)
        {
            coding = memory[I + k];
            y = (V[b2] + k) % L;

            for (j = 0, gap = 7; j < 8; j++, gap--)
            {
                x = (V[b3] + j) % l;

                if ((coding & (0x1 << gap)) != 0)
                {
                    if (Monitor::Instance().pixel[x][y].color == WHITE)
                    {
                        Monitor::Instance().pixel[x][y].color = BLACK;
                        V[0xF] = 1;
                    }
                    else
                    {
                        Monitor::Instance().pixel[x][y].color = WHITE;
                    }
                }
            }
        }
    }

    Uint8 CPU::WaitforKeyPress(Uint8 b3)
    {
        bool waiting = true, paused = false;

        while (waiting)
        {
            Monitor::Instance().window.waitEvent(Monitor::Instance().event);
            switch (Monitor::Instance().event.type)
            {
            case Event::Closed:
                Monitor::Instance().window.close();
                exit(0);
            case Event::KeyPressed:
                switch (Monitor::Instance().event.key.code)
                {
                case Keyboard::Numpad8:
                    V[b3] = 0x2;
                    keys[0x2] = 1;
                    waiting = 0;
                    break;
                case Keyboard::Numpad4:
                    V[b3] = 0x4;
                    keys[0x4] = 1;
                    waiting = 0;
                    break;
                case Keyboard::Numpad6:
                    V[b3] = 0x6;
                    keys[0x6] = 1;
                    waiting = 0;
                    break;
                case Keyboard::Numpad2:
                    V[b3] = 0x8;
                    keys[0x8] = 1;
                    break;
                case Keyboard::Space:
                    waiting = false;
                    paused = true;
                    break;
                default:
                    break;
                }
            }
        }
        return paused;
    }

	void CPU::CountDown()
	{
		if (gameCounter > 0)
		{
			gameCounter--;
		}
		if (soundCounter > 0)
		{
			soundCounter--;
		}
	}

    void CPU::Reset()
    {
        Uint8 i = 0;
        for (i = 0; i < 16; i++)
        {
            V[i] = 0;
            jump[i] = 0;
            keys[i] = 0;
        }

        pc = STARTADRESS;
        jumpcount = 0;
        gameCounter = 0;
        soundCounter = 0;
        I = 0;
        Monitor::Instance().PixelInitialisation();
        Monitor::Instance().ScreenUpdate();
    }

    bool CPU::OpcodeInterpretation(Uint16 opcode)
    {
        bool paused = false;
        Uint8 b4, b3, b2, b1;

        b3 = (opcode & (0x0F00)) >> 8;
        b2 = (opcode & (0x00F0)) >> 4;
        b1 = (opcode & (0x000F));

        b4 = GetAction(opcode);

        switch (b4)
        {
        case 0: {
            break;
        }
        case 1: {
            //00E0
            Monitor::Instance().ClearScreen();
            break;
        }

        case 2: {
            //00EE
            if (jumpcount > 0)
            {
                jumpcount--;
                pc = jump[jumpcount];
            }
            break;
        }
        case 3: {
            //1NNN
            pc = (b3 << 8) + (b2 << 4) + b1;
            pc -= 2;

            break;
        }
        case 4: {
            //2NNN
            jump[jumpcount] = pc;

            if (jumpcount < 15)
            {
                jumpcount++;
            }

            pc = (b3 << 8) + (b2 << 4) + b1;
            pc -= 2;

            break;
        }
        case 5: {
            //3XNN
            if (V[b3] == ((b2 << 4) + b1))
            {
                pc += 2;
            }

            break;
        }
        case 6: {
            //4XNN
            if (V[b3] != ((b2 << 4) + b1))
            {
                pc += 2;
            }

            break;
        }
        case 7: {
            //5XY0
            if (V[b3] == V[b2])
            {
                pc += 2;
            }

            break;
        }

        case 8: {
            //6XNN
            V[b3] = (b2 << 4) + b1;
            break;
        }
        case 9: {
            //7XNN
            V[b3] += (b2 << 4) + b1;

            break;
        }
        case 10: {
            //8XY0
            V[b3] = V[b2];

            break;
        }
        case 11: {
            //8XY1
            V[b3] = V[b3] | V[b2];

            break;
        }
        case 12: {
            //8XY2
            V[b3] = V[b3] & V[b2];

            break;
        }
        case 13: {
            //8XY3
            V[b3] = V[b3] ^ V[b2];

            break;
        }
        case 14: {
            //8XY4
            if ((V[b3] + V[b2]) > 255)
            {
                V[0xF] = 1;
            }
            else
            {
                V[0xF] = 0;
            }
            V[b3] += V[b2];

            break;
        }
        case 15: {
            //8XY5
            if ((V[b3] < V[b2]))
            {
                V[0xF] = 0;
            }
            else
            {
                V[0xF] = 1;
            }
            V[b3] -= V[b2];

            break;
        }
        case 16: {
            //8XY6
            V[0xF] = (V[b3] & (0x01));
            V[b3] = (V[b3] >> 1);

            break;
        }
        case 17: {
            //8XY7
            if ((V[b2] < V[b3]))
            {
                V[0xF] = 0;
            }
            else
            {
                V[0xF] = 1;
            }
            V[b3] = V[b2] - V[b3];

            break;
        }
        case 18: {
            //8XYE
            V[0xF] = (V[b3] >> 7);
            V[b3] = (V[b3] << 1);

            break;
        }

        case 19: {
            //9XY0
            if (V[b3] != V[b2])
            {
                pc += 2;
            }

            break;
        }
        case 20: {
            //ANNN
            I = (b3 << 8) + (b2 << 4) + b1;

            break;
        }
        case 21: {
            //BNNN
            pc = (b3 << 8) + (b2 << 4) + b1 + V[0];
            pc -= 2;

            break;

        }
        case 22: {
            //CXNN
            V[b3] = (rand()) % ((b2 << 4) + b1 + 1);

            break;

        }

        case 23: {
            //DXYN
            DrawScreen(b1, b2, b3);

            break;

        }
        case 24: {
            //EX9E
            if (keys[V[b3]] == 1)
            {
                pc += 2;
            }

            break;
        }
        case 25: {
            //EXA1
            if (keys[V[b3]] == 0)
            {
                pc += 2;
            }

            break;
        }

        case 26: {
            //FX07
            V[b3] = gameCounter;

            break;
        }
        case 27: {
            //FX0A
            paused = WaitforKeyPress(b3);

            break;
        }


        case 28: {
            //FX15
            gameCounter = V[b3];

            break;
        }
        case 29: {
            //FX18
            soundCounter = V[b3];

            break;
        }
        case 30: {
            //FX1E
            if ((I + V[b3]) > 0xFFF)
            {
                V[0xF] = 1;
            }
            else
            {
                V[0xF] = 0;
            }
            I += V[b3];


            break;
        }

        case 31: {
            //FX29
            I = V[b3] * 5;

            break;
        }

        case 32: {
            //FX33
            memory[I] = (V[b3] - V[b3] % 100) / 100;
            memory[I + 1] = (((V[b3] - V[b3] % 10) / 10) % 10);
            memory[I + 2] = V[b3] - memory[I] * 100 - 10 * memory[I + 1];

            break;
        }
        case 33: {
            //FX55
            Uint8 i = 0;
            for (i = 0; i <= b3; i++)
            {
                memory[I + i] = V[i];
            }

            break;
        }
        case 34: {
            //FX65
            Uint8 i = 0;

            for (i = 0; i <= b3; i++)
            {
                V[i] = memory[I + i];
            }

            break;
        }

        default: {

            break;
        }

        }
        pc += 2;
        return paused;
    }
}