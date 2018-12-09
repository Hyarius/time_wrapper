#include "time_game.h"

s_actor::s_actor()
{
	this->coord = t_vect(-1, -1);
	this->sprite = -1;
	this->dir = 0;
	path.clear();
}

s_actor::s_actor(int p_sprite)
{
	this->coord = t_vect(-1, -1);
	this->sprite = p_sprite;
	this->dir = 0;
	path.clear();
}
