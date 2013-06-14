#pragma once

// Rasterize 2D triangles into 1 byte-per-pixel image.
// @param indices Index buffer, 3 ints per triangle.
// @param vertices Vertices, 2 floats per vertex; 0..1 range over the image.
void RasterizeCoverage(
					   int triCount,
					   const int* indices,
					   const float* vertices,
					   int width,
					   int height,
					   unsigned char* image
					   );
