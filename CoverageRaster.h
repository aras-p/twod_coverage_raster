#pragma once

void RasterizeCoverage(
					   int triCount,
					   const int* indices,
					   const float* vertices,
					   int width,
					   int height,
					   char* image
					   );
