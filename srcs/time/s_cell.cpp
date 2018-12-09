#include "time_game.h"

		s_cell::s_cell()
{
	this->coord = t_vect(-1, -1);
	this->sprite = -1;
	this->wall = true;
}

		s_cell::s_cell(t_vect p_coord, int p_sprite, bool p_wall)
{
	this->coord = p_coord;
	this->sprite = p_sprite;
	this->wall = p_wall;
}
