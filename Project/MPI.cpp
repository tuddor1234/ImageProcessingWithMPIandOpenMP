#include "MPI.h"

#include<stdio.h> 
#include "../MPI/Include/mpi.h"
#include<stdlib.h>

void MPI::EdgeDetection(int argc, char* argv[])
{
    CImg<int> img;
    img.load("sample.BMP");
    CImg<int> newImg = img;
    
    auto start = high_resolution_clock::now();
    MPI_Init(&argc, &argv);

    RGBToGrayScale(img, argc, argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);	/* get current process id */
    MPI_Comm_size(MPI_COMM_WORLD, &size);	/* get number of processes */


    int widthSlice = (img.width() / size);
    int startWidth = widthSlice * rank;
    int endWidth = widthSlice * (rank + 1);

    for (int square = 0; square < size; square++)
    {
        int heightSlice = (img.height() / size);
        int startHeight = heightSlice * square;
        int endHeight = heightSlice * (square + 1);

        for (int x = startWidth; x <= endWidth; x++)
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

    MPI_Finalize();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    std::cout << "MPI " << duration.count() << " miliseconds" << std::endl;
    newImg.save("MPI.BMP");
    //newImg.display();
}

void MPI::RGBToGrayScale(CImg<int>& img, int argc, char* argv[])
{
   
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::cout << "RANK" << rank << "\n";

    int widthSlice = (img.width() / size);
    int startWidth = widthSlice * rank;
    int endWidth = widthSlice * (rank + 1) - 1;

    for (int square = 0; square < size; square++)
    {
        int heightSlice = (img.height() / size);
        int startHeight = heightSlice * square;
        int endHeight = heightSlice * (square + 1);

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

uint8_t MPI::GetValueForPixel(const CImg<int>& img, int x, int y)
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
