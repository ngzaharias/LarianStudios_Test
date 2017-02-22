#include "MapSettings.h"

#include "Utility/JsonHelper.h"

void MapSettings::Parse(const rapidjson::Value& value)
{
	if (value.IsObject() == false)
		return;

	lives = JsonHelper::ParseInt(value, "lives", lives);
	score = JsonHelper::ParseInt(value, "score", score);
	fontpath = JsonHelper::ParseString(value, "font", fontpath.c_str());
}
