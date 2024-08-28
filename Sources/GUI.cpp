#include "../Headers/GUI.h"




namespace GUI {
	using namespace General;

	//================= PlanetInfoPanel =================//

	// constr & destr
	PlanetInfoPanel::PlanetInfoPanel()
		: area_({ 500, 800 }, { WIDTH - 500, 0 }, sf::Color::Blue)
	{
		name_ = std::make_unique<sf::Text>();
		distance_ = std::make_unique<sf::Text>();
		radius_ = std::make_unique<sf::Text>();
		weight_ = std::make_unique<sf::Text>();
		velocity_ = std::make_unique<sf::Text>();
		population_ = std::make_unique<sf::Text>();

		TextSettings(*name_);
		TextSettings(*distance_);
		TextSettings(*radius_);
		TextSettings(*weight_);
		TextSettings(*velocity_);
		TextSettings(*population_);

	}

	// private
	void PlanetInfoPanel::UpdateInformation() {
		name_->setString("Planet: " + info_.name);
		distance_->setString("Distance: " + std::to_string(int(info_.distance)));
		radius_->setString("Radius: " + std::to_string(int(info_.radius)) + " * 10^4 km");
		weight_->setString("Weight: " + std::to_string(int(info_.weight)) + " * 10^25 kg");
		velocity_->setString("Velocity: " + std::to_string(int(info_.velocity)) + " km/s");
		population_->setString("Population: " + std::to_string(info_.population) + " b");
	}

	void PlanetInfoPanel::TextSettings(sf::Text& text, size_t char_size,
		sf::Color color, const sf::Font& font) {
		text.setCharacterSize((int)char_size);
		text.setFillColor(color);
		text.setFont(font);
	}

	// public
	void PlanetInfoPanel::Update(const sf::RenderWindow& window, const sf::Vector2f& pos, float scale) {

		auto area_pos = CurrentToGlobalPos(window, pos);
		area_.setPosition(area_pos);
		area_.setScale(scale, scale);

		auto name_pos = CurrentToGlobalPos(window, { pos.x + 10, pos.y + 10 });
		name_->setPosition(name_pos);
		name_->setScale(scale, scale);

		auto distance_pos = CurrentToGlobalPos(window, { pos.x + 10, pos.y + 30 });
		distance_->setPosition(distance_pos);
		distance_->setScale(scale, scale);

		auto diametr_pos = CurrentToGlobalPos(window, { pos.x + 10, pos.y + 50 });
		radius_->setPosition(diametr_pos);
		radius_->setScale(scale, scale);

		auto weight_pos = CurrentToGlobalPos(window, { pos.x + 10, pos.y + 70 });
		weight_->setPosition(weight_pos);
		weight_->setScale(scale, scale);

		auto velocity_pos = CurrentToGlobalPos(window, { pos.x + 10, pos.y + 90 });
		velocity_->setPosition(velocity_pos);
		velocity_->setScale(scale, scale);

		auto population_pos = CurrentToGlobalPos(window, { pos.x + 10, pos.y + 110 });
		population_->setPosition(population_pos);
		population_->setScale(scale, scale);
	}

	void PlanetInfoPanel::Draw(sf::RenderWindow& window) const {
		window.draw(area_);

		window.draw(*name_);
		window.draw(*distance_);
		window.draw(*radius_);
		window.draw(*weight_);
		window.draw(*velocity_);
		window.draw(*population_);
	}

	// setters
	void PlanetInfoPanel::SetPlanet(const General::PlanetInfo& info) {
		info_ = info;
		UpdateInformation();
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
	void Interface::SetPlanet(const General::PlanetInfo& info) {
		planetInfoPanel_.SetPlanet(info);
	}
	



}