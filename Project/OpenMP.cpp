#include "OpenMP.h"
#include <omp.h>
#include <chrono>
#include <iostream>

using namespace std::chrono;

void OpenMP::EdgeDetection()
{
    CImg<int> img;
    img.load("sample.BMP");
    CImg<int> newImg = img;

    auto start = high_resolution_clock::now();
    RGBToGrayScale(img);
    

    int tid;
#pragma omp parallel private(tid)  num_threads(8)
    {
        tid = omp_get_thread_num();
        auto total = omp_get_num_threads();

        int widthSlice = (img.width() / total);
        int startWidth = widthSlice * tid;
        int endWidth = widthSlice * (tid + 1);

        for (int square = 0; square < total; square++)
        {
            int heightSlice = (img.height() / total);
            int startHeight = heightSlice * square;
            int endHeight = heightSlice * (square + 1);

            for (int x = startWidth ; x <= endWidth; x++)
            {
                for (int y = startHeight; y < endHeight; y++)
                {
                    auto val = GetValueForPixel(img, x, y);
                    newImg(x, y, 0) = val;
                    newImg(x, y, 1) = val;
                    newImg(x, y, 2) = val;
                }
            }

        }
      

    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    std::cout << "OpenMP " << duration.count() << " miliseconds" << std::endl;
    newImg.save("OpenMP.bmp");
    //newImg.display();
}



void OpenMP::RGBToGrayScale(CImg<int>& img)
{
    
    int tid;
#pragma omp parallel private(tid) num_threads(8)
    {
        auto total = omp_get_num_threads();
        tid = omp_get_thread_num();
        
        int widthSlice = (img.width() / total);
        int startWidth = widthSlice * tid;
        int endWidth = widthSlice * (tid +1) -1;
        
        for (int square = 0; square < total; square++)
        {
            int heightSlice = (img.height() / total);
            int startHeight = heightSlice * square;
            int endHeight = heightSlice * (square + 1) ;

            for (int i = startWidth; i <= endWidth; i++)
            {
                for (int j = startHeight; j < endHeight; j++)
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
    
    }  
}

uint8_t OpenMP::GetValueForPixel(const CImg<int>& img, int x, int y)
{
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

    double Gx = 0;
    double Gy = 0;

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
