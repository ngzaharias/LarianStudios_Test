#ifndef PADDLE_SETTINGS_H
#define PADDLE_SETTINGS_H

#include <rapidjson/document.h>
#include <SFML/System/Vector2.hpp>

struct PaddleSettings
{
	void Parse(const rapidjson::Value& value);

	sf::Vector2f size = sf::Vector2f(20.0f, 20.0f);
	sf::Vector2f position = sf::Vector2f(400.0f, 400.0f);
};

#endif