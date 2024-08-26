#pragma once
#include <vector>


#include <SFML/Graphics.hpp>

#include "General.h"

namespace Navigation {
	
	class MenuButton {
	private:
		sf::Text text_;



	private:



	public:
		MenuButton(
			const std::string& name
		);

		void Draw(sf::RenderWindow& window) const;
		void UpdatePosition(const sf::Vector2f& pos, float scale);
		void IsHover(const sf::Vector2f& pos);

	};



	class MainMenu {
		// consist of the main buttons: stop/start, settings, exit etc.

	private:
		std::vector<MenuButton> buttons_;

	private:
		void Initialization();
		void UpdateButtonsPosition(const sf::RenderWindow& window, float scale);

	public:
		MainMenu();
		void Draw(sf::RenderWindow& window);
		void Update(const sf::RenderWindow& window, float scale);
		void IsHover(const sf::Vector2f& pos);
		


	};

	class BarMenu {
		// меню где будут настройки с ползунками: 
		// 1. ускорение/замедление времени 
		// 2. 
	private:


	private:


	public:


	};


}