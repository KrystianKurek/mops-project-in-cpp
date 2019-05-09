#include <iostream>
#include "mops_simulation.h"
#include "mops_event.h"
#include <queue>
#include "rand_exp.h"
#include <fstream>
using namespace std; 
template<typename T> void print_queue(T& q) {
	while (!q.empty()) {
		std::cout << q.top().time << " ";
		q.pop();
	}
	std::cout << '\n';
}
int main()
{
	std::vector<int> sizes{ 1000000 };
	mops_simulation s(1, 1, 100, sizes, -1, -1, 1000000);
	s.run();

	return 0;
}