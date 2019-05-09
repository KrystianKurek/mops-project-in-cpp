#pragma once
#include <random>

class rand_exp {
	static std::mt19937 generator;
	std::exponential_distribution<float> dist;
public:
	float get(); 
	rand_exp(float mi =6);
};