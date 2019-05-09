#include "mops_event.h"



mops_event::mops_event(float time, event_type type, int packet_idx, int router_idx)
{
	this->time = time;
	this->type = type; 
	this->packet_idx = packet_idx;
	this->router_idx = router_idx; 
}
