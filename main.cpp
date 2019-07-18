#include <algorithm>
#include "BitmapHeaders.hpp"

int main() {
	BMP bmp(100, 100, false);
	int r{}, g{}, b{};
	bmp.data.clear();
	for (int row = 0; row < 100; row++) {
		for (int col = 0; col < 100; col++) {
			bmp.data.push_back(rand() % 255);
			bmp.data.push_back(rand() % 255);
			bmp.data.push_back(rand() % 255);
		}
		std::sort(bmp.data.begin() + row * 300,
				  bmp.data.begin() + row * 300 + 300);
		std::rotate(bmp.data.begin() + row * 300,
					bmp.data.begin() + row * 300 + rand() % 300,
					bmp.data.begin() + row * 300 + 300);
	}
	bmp.write("bbb.bmp");
	return 0;
}
