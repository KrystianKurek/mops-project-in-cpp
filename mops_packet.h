#pragma once
#include "mops_event.h"
#include <vector>
class mops_packet
{
public:
	int packet_idx;
	bool lost;
	std::vector<std::vector<float>> times;
	mops_packet(int, int);
};