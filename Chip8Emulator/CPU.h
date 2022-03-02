#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include <SFML/Config.hpp>

#define MEMORYSIZE 4096
#define STARTADRESS 512
#define OPCODECOUNT 35

namespace Chip8Emulator
{
	class CPU
	{
	public:
		CPU(const CPU&) = delete;
		static CPU& Instance();

		void CPUInitialisation();
		sf::Uint16 GetOpcode();
		bool OpcodeInterpretation(sf::Uint16 opcode);
		void LoadFont();
		void CountDown();
		void Reset();

		sf::Uint8 memory[MEMORYSIZE];
		sf::Uint8 keys[16];
		sf::Uint8 soundCounter;

	private:
		CPU() {}

		struct JUMP
		{
			sf::Uint16 mask[OPCODECOUNT];
			sf::Uint16 id[OPCODECOUNT];
		};

		sf::Uint16 I;
		sf::Uint8 V[16];
		sf::Uint16 jump[16];
		sf::Uint8 jumpcount;
		sf::Uint8 gameCounter;
		sf::Uint16 pc;
		JUMP jp;

		void JumpInitialisation();
		sf::Uint8 GetAction(sf::Uint16 opcode);
		void DrawScreen(sf::Uint8 b1, sf::Uint8 b2, sf::Uint8 b3);
		sf::Uint8 WaitforKeyPress(sf::Uint8 b3);
	};
}

#endif
