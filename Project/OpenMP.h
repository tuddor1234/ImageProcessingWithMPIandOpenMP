#pragma once
#include "../CImg/CImg.h"
#include <cstdint>


using namespace cimg_library;

class OpenMP
{
public:
	static void EdgeDetection();
private:
	static void RGBToGrayScale(CImg<int>& img);
	static uint8_t GetValueForPixel(const CImg<int>& img, int x, int y);
};

