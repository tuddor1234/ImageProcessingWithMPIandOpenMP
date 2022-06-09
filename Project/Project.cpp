#include <iostream>
#include "Sequential.h"
#include "OpenMP.h"
#include "MPI.h"

using namespace std;

int main()
{

	//Sequential::EdgeDetection();
	OpenMP::EdgeDetection();
	//MPI::EdgeDetection();
	getchar();
	return 0;
}


