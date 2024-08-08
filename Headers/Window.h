#pragma once



#include <SFML/Graphics.hpp>

#include "Cursor.h"
#include "GeometicPrimitive.h"
#include "SolarSystem.h"


namespace MyWindow {
	class Window {
	private:
		// window
		unsigned width_;
		unsigned height_;
		std::shared_ptr<sf::RenderWindow> window_;

		// cursor
		MyCursor::Cursor cursor_;

		// planets
		SolarSystem::Planet planet_;
		

		// fps
		sf::Clock dtClock_;
		float dt_;
		sf::Text fps_;
		
		// font
		sf::Font font_;


	private:
		// general
		void Initialization();
		void Update();
		void UpdateSFMLEvents();
		void UpdateDt();
		void Render();
		void Draw();

		// mouse funcs
		

	public:
		Window(unsigned width = 800, unsigned height = 600, std::string wnd_name = "SFML Application");
		~Window();


		void Run();

	};
}



