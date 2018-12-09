#include "time_game.h"

s_stat::s_stat()
{
	this->value = -1;
	this->max = -1;
}

s_stat::s_stat(int p_max)
{
	this->value = p_max;
	this->max = p_max;
}

s_stat::s_stat(int p_value, int p_max)
{
	this->value = p_value;
	this->max = p_max;
}
