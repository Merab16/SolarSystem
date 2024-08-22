#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>


#include "../Headers/Window.h"
namespace MyWindow {
	// constr & destr
	Window::Window(unsigned width, unsigned height, std::string wnd_name)
		: width_(width)
		, height_(height)
		, settings_(0, 0, 8)
		, window_(new sf::RenderWindow(sf::VideoMode(width_, height_),
			wnd_name, sf::Style::Default, settings_))
	{
		Initialization();
		PlanetsInitialization();
	}

	Window::~Window() {
		for (auto& planet : planetsBehind_) {
			delete planet;
		}
		for (auto& planet : planetsFrontOf_) {
			delete planet;
		}
		delete sun_;
	}

	// private

		// general
	void Window::Initialization() {

		// window
		window_->setFramerateLimit(144);
		window_->setView(camera_.GetCamera());

		// font && fps
		font_.loadFromFile("Fonts/CascadiaCode.ttf");
		fps_.setFont(font_);
		fps_.setCharacterSize(16);


		interface_ = std::make_unique<GUI::Interface>(fps_, cursor_.GetText());
		
	}

	void Window::Update() {
		UpdateDt();

		UpdateSFMLEvents();
		
		UpdateMenuPosition();

		UpdateDepth();
		PlanetsUpdate();

		//std::cout << cameraPosition_.getCenter().x << ' ' 
			//<< cameraPosition_.getCenter().y << std::endl;
		
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
				KeyboardPressEvent(sfEvent.key.code);
				break;

			case sf::Event::MouseMoved:
				MouseMoveEvent(sfEvent);
				break;

			case sf::Event::MouseButtonPressed:
				MousePressEvent(sfEvent);
				break;
			case  sf::Event::MouseButtonReleased:
				MouseReleasedEvent(sfEvent);
				break;

			case sf::Event::MouseWheelScrolled:
				MouseWheelEvent(sfEvent);
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

		interface_->Draw(*window_);

	}

	void Window::UpdateMenuPosition() {
		//window.mapPixelToCoords(static_cast<sf::Vector2i>(pos));
		// fps
		auto fpsPos = window_->mapPixelToCoords({ 0, 0 });
		fps_.setPosition(sf::Vector2f{ fpsPos });

		// cursor
		auto cursorPos = window_->mapPixelToCoords({ 0, 20 });
		cursor_.UpdatePos(*window_, cursorPos);
		
		
		interface_->Update();
	}

	// mouse funcs
	void Window::MousePressEvent(const sf::Event& e) {
		
		if (e.mouseButton.button == sf::Mouse::Left) {
			camera_.Start(cursor_.GetPosition());

			isPressed_ = true;


			for (const auto& planet : planetsBehind_) {
				if (planet->IsClicked(*window_, cursor_.GetPosition())) {
					std::cout << planet->GetName() << std::endl;
					//std::cout << planet->GetRadius() << std::endl;
				} 
			}

			for (const auto& planet : planetsFrontOf_) {
				if (planet->IsClicked(*window_, cursor_.GetPosition())) {
					std::cout << planet->GetName() << std::endl;
					//std::cout << planet->GetRadius() << std::endl;
				}
			}
			

		}
		

	}

	void Window::MouseReleasedEvent(const sf::Event& e) {
		
		if (e.mouseButton.button == sf::Mouse::Left) {
			isPressed_ = false;

		}
		
	}

	void Window::MouseMoveEvent(const sf::Event& e) {
		

		if (isPressed_) {
			auto finish = cursor_.GetPosition();
			sf::Vector2f offset = camera_.Finish(finish); 
			//std::cout << offset.x << ' ' << offset.y << std::endl;
			if (std::abs(offset.x) > 5 || std::abs(offset.y) > 5) {
				camera_.GetOffset() += offset;

				camera_.Start(cursor_.GetPosition());
				camera_.SetCenter();
				window_->setView(camera_.GetCamera());
			}
			
		}

		
		
	}

	void Window::MouseWheelEvent(const sf::Event& e) {
		if (e.mouseButton.button == sf::Mouse::Wheel::VerticalWheel) {
			
			if (e.mouseWheelScroll.delta > 0) {
				camera_.GetZoom() -= 0.1;
				interface_->GetScale() *= (1 - 0.1);
			}
			else {
				camera_.GetZoom() += 0.1;
				interface_->GetScale() *= (1 + 0.1);
			}
			//fps_.setScale(camera_.GetZoom(), camera_.GetZoom());
			camera_.SetZoom();
			window_->setView(camera_.GetCamera());
			camera_.GetZoom() = 1.f;
			/*
			std::cout << "wheel movement: " << e.mouseWheelScroll.delta << std::endl;
			std::cout << "mouse x: " << e.mouseWheelScroll.x << std::endl;
			std::cout << "mouse y: " << e.mouseWheelScroll.y << std::endl;
			*/
		}
	}
	

	// keyboard funcs
	void Window::KeyboardPressEvent(int key) {

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

		sun_ = new SolarSystem::Sun(60);
		for (const auto& planet : General::planetsInfo) {
			planetsBehind_.push_back(new SolarSystem::Planet(planet.name, planet.distance + 30, planet.sunPeriod,
				planet.diametr, planet.weight, planet.velocity));
		}
	}

	void Window::PlanetsUpdate() {

		for (auto& planet : planetsBehind_) {
			planet->UpdatePosition(dt_);
		}

		
		sun_->UpdatePosition(dt_);
		

		for (auto& planet : planetsFrontOf_) {
			planet->UpdatePosition(dt_);
		}


		
	}

	void Window::PlanetsDraw() const {

		for (const auto& planet : planetsBehind_) {
			planet->DrawEllipse(*window_);
		}

		for (const auto& planet : planetsFrontOf_) {
			planet->DrawEllipse(*window_);
		}


		for (const auto& planet : planetsBehind_) {
			planet->Draw(*window_);
		}

		
		sun_->Draw(*window_);
		

		for (const auto& planet : planetsFrontOf_) {
			planet->Draw(*window_);
		}

		
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



