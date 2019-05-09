#include "mops_simulation.h"
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>



float mean(std::vector<float> v) {
	float s = 0;
	for (auto value : v){
		s += value;
	}
	return s / v.size();
}
void mops_simulation::run()
{
	mops_event e = mops_event(this->time, ARRIVAL, 0, 0);
	packet_list.push_back(mops_packet(this->packet_list.size(), this->routers.size()));
	this->packet_list[0].times[0][ARRIVAL] = e.time;
	this->event_queue.push(e);
	while (!this->end())
	{
		
		e = this->event_queue.top();
		//std::cout << e.type << " " <<e.packet_idx<<std::endl;;
		this->event_queue.pop();
		this->handle_event(e.router_idx, e);
	}
	print_statistics();
}

bool mops_simulation::end()
{
	if (max_packet_count != -1){
		return packet_list.size() >= max_packet_count;
	}
	else if (max_event_count != -1) {
		return event_counter >= max_event_count;
	}
	else{
		return time >= max_time;
	}
}

void mops_simulation::handle_event(int router_idx, mops_event e)
{
	time = e.time;
	event_counter++; 
	if (e.type == ARRIVAL) {
		handle_type_arrival(router_idx, e.packet_idx);
	}
	else if (e.type == START_SERVICE) {
		handle_type_start_service(router_idx, e.packet_idx);
	}
	else {
		handle_type_end_service(router_idx, e.packet_idx);
	}
}

void mops_simulation::handle_type_arrival(int router_idx, int packet_idx)
{
	if (routers[router_idx].full()) {
		routers[router_idx].packets_lost++; 
		packet_list[packet_idx].lost = true;
	}
	else if(!routers[router_idx].busy) {
		put_start_service(router_idx, packet_idx);
	}
	else {
		routers[router_idx].add_packet(packet_idx);
	}
	
	if (router_idx == 0){
		put_arrival(router_idx, packet_idx);
	}

}

void mops_simulation::put_arrival(int router_idx, int packet_idx)
{
	if (router_idx == 0) {
		float t = time + l.get();
		mops_packet packet(packet_list.size(), routers.size());
		packet.times[router_idx][ARRIVAL] = t;
		packet_list.push_back(packet);
		mops_event e(t, ARRIVAL, packet.packet_idx, router_idx);
		event_queue.push(e);
	}
	else {
		float t = packet_list[packet_idx].times[router_idx - 1][END_SERVICE];
		mops_event e(t, ARRIVAL, packet_idx, router_idx);
		packet_list[packet_idx].times[router_idx][ARRIVAL] = t;
		event_queue.push(e);
	}
	 
}

void mops_simulation::handle_type_start_service(int router_idx, int packet_idx)
{
	put_end_service(router_idx, packet_idx);
	routers[router_idx].busy = true; 
}

void mops_simulation::put_start_service(int router_idx, int packet_idx)
{
	mops_event e = mops_event(time, START_SERVICE, packet_idx, router_idx);
	packet_list[packet_idx].times[router_idx][START_SERVICE] = time; 
	event_queue.push(e);
}

void mops_simulation::handle_type_end_service(int router_idx, int packet_idx)
{
	if (routers[router_idx].number_of_packet_in_queue() > 0) {
		int packet_idx_temp = routers[router_idx].remove_packet();
		put_start_service(router_idx, packet_idx_temp);
	}
	routers[router_idx].busy = false; 

	if (router_idx != routers.size() - 1) {
		put_arrival(router_idx + 1, packet_idx);
	}
}

void mops_simulation::put_end_service(int router_idx, int packet_idx)
{
	float t = time + m.get();
	mops_event e = mops_event(t, END_SERVICE, packet_idx, router_idx);
	packet_list[packet_idx].times[router_idx][END_SERVICE] = t; 
	event_queue.push(e);
}

void mops_simulation::print_statistics()
{
	int lost = 0;
	int lost1 = 0; 
	std::vector<float> delays; 
	float start, end; 
	for (int i = 0; i < routers.size(); i++) {
		std::cout << "Number of packet lost in router " << i << ": " << routers[i].packets_lost << std::endl;
		lost += routers[i].packets_lost; 
		std::vector<float> waiting_in_queue;
		std::vector<float> service_time;
		for (auto packet : packet_list) {
			start = packet.times[i][ARRIVAL]; 
			end = packet.times[i][START_SERVICE];
			if (start != -1 && end != -1) {
				waiting_in_queue.push_back(end - start);
			}
			start = end; 
			end = packet.times[i][END_SERVICE];
			if (start != -1 && end != -1) {
				service_time.push_back(end - start);
			}
		}
		std::cout << "Average time of waiting in " << i << " router's queue is: " << mean(waiting_in_queue) << std::endl;
		std::cout << "Average time of service in " << i << " router's queue is: " << mean(service_time) << std::endl;
	}
	if (lambda != mi) {
		float traffic = lambda / mi;
		std::cout << "Average traffic (ro) (theoretical): " << traffic << std::endl;
		std::cout << "Average time of service (theoretical): " << traffic / mi / (1.0 - traffic) << std::endl;
	}
	
	for (auto packet : packet_list) {
		if (packet.lost) {
			lost1++;
		}
		start = packet.times[0][ARRIVAL];
		end = packet.times[routers.size() - 1][END_SERVICE]; 
		if (start != -1 && end != -1) {
			delays.push_back(end - start);
		}
	}
	std::sort(delays.begin(), delays.end());
	std::cout << "Packets lost: " << std::round(100 * lost / packet_list.size())<<"%"<<std::endl;
	std::cout << "Packets lost: " << std::round(100 * lost1 / packet_list.size()) << "%" << std::endl;
	std::cout << "Number of events: " << event_counter << ", number of packets: " << packet_list.size() << ", time: " << time << std::endl;
	timer.stop();
	long time = timer.getDuration();
	double time_d = time / 1000000000.;
	std::cout << "Simulation took " << time << "s time." << std::endl;
	std::ofstream file; 
	file.open("data.txt");
	int xD = 0;
	//for (int i = delays.size() - 50; i < delays.size(); i++)
	//{
		//std::cout << delays[i] << std::endl;
	//}
	for (auto delay : delays) {
		if (xD < 50)
		{
			//std::cout << delay << std::endl;
			xD++;
		}
		file << delay << std::endl;
	}
	file.close();
	std::string command = "python hist.py"; 
	system(command.c_str());
}


mops_simulation::mops_simulation(int routers_number, float lambda, float mi, std::vector<int> queue_sizes, float max_time, int max_event_count, int max_packet_count, bool debug)
{
	this->timer = Timer();
	this->timer.start(); 
	this->max_time = max_time;
	this->max_event_count = max_event_count;
	this->max_packet_count = max_packet_count;
	std::cout << "Lambda: " << lambda << std::endl; 
	this->lambda = lambda;
	std::cout << "Mi: " << mi << std::endl;
	this->mi = mi;
	this->event_counter = 0;
	this->time = 0;
	this->debug = debug;
	for (int i = 0; i < routers_number; i++)
	{
		this->routers.push_back(mops_router(queue_sizes[i]));
	}
	m = rand_exp(mi);
	l = rand_exp(lambda); 
}
