#include <string>
#include <iostream>


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
	}

	Window::~Window() {

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
		

		planet_.UpdatePosition(dt_);
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


	void Window::Render() {
		// clear
		window_->clear();

		// draw
		Draw();

		// display
		window_->display();
	}

	void Window::Draw() {
		
		planet_.Draw(*window_);


		cursor_.Draw(*window_);
		window_->draw(fps_);
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



