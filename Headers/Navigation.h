#pragma once
#include <vector>


#include <SFML/Graphics.hpp>

#include "General.h"

namespace Navigation {
	
	enum class BUTTON_ID {
		START,
		SETTINGS,
		EXIT,




		NONE
	};

	class MenuButton {
	private:
		sf::Text text_;
		BUTTON_ID id_;

	private:



	public:
		

		MenuButton(
			const std::string& name,
			BUTTON_ID id
		);

		void Draw(sf::RenderWindow& window) const;
		void UpdatePosition(const sf::Vector2f& pos, float scale);
		void IsHover(const sf::Vector2f& pos);
		BUTTON_ID IsClicked(const sf::Vector2f& pos) const;


		

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
		void IsClicked(sf::RenderWindow& window, const sf::Vector2f& pos) const;


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