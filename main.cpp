#include <algorithm>
#include <math.h>

#include <range/v3/view.hpp>
#include <range/v3/view/generate.hpp>
#include <range/v3/action.hpp>

#include "BitmapHeaders.hpp"

int main() {
	BMP bmp(1000, 1000, false);
	// bmp.data.resize(3000000);
	double n = 0;
	int i = 0;
	int hz = 0;

	bmp.data = ranges::view::generate([n, i, hz]() mutable -> unsigned char {
				   i++;
				   if (i == 10) {
					   i = 1;
					   n += .00011;
				   }
				   auto res = 255 * (1 + sin(n * i)) / 2;
				   return res;
			   })
			   | ranges::view::take(3000000);


	bmp.write("bbb.bmp");
	return 0;
}
