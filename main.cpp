#include <algorithm>
#include <math.h>
#include "BitmapHeaders.hpp"

template <typename Func>
BMP generateFull(unsigned int width, unsigned int height,
				 unsigned int bitsPerPixel, Func &&generator) {
	BMP bmp(width, height, bitsPerPixel == 4 ? true : false);
	bmp.data.resize(bitsPerPixel * width * height);

	std::generate(bmp.data.begin(), bmp.data.end(), generator);
	return bmp;
}

template <typename GenFunc, typename ModFunc>
BMP generateLines(unsigned int width, unsigned int height,
				  unsigned int bitsPerPixel, GenFunc &&generator,
				  ModFunc &&modifier) {
	BMP bmp(width, height, bitsPerPixel == 4 ? true : false);
	bmp.data.clear();
	for (unsigned int row = 0; row < height; row++) {
		std::generate_n(std::back_insert_iterator<decltype(bmp.data)>(bmp.data),
						bitsPerPixel * width, generator);

		auto beg = bmp.data.begin() + row * bitsPerPixel * width;
		auto end = bmp.data.end();
		modifier(beg, end);
	}
	return bmp;
}


void writePix() {

	unsigned int width = 1000, height = 1000, bitsPerPixel = 3;
	auto generator = []() -> unsigned char { return rand() % 255; };
	BMP bmp0 = generateFull(width, height, bitsPerPixel, generator);
	bmp0.write("bmp0.bmp");


	BMP bmp1 = generateLines(
		width, height, 3, generator,
		[=](const auto &begin, const auto &end) { std::sort(begin, end); });
	bmp1.write("bmp1.bmp");


	BMP bmp2 = generateFull(width, height, bitsPerPixel,
							[n = .0, i = 0]() mutable -> unsigned char {
								i++;
								if (i == 10) {
									i = 1;
									n += .011;
								}
								return uint8_t(255 * (1 + sin(n * i)) / 2);
							});
	bmp2.write("bmp2.bmp");


	BMP bmp3 = generateLines(
		width, height, 3, generator, [=](const auto &begin, const auto &end) {
			std::nth_element(begin, begin + (rand() % 1000), end);
		});
	bmp3.write("bmp3.bmp");

	BMP bmp4 = generateLines(
		width, height, 3, generator, [=](const auto &begin, const auto &end) {
			std::nth_element(begin, begin + (rand() % 1000), end);
			std::rotate(begin, begin + (rand() % 500), end);
		});
	bmp4.write("bmp4.bmp");

	BMP bmp5 = generateLines(
		width, height, 3, generator, [=](const auto &begin, const auto &end) {
			std::sort(begin, end);
			std::rotate(begin, begin + (rand() % 500), end);
		});
	bmp5.write("bmp5.bmp");
}
int main() {
	writePix();
	return 0;
}
