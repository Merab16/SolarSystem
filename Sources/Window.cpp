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
		
		// camera
		cameraOffset_ = sf::Vector2f(General::WIDTH / 2, General::HEIGHT / 2);
		cameraPosition_.setCenter(cameraOffset_);
		cameraPosition_.setSize(General::WIDTH, General::HEIGHT);


		// window
		window_->setFramerateLimit(144);
		window_->setView(cameraPosition_);

		// font && fps
		font_.loadFromFile("Fonts/CascadiaCode.ttf");
		fps_.setFont(font_);
		fps_.setCharacterSize(16);
		
	}

	void Window::Update() {
		UpdateDt();

		UpdateSFMLEvents();
		
		UpdateMenuPosition();

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

	void Window::UpdateMenuPosition() {
		fps_.setPosition(sf::Vector2f{ 
			(cameraOffset_.x - General::WIDTH / 2),
			(cameraOffset_.y - General::HEIGHT / 2)
		});

		
	}

	// mouse funcs
	void Window::MousePressEvent(const sf::Event& e) {
		if (e.type == sf::Event::MouseButtonPressed) {
			if (e.mouseButton.button == sf::Mouse::Left) {
				startCamera_ = cursor_.GetPosition();
				isPressed_ = true;
			}
		}

	}

	void Window::MouseReleasedEvent(const sf::Event& e) {
		if (e.type == sf::Event::MouseButtonReleased) {
			if (e.mouseButton.button == sf::Mouse::Left) {
				isPressed_ = false;

			}
		}
	}

	void Window::MouseMoveEvent(const sf::Event& e) {
		cursor_.UpdatePos(*window_, cameraOffset_);

		if (isPressed_) {
			auto finish = cursor_.GetPosition();
			sf::Vector2f offset{};
			offset.x = startCamera_.x - finish.x;
			offset.y = startCamera_.y - finish.y;
			cameraOffset_ += offset;
			
			startCamera_ = cursor_.GetPosition();

			cameraPosition_.setCenter(cameraOffset_);
			window_->setView(cameraPosition_);
		}
		
	}

	

	// keyboard funcs
	void Window::KeyboardPressEvent(int key) {
		switch (key) {
		case sf::Keyboard::Left:
			cameraOffset_.x -= cameraOffsetScale;
			break;
		case sf::Keyboard::Right:
			cameraOffset_.x += cameraOffsetScale;
			break;
		case sf::Keyboard::Up:
			cameraOffset_.y -= cameraOffsetScale;
			break;
		case sf::Keyboard::Down:
			cameraOffset_.y += cameraOffsetScale;
			break;
		}
		cameraPosition_.setCenter(cameraOffset_);
		window_->setView(cameraPosition_);
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



