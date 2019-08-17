#include "PerlinNoise.h"
#include <numeric>
#include <random>

PerlinNoise::PerlinNoise(unsigned int seed)
{
	p.resize(256);
	std::iota(p.begin(), p.end(), 0); // Fill p with values from 0 to 255
	std::default_random_engine engine(seed); // Initialize a random engine with seed
	std::shuffle(p.begin(), p.end(), engine); // Shuffle using the above random engine
	p.insert(p.end(), p.begin(), p.end()); // Duplicate the permutation vector
}
// Get a noise value, for 2D images z can have any value
double PerlinNoise::noise(float x, float y, float z)
{
	// Find the unit cube that contains the point [0, 256)
	int X = (int)x % 256;
	int Y = (int)y % 256;
	int Z = (int)z % 256;

	// Find relative x, y, z of point in unit cube [0, 1)
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);

	// Compute fade curves for each of x, y, z
	float u = fade(x);
	float v = fade(y);
	float w = fade(z);

	// Hash coordinates of the 8 cube corners
	int A = p[X] + Y;
	int AA = p[A] + Z;
	int AB = p[A + 1] + Z;
	int B = p[X + 1] + Y;
	int BA = p[B] + Z;
	int BB = p[B + 1] + Z;

	// Add blended results from 8 corners of cube
	float res = lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x - 1, y, z)), lerp(u, grad(p[AB], x, y - 1, z), grad(p[BB], x - 1, y - 1, z))), lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1), grad(p[BA + 1], x - 1, y, z - 1)), lerp(u, grad(p[AB + 1], x, y - 1, z - 1), grad(p[BB + 1], x - 1, y - 1, z - 1))));
	return (res + 1.0) / 2.0;
}

double PerlinNoise::fade(float t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}
double PerlinNoise::lerp(float t, float a, float b)
{
	return a + t * (b - a);
}
double PerlinNoise::grad(int hash, float x, float y, float z)
{
	int h = hash & 15;
	// Convert lower 4 bits of hash into 12 gradient directions
	float u = h < 8 ? x : y,
		v = h < 4 ? y : h == 12 || h == 14 ? x : z;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
