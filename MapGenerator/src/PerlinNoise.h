#pragma once
#include <vector>

class PerlinNoise {
	// The permutation vector
	std::vector<int> p;
public:
	// Generate a new permutation vector based on the value of seed
	PerlinNoise(unsigned int seed);
	// Get a noise value, for 2D images z can have any value
	double noise(float x, float y, float z);
private:
	double fade(float t);
	double lerp(float t, float a, float b);
	double grad(int hash, float x, float y, float z);
};