#include <iostream>
#include "Sequential.h"
#include "OpenMP.h"
#include "MPI.h"

using namespace std;

int main(int argc, char* argv[])
{
	Sequential::EdgeDetection();
	OpenMP::EdgeDetection();
	MPI::EdgeDetection(argc, argv);
	getchar();
	return 0;
}


