#pragma once
#include <string>


#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


namespace General {
	constexpr float	WIDTH = 1600;
	constexpr float	HEIGHT = 900;
	
	struct PlanetInfo {
		std::string name;
		float distance;
		float sunPeriod; // day
		float diametr; // * 10^4
		float weight; // * 10^25
		float velocity;
	};

	static float distanceScale = 10;
	static float diametrScale = 5;
	const float ONE_YEAR = 365.24f;
	static size_t SPRITE_SIZE = 500;
	//static float PERIOD_SCALE = 0.055;
	static float PERIOD_SCALE = 20;

	static std::vector<PlanetInfo> planetsInfo = {
	//	  name		dist					period			         D					weight	vel
		{"Mercury", 0.39f * distanceScale,	88.f,				0.48f * diametrScale,	0.03f,	47.f},
		{"Venus",	0.72f * distanceScale,	224.7f,				1.21f * diametrScale,	0.49f,	35.f},
		{"Earth",	1.f * distanceScale,	ONE_YEAR,			1.27f * diametrScale,	0.6f,	30.f},
		{"Mars",	1.52f * distanceScale,	687.f,				0.68f * diametrScale,	0.06f,	24.f},
		{"Jupiter", 5.2f * distanceScale,	11.9f * ONE_YEAR,	13.98f * diametrScale,	190.f,	13.f},
		{"Saturn",	9.54f * distanceScale,	29.5f * ONE_YEAR,	11.6f * diametrScale,	56.8f,	9.7f},
		{"Uranus",	19.19f * distanceScale,	84.f * ONE_YEAR,	5.08f * diametrScale,	8.7f,	6.8f},
		{"Neptune", 30.07f * distanceScale,	167.8f * ONE_YEAR,	4.86f * diametrScale,	10.3f,	5.4f}
	};

	// Fonts
	class Fonts {
	public:
		static sf::Font MAIN_FONT;
		static void Initialization();
		
	};

	


}


