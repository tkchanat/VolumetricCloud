#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <iostream>
#include "CLI11.hpp"
#include "stb_image_write.h"

void GeneratePerlin(char const* filename)
{
	int w = 100;
	int h = 100;
	int comp = 1;
	unsigned char* data = new unsigned char[w * h * comp];
	for (int i = 0; i < w * h * comp; i += comp)
	{
		data[i] = rand() % 255;
	}
	int stride_in_bytes = sizeof(unsigned char) * 4;

	int result = stbi_write_png(filename, w, h, comp, (const void*) data, 0);
	if (result == 0)
	{
		std::cout << "Error!" << std::endl;
	}
}

int main(int argc, char* argv[])
{
	srand(0);
	CLI::App app{ "An command line application to generate Perlin noise and Worley noise for creating a weather map. This application is coupled with the VolumetricCloud project.\n" };

	// Define options
	bool perlin;
	bool worley;
	std::string output;
	app.add_option("-p", perlin, "Generate a Perlin noise");
	app.add_option("-w", worley, "Generate a Worley noise");
	app.add_option("-o", output, "Output destination")->required(true);
	CLI11_PARSE(app, argc, argv);

	// Generate maps
	if (perlin)
	{
		GeneratePerlin(output.c_str());
	}

	return 0;
}