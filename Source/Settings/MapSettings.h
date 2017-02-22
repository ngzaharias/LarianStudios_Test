#ifndef MAP_SETTINGS_H
#define MAP_SETTINGS_H

#include <rapidjson/document.h>

struct MapSettings
{
	void Parse(const rapidjson::Value& value);

	int lives = 3;
	int score = 0;
	std::string fontpath = "Assets/Fonts/kenpixel_square.ttf";
};
#endif