#include "time_wrapper.h"

			s_player::s_player()
{
	this->coord = t_vect(-1, -1);
	this->sprite = -1;
}

			s_player::s_player(t_vect p_coord, int p_sprite)
{
	this->coord = p_coord;
	this->sprite = p_sprite;
}
