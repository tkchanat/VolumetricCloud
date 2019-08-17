#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <iostream>
#include "CLI11.hpp"
#include "stb_image_write.h"
#include "PerlinNoise.h"

void GeneratePerlin(char const* filename)
{
	PerlinNoise perlin(0);
	int w = 256;
	int h = 256;
	int comp = 1;
	int scale = 8;
	unsigned char* data = new unsigned char[w * h * comp];
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			float x = (float)j / (float)w * scale;
			float y = (float)i / (float)h * scale;
			data[i * w + j] = perlin.noise(x, y, 0) * 255;
		}
	}
	int stride_in_bytes = w * comp * sizeof(unsigned char);

	int result = stbi_write_png(filename, w, h, comp, (const void*) data, 0);
	if (result == 0)
	{
		std::cerr << "Error while writing image!" << std::endl;
	}

	// Release memory
	if (data)
	{
		delete[] data;
		data = nullptr;
	}
}

int main(int argc, char* argv[])
{
	CLI::App app{ "An command line application to generate Perlin noise and Worley noise for creating a weather map. This application is coupled with the VolumetricCloud project.\n" };

	// Define options
	std::string type = "Perlin";
	std::string output = "no_name.png";
	app.add_option("-t,--type", type, "Type of noise (Perlin / Worley)")->required(true);
	app.add_option("-o,--output", output, "Output destination")->required(true);
	CLI11_PARSE(app, argc, argv);

	// Generate maps
	if (type == "Perlin")
	{
		GeneratePerlin(output.c_str());
	}
	else if (type == "Worley")
	{
		//GenerateWorley();
	}
	else
	{
		std::cerr << "No such noise type (Available: Perlin / Worley)" << std::endl;
	}

	return 0;
}