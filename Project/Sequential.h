#pragma once
#include "../CImg/CImg.h"
#include <iostream>
#include <chrono>
using namespace std::chrono;
using namespace cimg_library;

class Sequential
{
public:
	static void EdgeDetection();
private:
	static void RGBToGrayScale(CImg<int>& img);
	static uint8_t GetValueForPixel(const CImg<int>& img, int x, int y);
};

