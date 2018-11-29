#include "time_wrapper.h"

			s_cell::s_cell()
{
	this->obstacle = false;
	this->sprite = -1;
}

			s_cell::s_cell(bool p_obstacle, int p_sprite)
{
	this->obstacle = p_obstacle;
	this->sprite = p_sprite;
}
