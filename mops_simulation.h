#pragma once
#include <vector>
#include <queue>
#include "mops_packet.h"
#include "mops_event.h"
#include "mops_router.h"
#include "Timer.h"
#include "rand_exp.h"
class mops_simulation
{
	Timer timer; 
	float max_time;
	int max_event_count;
	int max_packet_count; 
	float lambda;
	float mi; 
	int event_counter; 
	float time; 
	std::vector<mops_packet> packet_list; 
	std::vector<mops_router> routers;
	bool debug; 
	std::priority_queue<mops_event, std::deque<mops_event>, mops_event_compare> event_queue;
	rand_exp l;
	rand_exp m;
	 
	bool end();
	void handle_event(int, mops_event);

	void handle_type_arrival(int router_idx, int packet_idx);
	void put_arrival(int router_idx, int packet_idx);


	void handle_type_start_service(int router_idx, int packet_idx);
	void put_start_service(int router_idx, int packet_idx);


	void handle_type_end_service(int router_idx, int packet_idx);
	void put_end_service(int router_idx, int packet_idx);

	void print_statistics();



public:
	mops_simulation(int routers_number, float lambda, float mi, std::vector<int> queue_sizes, float max_time = -1.0, int max_event_count = -1, int max_packet_count = -1, bool debug = false);
	void run();
};