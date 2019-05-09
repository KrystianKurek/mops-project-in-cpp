#pragma once
#include <deque>
class mops_router
{
public:
	int buffer_size;
	int packets_lost; 
	bool busy; 
	std::deque<int>buffer;
	mops_router(int buffer_size); 
	int number_of_packet_in_queue(); 
	bool full();
	void add_packet(int);
	int remove_packet();
};