#include <algorithm>
#include <math.h>
#include "BitmapHeaders.hpp"
#include "GifHeaders.hpp"

template <typename Func>
BMP generateFull(int width, int height, int bitsPerPixel, Func &&generator) {
	BMP bmp(width, height, bitsPerPixel == 4 ? true : false);
	bmp.data.resize(bitsPerPixel * width * height);

	std::generate(bmp.data.begin(), bmp.data.end(), generator);
	return bmp;
}

template <typename GenFunc, typename ModFunc>
BMP generateLines(int width, int height, int bitsPerPixel, GenFunc &&generator,
				  ModFunc &&modifier) {
	BMP bmp(width, height, bitsPerPixel == 4 ? true : false);
	bmp.data.clear();
	for (int row = 0; row < height; row++) {
		std::generate_n(std::back_insert_iterator<decltype(bmp.data)>(bmp.data),
						bitsPerPixel * width, generator);

		auto beg = bmp.data.begin() + row * bitsPerPixel * width;
		auto end = bmp.data.end();
		modifier(beg, end);
	}
	return bmp;
}


void writePix() {

	auto width = 1000, height = 1000, bitsPerPixel = 4;
	auto generator = []() -> unsigned char { return rand() % 255; };
	BMP bmp0 = generateFull(width, height, 4, generator);
	bmp0.write("bmp0.bmp");

	BMP bmp1 = generateLines(
		width, height, 4, generator,
		[=](const auto &begin, const auto &end) mutable {
			std::sort(begin, end);
			std::rotate(begin, begin + rand() % (bitsPerPixel * width), end);
		});
	bmp1.write("bmp1.bmp");

	double n = 0;
	int i = 0;
	BMP bmp2 =
		generateFull(width, height, 4, [n, i]() mutable -> unsigned char {
			i++;
			if (i == 10) {
				i = 1;
				n += .00011;
			}
			return 255 * (1 + sin(n * i)) / 2;
		});
	bmp2.write("bmp2.bmp");

	BMP bmp3 = generateLines(width, height, 4, generator,
							 [=](const auto &begin, const auto &end) mutable {
								 std::sort(begin, end);
								 auto nth =
									 begin + rand() % (bitsPerPixel * width);
								 std::nth_element(begin, nth, end);
							 });
	bmp3.write("bmp3.bmp");


	BMP bmp4 = generateLines(width, height, 4, generator,
							 [=](const auto &begin, const auto &end) mutable {
								 std::sort(begin, end);
								 auto nth =
									 begin + rand() % (bitsPerPixel * width);
								 std::partial_sort(begin, nth, end);
							 });
	bmp4.write("bmp4.bmp");

	std::vector<uint8_t> black(width * height * 4, 0);
	std::vector<uint8_t> white(width * height * 4, 255);

	auto fileName = "bwgif.gif";
	int delay = 100;
	GifWriter g;
	GifBegin(&g, fileName, width, height, delay);
	GifWriteFrame(&g, black.data(), width, height, delay);
	GifWriteFrame(&g, bmp0.data.data(), width, height, delay);
	GifWriteFrame(&g, bmp1.data.data(), width, height, delay);
	GifWriteFrame(&g, bmp2.data.data(), width, height, delay);
	GifWriteFrame(&g, bmp3.data.data(), width, height, delay);
	GifWriteFrame(&g, bmp4.data.data(), width, height, delay);


	GifWriteFrame(&g, white.data(), width, height, delay);
	GifEnd(&g);
}
int main() {
	writePix();
	return 0;
}
