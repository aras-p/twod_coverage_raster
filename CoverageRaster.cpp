#include "CoverageRaster.h"
#include <algorithm>

// Basically from Fabian "ryg" Giesen's
// http://fgiesen.wordpress.com/2013/02/08/triangle-rasterization-in-practice/
// http://fgiesen.wordpress.com/2013/02/10/optimizing-the-basic-rasterizer/


struct Point2D
{
	int x, y;
};

static int orient2d(const Point2D& a, const Point2D& b, const Point2D& c)
{
	return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
}

template<typename T>
static inline T min3(T a, T b, T c)
{
	return std::min(a, std::min(b,c));
}

template<typename T>
static inline T max3(T a, T b, T c)
{
	return std::max(a, std::max(b,c));
}

static void PutPixel (int x, int y, int width, int height, unsigned char* image)
{
	//image[y * width + x] = 0xFF;
	image[y * width + x] += 8;
}

static void RasterizeTri(
						 const Point2D& v0, const Point2D& v1, const Point2D& v2,
						 int width, int height, unsigned char* image
						 )
{
	// Compute triangle bounding box
	int minX = min3(v0.x, v1.x, v2.x);
	int minY = min3(v0.y, v1.y, v2.y);
	int maxX = max3(v0.x, v1.x, v2.x);
	int maxY = max3(v0.y, v1.y, v2.y);

	// Clip against bounds
	minX = std::max(minX, 0);
	minY = std::max(minY, 0);
	maxX = std::min(maxX, width - 1);
	maxY = std::min(maxY, height - 1);

	// Rasterize
	Point2D p;
	for (p.y = minY; p.y <= maxY; p.y++)
	{
		for (p.x = minX; p.x <= maxX; p.x++)
		{
			// Determine barycentric coordinates
			int w0 = orient2d(v1, v2, p);
			int w1 = orient2d(v2, v0, p);
			int w2 = orient2d(v0, v1, p);

			// If p is on or inside all edges, render pixel.
			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				PutPixel (p.x, p.y, width, height, image);
			}
		}
	}
}


void RasterizeCoverage(
					   int triCount,
					   const int* indices,
					   const float* vertices,
					   int width,
					   int height,
					   unsigned char* image
)
{
	for (int t = 0; t < triCount; ++t, indices += 3)
	{
		int idx0 = indices[0]*2, idx1 = indices[1]*2, idx2 = indices[2]*2;
		Point2D v0, v1, v2;
		v0.x = vertices[idx0] * width;
		v0.y = vertices[idx0+1] * height;
		v1.x = vertices[idx1] * width;
		v1.y = vertices[idx1+1] * height;
		v2.x = vertices[idx2] * width;
		v2.y = vertices[idx2+1] * height;
		
		if (orient2d(v0, v1, v2) < 0)
		{
			std::swap (v1, v2);
		}
		
		RasterizeTri(v0, v1, v2, width, height, image);
	}
}
