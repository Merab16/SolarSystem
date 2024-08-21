#pragma once



#include <SFML/Graphics.hpp>

#include "Cursor.h"
#include "GeometicPrimitive.h"
#include "SolarSystem.h"
#include "General.h"
#include "Camera.h"


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

		// camera
		Camera::Camera camera_;
		//sf::View cameraPosition_;
		//sf::Vector2f cameraOffset_;
		//float cameraOffsetScale = 2.f;
		//float cameraZoom_ = 1.f;
		//sf::Vector2f startCamera_{ 0.f, 0.f };
		bool isPressed_ = false;

		// fps
		sf::Clock dtClock_;
		float dt_;
		sf::Text fps_;
		
		
		// font
		sf::Font font_;

		// gui
		float guiScale_ = 1.f;


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



