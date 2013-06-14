#pragma once

void RasterizeCoverage(
					   int triCount,
					   const int* indices,
					   const float* vertices,
					   int width,
					   int height,
					   unsigned char* image
					   );
