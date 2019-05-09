#include <iostream>
#include "mops_simulation.h"
#include "mops_event.h"
#include <queue>
#include "rand_exp.h"
#include <fstream>
using namespace std; 

int main()
{

	std::vector<int> sizes{ 1000000 };
	mops_simulation s(1, 1, 100, sizes, -1, -1, 1000000);
	s.run();

	return 0;
}