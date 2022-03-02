#ifndef EMULATOR_H
#define EMULATOR_H

#define CPUSPEED 4
#define FPS 16

#include "CPU.h"
#include "Monitor.h"
#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>

namespace Chip8Emulator
{
	class Emulator
	{
	public:
		void EmulationLoop();

	private:
		sf::SoundBuffer buffer;
		sf::Sound sound;
		bool paused;

		bool LoadGame(const char* gameName);
		void EventListener();
		void PauseListener();
	};
}

#endif
