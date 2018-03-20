#pragma once

class FpsCounter
{
public:
	void update(const float &dt);
	float getFps() const;

private:
	float _fps;
};