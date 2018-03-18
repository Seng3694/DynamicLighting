#include "FpsCounter.hpp"

void FpsCounter::update(const float &dt)
{
	_fps = 1.0f / dt;
}

float FpsCounter::getFps() const
{
	return _fps;
}