#pragma once
#include "../CImg/CImg.h"
#include <cstdint>
#include <chrono>
#include <iostream>

using namespace std::chrono;

using namespace cimg_library;

class MPI
{
public:
	static void EdgeDetection(int argc, char* argv[]);
private:
	static void RGBToGrayScale(CImg<int>& img);
	static uint8_t GetValueForPixel(const CImg<int>& img, int x, int y);
};

