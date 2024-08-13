#include <string>
#include <iostream>
#include <algorithm>


#include "../Headers/Window.h"
namespace MyWindow {
	// constr & destr
	Window::Window(unsigned width, unsigned height, std::string wnd_name)
		: width_(width)
		, height_(height)
		, settings_(0, 0, 8)
		, window_(new sf::RenderWindow(sf::VideoMode(width_, height_), wnd_name, sf::Style::Default, settings_))
	{
		Initialization();
		PlanetsInitialization();
	}

	Window::~Window() {
		for (auto& planet : planets_) {
			delete planet;
		}
	}

	// private

		// general
	void Window::Initialization() {
		

		window_->setFramerateLimit(144);

		font_.loadFromFile("Fonts/CascadiaCode.ttf");
		fps_.setFont(font_);
		fps_.setCharacterSize(16);
		fps_.setPosition(sf::Vector2f{ 0, 10 });

		//window_->setPosition(sf::Vector2i(0, 0));
	}

	void Window::Update() {
		UpdateDt();

		UpdateSFMLEvents();
		
		UpdateDepth();
		PlanetsUpdate();
	}

	void Window::UpdateSFMLEvents() {
		sf::Event sfEvent;
		while (window_->pollEvent(sfEvent))
		{
			switch (sfEvent.type) {
			case sf::Event::Closed:
				window_->close();
				break;
			case sf::Event::KeyPressed:
				
				break;

			case sf::Event::MouseMoved:
				cursor_.UpdatePos(*window_);
				break;

			case sf::Event::MouseButtonPressed:
				
				break;




			}

		}

	}

	void Window::UpdateDt() {
		dt_ = dtClock_.restart().asSeconds();
		fps_.setString(std::string("FPS: " + std::to_string(int(1.f / dt_))));
	}

	void Window::UpdateDepth() {

		std::vector<SolarSystem::Planet*> tmp;

		for (auto& planet : planetsBehind_) {
			tmp.push_back(std::move(planet));
		}

		for (auto& planet : planetsFrontOf_) {
			tmp.push_back(std::move(planet));
		}

		planetsBehind_.clear();
		planetsFrontOf_.clear();

		for (auto& planet : tmp) {
			if (planet->GetAngle() >= 180) {
				planetsFrontOf_.push_back(std::move(planet));
			}
			else {
				planetsBehind_.push_back(std::move(planet));
			}
		}

		std::sort(planetsBehind_.begin(), planetsBehind_.end(), []
			(const SolarSystem::Planet* lhs, const SolarSystem::Planet* rhs) {
				return lhs->GetDistance() > rhs->GetDistance();
			});

		std::sort(planetsFrontOf_.begin(), planetsFrontOf_.end(), []
		(const SolarSystem::Planet* lhs, const SolarSystem::Planet* rhs) {
				return lhs->GetDistance() < rhs->GetDistance();
			});


	}

	void Window::Render() {
		// clear
		window_->clear();

		// draw
		Draw();

		// display
		window_->display();
	}

	void Window::Draw() {
		
		PlanetsDraw();


		cursor_.Draw(*window_);
		window_->draw(fps_);
	}


	// planets 
	void Window::PlanetsInitialization() {
		// PLANETS	dist	D, km	
		// sun		
		// mercury	0.39	4.9k
		// venus	0.72	12.1k
		// earth	1.		12.7k
		// mars		1.52	6.8k
		// jupiter	5.2		139.8k
		// saturn	9.54	116k
		// uranus	19.19	50.8k
		// neptune	30.07	48.6k
		
		// min distance - 50
		//planetsBehind_.push_back(new SolarSystem::Planet(20, 50, sf::Color::Green));
		//planetsBehind_.push_back(new SolarSystem::Planet(20, 60, sf::Color::Red));
		//planetsBehind_.push_back(new SolarSystem::Planet(10, 60, sf::Color::Cyan));
		//planetsBehind_.push_back(new SolarSystem::Planet(40, 90, sf::Color::Magenta));
		//planetsBehind_.push_back(new SolarSystem::Planet(20, 100));

		planetsBehind_.push_back(new SolarSystem::Planet(5, 50));
		planetsBehind_.push_back(new SolarSystem::Planet(8, 55));
		planetsBehind_.push_back(new SolarSystem::Planet(10, 60));
		planetsBehind_.push_back(new SolarSystem::Planet(6, 70));
		planetsBehind_.push_back(new SolarSystem::Planet(50, 80));
		planetsBehind_.push_back(new SolarSystem::Planet(40, 90));
		planetsBehind_.push_back(new SolarSystem::Planet(20, 100));
		planetsBehind_.push_back(new SolarSystem::Planet(18, 110));

		

		planets_.push_back(new SolarSystem::Sun(60));

	}

	void Window::PlanetsUpdate() {

		for (auto& planet : planetsBehind_) {
			planet->UpdatePosition(dt_);
		}

		for (auto& planet : planets_) {
			planet->UpdatePosition(dt_);
		}

		for (auto& planet : planetsFrontOf_) {
			planet->UpdatePosition(dt_);
		}


		
	}

	void Window::PlanetsDraw() const {

		for (const auto& planet : planetsBehind_) {
			planet->Draw(*window_);
		}

		for (const auto& planet : planets_) {
			planet->Draw(*window_);
		}

		for (const auto& planet : planetsFrontOf_) {
			planet->Draw(*window_);
		}


		/*for (const auto& planet : planets_) {
			planet->Draw(*window_);
		}*/
		
	}

	// public
	void Window::Run() {
		while (window_->isOpen()) {

			// updateDt

			// update
			Update();


			// render
			Render();
		}
	}
}



