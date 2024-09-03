#pragma once



#include <SFML/Graphics.hpp>

#include "Cursor.h"
#include "GeometicPrimitive.h"
#include "SolarSystem.h"
#include "General.h"
#include "Camera.h"
#include "GUI.h"


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
		std::vector<SolarSystem::Planet*> planetsBehind_;
		std::vector<SolarSystem::Planet*> planetsFrontOf_;

		// background
		std::unique_ptr<sf::Texture> textureBackground_;
		std::unique_ptr<sf::Sprite> spriteBackground_;


		// camera
		Camera::Camera camera_;
		bool isPressed_ = false;

		// fps
		sf::Clock dtClock_;
		float dt_;
		sf::Text fps_;

		// gui
		std::unique_ptr<GUI::Interface> interface_;

		// double click
		sf::Clock dcClock_;

		

	private:
		// general
		void Initialization();
		void Update();
		void UpdateSFMLEvents();
		void UpdateDt();
		void UpdateDepth();
		void Render();
		void Draw();
		void UpdateMenuPosition();


		// mouse funcs
		void MousePressEvent(const sf::Event& e);
		void MouseReleasedEvent(const sf::Event& e);
		void MouseMoveEvent(const sf::Event& e);
		void MouseWheelEvent(const sf::Event& e);
		

		// keyboard func
		void KeyboardPressEvent(int key);
		
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



