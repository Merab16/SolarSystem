#pragma once
#include <SFML/Graphics.hpp>

#include "SolarSystem.h"


namespace Camera {
	class Camera {
	private:
		sf::View camera_;
		sf::Vector2f offset_;
		float offsetScale = 2.f;
		float zoom_ = 1.f;
		sf::Vector2f start_{ 0.f, 0.f };

		// focus
		const SolarSystem::Planet* planet_ = nullptr;

	private:


	public:
		Camera();


		
		void Start(const sf::Vector2f& pos);
		sf::Vector2f Finish(const sf::Vector2f& pos);
		void SetCenter();
		void SetZoom();
		void SetPlanet(const SolarSystem::Planet* planet);
		void Update(sf::RenderWindow& window);

		// getters
		const sf::View& GetCamera() const { return camera_; }
		sf::Vector2f& GetOffset() { return offset_; }
		const sf::Vector2f& GetOffset() const { return offset_; }
		float& GetZoom() { return zoom_; }

	};
}