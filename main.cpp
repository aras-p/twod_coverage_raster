#include "CoverageRaster.h"
#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


static inline float rand01()
{
	return float(rand()) / RAND_MAX;
}


int main(int argc, const char * argv[])
{
	const int kWidth = 960;
	const int kHeight = 600;
	const int kTriangles = 1000;
	const int kVertices = 4000;
	
	srand(0);
	
	int* indices = new int[kTriangles*3];
	float* vertices = new float[kVertices*2];
	unsigned char* image = new unsigned char[kWidth * kHeight];
	memset (image, 0, kWidth*kHeight);
	
	for (int i = 0; i < kVertices*2; ++i)
		vertices[i] = rand01() * 0.8f + 0.1f;
	for (int i = 0; i < kTriangles*3; ++i)
		indices[i] = rand() % kVertices;
	
	RasterizeCoverage(kTriangles, indices, vertices, kWidth, kHeight, image);
	
	stbi_write_png("output.png", kWidth, kHeight, 1, image, kWidth);
	
	delete[] image;
	delete[] vertices;
	delete[] indices;
    return 0;
}
