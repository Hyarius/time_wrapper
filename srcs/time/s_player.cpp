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
	this->hp_string = "hp : " + to_string(this->hp.value) + "/" + to_string(this->hp.max);
	this->score_string = "score : " + to_string(this->score);
	this->move_string = "move : " + to_string(this->move.value) + "/" + to_string(this->move.max);
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
	this->hp_string = "hp : " + to_string(this->hp.value) + "/" + to_string(this->hp.max);
	this->score_string = "score : " + to_string(this->score);
	this->move_string = "move : " + to_string(this->move.value) + "/" + to_string(this->move.max);
}

void	s_player::print_path()
{
	int i = 0;
	while (i < this->path.size())
	{
		printf("[%.0f / %.0f]", path[i].x, path[i].y);
		if (i != path.size() - 1)
			printf(" - ");
		i++;
	}
	printf("\n");
}

void	s_player::reset_move_count()
{
	this->move.value = this->move.max;
}

void	s_player::reset_hp_string()
{
	this->hp_string = "hp : " + to_string(this->hp.value) + "/" + to_string(this->hp.max);
}

void	s_player::reset_move_string()
{
	this->move_string = "move : " + to_string(this->move.value) + "/" + to_string(this->move.max);
}

void	s_player::reset_score_string()
{
	this->score_string = "score : " + to_string(this->score);
}
