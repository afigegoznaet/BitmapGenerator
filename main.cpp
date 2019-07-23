#include <algorithm>
#include <math.h>
#include "BitmapHeaders.hpp"


//#include <range/v3/view.hpp>
//#include <range/v3/view/generate.hpp>
//#include <range/v3/action.hpp>

int main() {

	auto width = 1000, height = 1000, bitsPerPixel = 3;
	BMP bmp0(width, height, false);
	bmp0.data.resize(3 * width * height);

	std::generate(bmp0.data.begin(), bmp0.data.end(),
				  []() -> unsigned char { return rand() % 255; });

	bmp0.write("bmp0.bmp");

	BMP bmp1(width, height, false);
	bmp1.data.clear();
	for (int row = 0; row < height; row++) {
		std::generate_n(
			std::back_insert_iterator<decltype(bmp1.data)>(bmp1.data),
			bitsPerPixel * width,
			[]() -> unsigned char { return rand() % 255; });


		auto beg = bmp1.data.begin() + row * bitsPerPixel * width;
		auto end = bmp1.data.end();
		std::sort(beg, end);
		std::rotate(beg, beg + rand() % (bitsPerPixel * width), end);
		// ranges
		//
	}
	bmp1.write("bmp1.bmp");

	BMP bmp2(width, height, false);
	bmp2.data.resize(bitsPerPixel * width * height);
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
