#include "FpsCounter.h"

void seng::FpsCounter::update(const float &dt)
{
	_fps = 1.0f / dt;
}

float seng::FpsCounter::getFps() const
{
	return _fps;
}