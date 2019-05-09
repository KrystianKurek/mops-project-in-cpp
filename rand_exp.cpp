#include "rand_exp.h"
#include <iostream>
#include <ctime>
std::mt19937 rand_exp::generator(std::time(nullptr));

float rand_exp::get()
{
	return dist(generator);
}

rand_exp::rand_exp(float lambda)
{
	this->dist = std::exponential_distribution<float>(lambda);
}
