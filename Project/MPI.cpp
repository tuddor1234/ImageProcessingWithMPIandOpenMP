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
    RGBToGrayScale(img);
    
    MPI_Init(&argc, &argv);
    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d out of %d processors\n",
        processor_name, world_rank, world_size);

    // Finalize the MPI environment.
    MPI_Finalize();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    std::cout << "OpenMP " << duration.count() << " miliseconds" << std::endl;

    //newImg.display();
}

void MPI::RGBToGrayScale(CImg<int>& img)
{
}

uint8_t MPI::GetValueForPixel(const CImg<int>& img, int x, int y)
{
    return uint8_t();
}
