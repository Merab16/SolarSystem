#pragma once
#include <SFML/Graphics.hpp>



#include "Cursor.h"
#include "Navigation.h"

namespace GUI {

	class PlanetInfoPanel {
		struct PanelStructure {
			std::string name;
			std::string radius;
			std::string distance;
		};



	private:
		// Возможно сделать в сводке маленькую картинку этой планеты, которач будет вращаться
		GeometricPrimitive::Rectangle area_;
		sf::Text planetName_;
	private:



	public:
		PlanetInfoPanel();

		void Update(const sf::RenderWindow& window, const sf::Vector2f& pos, float scale);
		void Draw(sf::RenderWindow& window) const;
		
		// setters
		void SetName(const std::string& name);
	};

	class Interface {
	private:
		float guiScale_;


		sf::Text& fps_;
		sf::Text& cursorPos_;

		// main menu
		Navigation::MainMenu mainMenu_;

		// planet's info
		PlanetInfoPanel planetInfoPanel_;

	private:



	public:
		Interface(sf::Text& fps, sf::Text& cursor);
		void Draw(sf::RenderWindow& window);
		void Update(const sf::RenderWindow& window);
		void IsHover(const sf::Vector2f& pos);
		void IsClicked(sf::RenderWindow& window, const sf::Vector2f& pos) const;


		// getters
		float& GetScale() { return guiScale_; }

		// setters
		void SetName(const std::string& name);



	};

	


}