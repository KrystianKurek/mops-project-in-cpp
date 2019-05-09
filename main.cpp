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
{/*
	std::priority_queue<mops_event, deque<mops_event>, mops_event_compare> x;
	for (int i = 100; i > 0; i--) {
		x.push(mops_event(i + 0.5f, ARRIVAL, 1, 1));
	}
	print_queue(x);
	*/
	
	std::vector<int> sizes{ 1000000 };
	mops_simulation s(1, 1, 100, sizes, -1, -1, 1000000);
	s.run();
	
		/*
	rand_exp a(5);
	std::ofstream file;
	file.open("test.txt");
	float s = 0; 
	for (int i = 0; i < 10000; i++) {
		s += a.get();
		file << s << std::endl; 
	}
	std::cout << s / 10000 << std::endl;
	file.close();*/
	return 0;
}