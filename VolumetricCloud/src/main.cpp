#define _USE_MATH_DEFINES
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <stb_image_write.h>

const float sphere_radius = 1.5;

float signed_distance(const glm::vec3 &p) {
	return glm::length(p) - sphere_radius;
}

bool sphere_trace(const glm::vec3 &orig, const glm::vec3 &dir, glm::vec3 &pos) {
	pos = orig;
	for (int i = 0; i < 128; i++) {
		float d = signed_distance(pos);
		if (d < 0) return true;
		pos = pos + dir * std::max(d * 0.1f, .01f);
	}
	return false;
}

int main() {
	const int   width = 640;
	const int   height = 480;
	const float fov = M_PI / 3.;

	int comp = 3;
	unsigned char* data = new unsigned char[width * height * comp];

	for (int j = 0; j < height; ++j) { // actual rendering loop
		for (int i = 0; i < width; ++i) {
			float dir_x = (i + 0.5) - width / 2.;
			float dir_y = -(j + 0.5) + height / 2.;    // this flips the image at the same time
			float dir_z = -height / (2.*tan(fov / 2.));
			glm::vec3 hit;
			if (sphere_trace(glm::vec3(0, 0, 3), glm::normalize(glm::vec3(dir_x, dir_y, dir_z)), hit)) { // the camera is placed to (0,0,3) and it looks along the -z axis
				data[(i + j * width) * comp + 0] = 255;
				data[(i + j * width) * comp + 1] = 255;
				data[(i + j * width) * comp + 2] = 255;
			}
			else {
				data[(i + j * width) * comp + 0] = 153; // background color
				data[(i + j * width) * comp + 1] = 180; // background color
				data[(i + j * width) * comp + 2] = 250; // background color
			}
		}
	}

	int result = stbi_write_png("raymarch_test.png", width, height, comp, (const void*)data, 0);
	if (result == 0)
	{
		std::cerr << "Error while writing image!" << std::endl;
	}

	return 0;
}