#pragma once

namespace seng
{
	class Random
	{
	public:
		Random();

		void setSeed(const unsigned int& seed);
		unsigned int getSeed() const;

		int next() const;
		int range(const int &fromIncl, const int &toIncl) const;

	private:
		unsigned int _seed;
	};
}