#ifndef MONITOR_H
#define MONITOR_H

#include <SFML/Graphics.hpp>
#include <cstdint>

#define BLACK  0 
#define WHITE 1 
#define l 64
#define L 32
#define DIMPIXEL 8
#define WIDTH   l*DIMPIXEL
#define HEIGHT  L*DIMPIXEL

namespace Chip8Emulator
{
	class Monitor
	{
	public:
		Monitor(const Monitor&) = delete;
		static Monitor& Instance();

		struct PIXEL
		{
			sf::Vector2<sf::Uint16> position;
			sf::Uint8 color;
		};

		PIXEL pixel[l][L];
		sf::RenderWindow window;
		sf::Event event;

		void ScreenInitialisation();
		void PixelInitialisation();
		void ScreenUpdate();
		void ClearScreen();

	private:
		Monitor() {}

		sf::RectangleShape square[2];

		void DrawPixel(sf::Uint8 x, sf::Uint8 y);
	};
}

#endif
