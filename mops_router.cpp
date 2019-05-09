#include "mops_router.h"
#include <iostream>

mops_router::mops_router(int buffer_size)
{
	this->buffer_size = buffer_size; 
	this->packets_lost = 0; 
	this->busy = false; 
}

int mops_router::number_of_packet_in_queue()
{
	return this->buffer.size();
}

bool mops_router::full()
{
	if (this->buffer_size == 0){
		return false;
	}
	else if (this->buffer_size == this->buffer.size()){

		return true;
	}
	return false;
}

void mops_router::add_packet(int id)
{
	this->buffer.push_back(id);
}

int mops_router::remove_packet()
{
	int id = this->buffer.front();
	this->buffer.pop_front();
	return id;
}
