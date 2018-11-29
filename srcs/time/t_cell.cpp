#include "time_wrapper.h"

			s_cell::s_cell()
{
	this->coord = t_vect(-1, -1);
	this->obstacle = false;
	this->sprite = -1;
}

			s_cell::s_cell(t_vect p_coord, bool p_obstacle, int p_sprite)
{
	this->coord = p_coord;
	this->obstacle = p_obstacle;
	this->sprite = p_sprite;
}
