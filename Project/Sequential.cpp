#include "Sequential.h"

void Sequential::RGBToGrayScale(CImg<int>& img)
{
    for (int i = 0; i < img.width(); i++)
    {
        for (int j = 0; j < img.height(); j++)
        {
            auto R = img(i, j, 0);
            auto G = img(i, j, 1);
            auto B = img(i, j, 2);
            auto Grey = sqrt((R * R + B * B + G * G) / 3);
            img(i, j, 0) = Grey;
            img(i, j, 1) = Grey;
            img(i, j, 2) = Grey;
        }
    }
}

void Sequential::EdgeDetection()
{
    CImg<int> img;
    img.load("sample.BMP");
    CImg<int> newImg = img;

    auto start = high_resolution_clock::now();
    RGBToGrayScale(img);

    for (int x = 1; x < img.width() - 1; x++)
    {
        for (int y = 1; y < img.height() - 1; y++)
        {
            auto val = GetValueForPixel(img, x, y);
            newImg(x, y, 0) = val;
            newImg(x, y, 1) = val;
            newImg(x, y, 2) = val;
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    std::cout << "Sequential " << duration.count() << " miliseconds" << std::endl;
    //newImg.display();
}

const int KerX[3][3] =
{
    {-1, -2, -1},
    { 0,  0,  0},
    {+1, +2, +1}
};

const int KerY[3][3] =
{
    {-1, 0, +1},
    {-2, 0, +2},
    {-1, 0, +1}
};

uint8_t Sequential::GetValueForPixel(const CImg<int>& img, int x, int y)
{
    cimg_float64 Gx = 0;
    cimg_float64 Gy = 0;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            int px = x + (i - 1);
            int py = y + (j - 1);

            int pvalue = img.atXY(px, py, 0);

            Gx += KerX[i][j] * pvalue;
            Gy += KerY[i][j] * pvalue;
        }
    }


    // Summing is the default operation
    double l_sum = std::abs(Gx) + std::abs(Gy);

    return static_cast<int>(std::round(l_sum));
}
