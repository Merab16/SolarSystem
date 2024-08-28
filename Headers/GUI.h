#pragma once
#include <SFML/Graphics.hpp>



#include "Cursor.h"
#include "Navigation.h"
#include "General.h"

namespace GUI {
	


	class PlanetInfoPanel {
	private:
		// Возможно сделать в сводке маленькую картинку этой планеты, которач будет вращаться
		GeometricPrimitive::Rectangle area_;
		General::PlanetInfo info_;

		// info
		std::unique_ptr<sf::Text> name_;
		std::unique_ptr<sf::Text> distance_;
		std::unique_ptr<sf::Text> radius_;
		std::unique_ptr<sf::Text> weight_; 
		std::unique_ptr<sf::Text> velocity_;
		std::unique_ptr<sf::Text> population_;

	private:
		void UpdateInformation();
		void TextSettings(sf::Text& text, 
			size_t char_size = 24,
			sf::Color color = sf::Color::White,
			const sf::Font& font = General::Fonts::MAIN);

	public:
		PlanetInfoPanel();

		void Update(const sf::RenderWindow& window, const sf::Vector2f& pos, float scale);
		
		void Draw(sf::RenderWindow& window) const;
		
		// setters
		void SetPlanet(const General::PlanetInfo& info);
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
		void SetPlanet(const General::PlanetInfo& info);



	};

	


}