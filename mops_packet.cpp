#include <vector>
#include "mops_packet.h"

mops_packet::mops_packet(int packet_idx, int routers_number)
{
	this->lost = false;
	this->packet_idx = packet_idx;
	for (int i = 0; i < routers_number; i++)
	{
		std::vector<float> temp;
		for (int j = 0; j < 3; j++)
		{
			temp.push_back(-1.0f);
		}
		this->times.push_back(temp);
	}

}
