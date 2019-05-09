#pragma once
#include <iostream>
enum event_type {ARRIVAL = 0, START_SERVICE = 1, END_SERVICE = 2};

class mops_event {
public: 
	float time; 
	event_type type; 
	int packet_idx; 
	int router_idx; 
	mops_event(float, event_type, int, int);
};

class mops_event_compare
{
public:
	bool operator()(const mops_event& lhs, const mops_event& rhs)
	{
		//std::cout << lhs.time << " " << rhs.time << std::endl; 
		return lhs.time > rhs.time;
	}
};