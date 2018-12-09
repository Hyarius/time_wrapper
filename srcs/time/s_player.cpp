#include "time_game.h"

s_player::s_player()
{
	this->coord = t_vect(-1, -1);
	this->sprite = -1;
	this->dir = 0;
	this->hp = t_stat();
	this->move = t_stat();
	this->score = 0;
	this->path.clear();
	this->path.push_back(this->coord);
}

s_player::s_player(t_vect p_coord, int p_hp, int p_move, int p_sprite)
{
	this->coord = p_coord;
	this->sprite = p_sprite;
	this->dir = 0;
	this->hp = t_stat(p_hp);
	this->move = t_stat(p_move);
	this->score = 0;
	this->path.clear();
	this->path.push_back(this->coord);
}
