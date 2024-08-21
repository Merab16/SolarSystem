#include <iostream>


#include "../Headers/Camera.h"
#include "../Headers/General.h"



namespace Camera {
	
	// constr & destr
	Camera::Camera() {
		offset_ = sf::Vector2f(General::WIDTH / 2, General::HEIGHT / 2);
		camera_.setCenter(offset_);
		camera_.setSize(General::WIDTH, General::HEIGHT);
		camera_.zoom(zoom_);
	}


	// public
	void Camera::Start(const sf::Vector2f& pos) {
		start_ = pos;
	}

	sf::Vector2f Camera::Finish(const sf::Vector2f& pos) {
		return {start_.x - pos.x, start_.y - pos.y };
	}

	void Camera::SetCenter() {
		camera_.setCenter(offset_);
	}

	void Camera::SetZoom() {
		camera_.zoom(zoom_);
	}

}