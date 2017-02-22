#ifndef BRICK_SETTINGS_H
#define BRICK_SETTINGS_H

#include <rapidjson/document.h>
#include <SFML/System/Vector2.hpp>

struct BrickSettings
{
	void Parse(const rapidjson::Value& value);
	
	sf::Vector2f size = sf::Vector2f(100.0f, 50.0f);
	sf::Vector2f position = sf::Vector2f(400.0f, 300.0f);
};
#endif