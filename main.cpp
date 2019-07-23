#include <algorithm>
#include <math.h>

#include <algorithm>
#include "BitmapHeaders.hpp"

int main() {

	auto width = 1000, height = 1000;
	BMP bmp0(width, height, false);
	bmp0.data.resize(3 * width * height);

	std::generate(bmp0.data.begin(), bmp0.data.end(),
				  []() -> unsigned char { return rand() % 255; });

	bmp0.write("bmp0.bmp");

	BMP bmp1(width, height, false);

	bmp1.data.clear();
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			bmp1.data.push_back(rand() % 255);
			bmp1.data.push_back(rand() % 255);
			bmp1.data.push_back(rand() % 255);
		}
		std::sort(bmp1.data.begin() + row * 3 * height,
				  bmp1.data.begin() + row * 3 * height + 3 * height);
		std::rotate(bmp1.data.begin() + row * 3 * width,
					bmp1.data.begin() + row * 3 * width + rand() % (3 * width),
					bmp1.data.begin() + row * 3 * width + 3 * width);
	}
	bmp1.write("bmp1.bmp");

	BMP bmp2(width, height, false);
	bmp2.data.resize(3 * width * height);
	double n = 0;
	int i = 0;

	std::generate(bmp2.data.begin(), bmp2.data.end(),
				  [n, i]() mutable -> unsigned char {
					  i++;
					  if (i == 10) {
						  i = 1;
						  n += .00011;
					  }
					  return 255 * (1 + sin(n * i)) / 2;
				  });

	bmp2.write("bmp2.bmp");

	return 0;
}
