#include "../Headers/GUI.h"




namespace GUI {
	using namespace General;

	//================= PlanetInfoPanel =================//

	// constr & destr
	PlanetInfoPanel::PlanetInfoPanel()
		: area_({ 500, 800 }, { WIDTH - 500, 0 }, sf::Color::Blue)
	{
		planetName_.setFont(Fonts::MAIN);
		planetName_.setCharacterSize(24);
		planetName_.setFillColor(sf::Color::White);
		planetName_.setString("Planet: ");
	}

	// private

	// public
	void PlanetInfoPanel::Update(const sf::RenderWindow& window, const sf::Vector2f& pos, float scale) {

		auto area_pos = CurrentToGlobalPos(window, pos);
		area_.setPosition(area_pos);
		area_.setScale(scale, scale);

		auto name_pos = CurrentToGlobalPos(window, { pos.x + 10, pos.y + 10 });
		planetName_.setPosition(name_pos);
		planetName_.setScale(scale, scale);
	}

	void PlanetInfoPanel::Draw(sf::RenderWindow& window) const {
		window.draw(area_);
		window.draw(planetName_);
	}

	// setters
	void PlanetInfoPanel::SetName(const std::string& name) {
		planetName_.setString("Planet: " + name);
	}


	//================= Interface =================//
	// constr & destr
	Interface::Interface(sf::Text& fps, sf::Text& cursor)
		: guiScale_(1.f)
		, fps_(fps)
		, cursorPos_(cursor)
	{

	}


	// public
	void Interface::Draw(sf::RenderWindow& window) {
		mainMenu_.Draw(window);

		window.draw(fps_);
		window.draw(cursorPos_);
		planetInfoPanel_.Draw(window);
	}

	void Interface::Update(const sf::RenderWindow& window) {
		fps_.setScale(guiScale_, guiScale_);
		cursorPos_.setScale(guiScale_, guiScale_);
		
		mainMenu_.Update(window, guiScale_);
		
		planetInfoPanel_.Update(
			window,
			{WIDTH -500, 0},
			guiScale_);

	}

	void Interface::IsHover(const sf::Vector2f& pos) {
		mainMenu_.IsHover(pos);
	}

	void Interface::IsClicked(sf::RenderWindow& window, const sf::Vector2f& pos) const {
		mainMenu_.IsClicked(window, pos);
	}

	// setters
	void Interface::SetName(const std::string& name) {
		planetInfoPanel_.SetName(name);
	}
	



}