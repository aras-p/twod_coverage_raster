#include "CoverageRaster.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"


static inline float rand01()
{
	return float(rand()) / RAND_MAX;
}


int main(int argc, const char * argv[])
{
	const int kWidth = 2048;
	const int kHeight = 1024;
	const int kTriangles = 1000;
	const int kVertices = kTriangles*3;
	
	srand(0);
	
	int* indices = new int[kTriangles*3];
	float* vertices = new float[kVertices*2];
	unsigned char* image = new unsigned char[kWidth * kHeight];
	memset (image, 0, kWidth*kHeight);
	
	for (int i = 0; i < kTriangles; ++i)
	{
		float x = rand01();
		float y = rand01();
		vertices[i*6+0] = x;
		vertices[i*6+1] = y;
		vertices[i*6+2] = x + rand01()*0.4f-0.2f;
		vertices[i*6+3] = y + rand01()*0.4f-0.2f;
		vertices[i*6+4] = x + rand01()*0.4f-0.2f;
		vertices[i*6+5] = y + rand01()*0.4f-0.2f;
	}
	for (int i = 0; i < kTriangles; ++i)
	{
		indices[i*3+0] = i*3+0;
		indices[i*3+1] = i*3+1;
		indices[i*3+2] = (rand01() < 0.9f) ? (i*3+2) : (rand()%kVertices);
	}
	
	clock_t t0 = clock();
	
	RasterizeCoverage(kTriangles, indices, vertices, kWidth, kHeight, image);

	clock_t t1 = clock();
	float dt = float(t1-t0) / CLOCKS_PER_SEC;
	
	stbi_write_png("output.png", kWidth, kHeight, 1, image, kWidth);
	printf("Rasterized %i tris into %ix%i: %ims\n", kTriangles, kWidth, kHeight, (int)(dt * 1000.0f));
	
	delete[] image;
	delete[] vertices;
	delete[] indices;
    return 0;
}
