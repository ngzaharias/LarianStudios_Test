#ifndef BALL_SETTINGS_H
#define BALL_SETTINGS_H

#include <rapidjson/document.h>
#include <SFML/System/Vector2.hpp>

struct BallSettings
{
	void Parse(const rapidjson::Value& document);

	sf::Vector2f size = sf::Vector2f(20.0f, 20.0f);
	sf::Vector2f position = sf::Vector2f(400.0f, 400.0f);
	float velocityMin = 500.0f;
	float velocityMax = 1500.0f;
};
#endif