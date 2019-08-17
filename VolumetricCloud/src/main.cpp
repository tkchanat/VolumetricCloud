#define _USE_MATH_DEFINES
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <algorithm>
#include <cmath>
#include <limits>
#include <iostream>
#include <vector>
#include <glm/glm/glm.hpp>
#include <stb/stb_image_write.h>

#define MAX_STEPS 128
#define MAX_DIST 128.0
#define SURF_DIST 0.025f

float DistanceFunction(const glm::vec3 &p) {
	glm::vec3 spherePosition = {0, 1, -6};
	float sphereRadius = 1;
	float sphereDist = glm::length(p - spherePosition) - sphereRadius;

	float planeDist = p.y;
	return std::min(sphereDist, planeDist);
}

glm::vec3 GetNormal(const glm::vec3 &pos) {
	const float eps = 0.01;
	float d = DistanceFunction(pos);
	float nx = DistanceFunction(pos + glm::vec3(eps, 0, 0)) - d;
	float ny = DistanceFunction(pos + glm::vec3(0, eps, 0)) - d;
	float nz = DistanceFunction(pos + glm::vec3(0, 0, eps)) - d;
	return glm::normalize(glm::vec3(nx, ny, nz));
}

float RayMarch(const glm::vec3& orig, const glm::vec3& dir) {
	float totalDist = 0.0f;
	// step through the ray
	for (int i = 0; i < MAX_STEPS; ++i) {
		glm::vec3 point = orig + dir * totalDist;
		float stepDist = DistanceFunction(point);
		totalDist += stepDist;
		if (stepDist < SURF_DIST || totalDist > MAX_DIST) break;
	}
	return totalDist;
}

int main() {
	const int width = 640;
	const int height = 480;
	const float fov = glm::radians(60.0f);

	glm::vec3 cameraPosition(0, 1, 0);
	int comp = 3;
	unsigned char* data = new unsigned char[width * height * comp];
	for (int j = 0; j < height; ++j) { // actual rendering loop
		for (int i = 0; i < width; ++i) {
			float dir_x = (i + 0.5) - width / 2.;
			float dir_y = -(j + 0.5) + height / 2.;    // this flips the image at the same time
			float dir_z = -height / (2.*tan(fov / 2.));
			glm::vec3 viewDirection = glm::normalize(glm::vec3(dir_x, dir_y, dir_z));
			float distance = RayMarch(cameraPosition, viewDirection);
			glm::vec3 hit = cameraPosition + viewDirection * distance;
			// Diffuse lighting
			glm::vec3 lightPosition(0, 5, -6);
			glm::vec3 lightNormal = glm::normalize(lightPosition - hit);
			glm::vec3 surfaceNormal = GetNormal(hit);
			float intensity = glm::dot(lightNormal, surfaceNormal);
			// Shadow
			float distToLight = RayMarch(hit + lightNormal, lightNormal);
			if (distToLight < glm::length(lightPosition - hit))
				intensity *= 0.1f;

			data[(i + j * width) * comp + 0] = glm::clamp(intensity * 255, 0.f, 255.f);
			data[(i + j * width) * comp + 1] = glm::clamp(intensity * 255, 0.f, 255.f);
			data[(i + j * width) * comp + 2] = glm::clamp(intensity * 255, 0.f, 255.f);
		}
	}

	int result = stbi_write_png("raymarch_test.png", width, height, comp, (const void*)data, 0);
	if (result == 0)
	{
		std::cerr << "Error while writing image!" << std::endl;
	}
	return 0;
}