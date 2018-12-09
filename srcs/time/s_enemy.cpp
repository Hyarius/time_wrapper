#include "time_game.h"

s_enemy::s_enemy()
{
	this->coord = t_vect(-1, -1);
	this->sprite = -1;
	this->dir = 0;
	this->vision = -1;
	this->index = 0;
	this->path.clear();
	this->path.push_back(this->coord);
}

s_enemy::s_enemy(vector<t_vect> p_path, int p_sprite, int p_vision)
{
	this->coord = p_path[0];
	this->sprite = p_sprite;
	this->dir = 0;
	this->vision = p_vision;
	this->index = 0;
	this->path.clear();
	this->path.push_back(this->coord);
}
