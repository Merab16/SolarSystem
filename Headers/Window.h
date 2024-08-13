#pragma once



#include <SFML/Graphics.hpp>

#include "Cursor.h"
#include "GeometicPrimitive.h"
#include "SolarSystem.h"
#include "General.h"


namespace MyWindow {
	class Window {
	private:
		// window
		unsigned width_;
		unsigned height_;
		sf::ContextSettings settings_;
		std::shared_ptr<sf::RenderWindow> window_;
		

		// cursor
		MyCursor::Cursor cursor_;

		// planets
		SolarSystem::Sun* sun_;
		std::vector< SolarSystem::Planet*> planetsBehind_;
		std::vector< SolarSystem::Planet*> planetsFrontOf_;

		

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
		void UpdateDepth();
		void Render();
		void Draw();

		// mouse funcs
		
		// planets
		void PlanetsInitialization();
		void PlanetsUpdate();
		void PlanetsDraw() const;

	public:
		Window(unsigned width = General::WIDTH, unsigned height = General::HEIGHT,
			std::string wnd_name = "SFML Application");
		~Window();


		void Run();

	};
}



