#include "BallSettings.h"

#include "Utility/JsonHelper.h"

void BallSettings::Parse(const rapidjson::Value& value)
{
	if (value.IsObject() == false)
		return;

	size.x = JsonHelper::ParseFloat(value, "size_x", size.x);
	size.y = JsonHelper::ParseFloat(value, "size_y", size.y);

	position.x = JsonHelper::ParseFloat(value, "position_x", position.x);
	position.y = JsonHelper::ParseFloat(value, "position_y", position.y);

	velocityMin = JsonHelper::ParseFloat(value, "velocity_min", velocityMin);
	velocityMax = JsonHelper::ParseFloat(value, "velocity_max", velocityMax);
}
