#include "time_game.h"

void		player_score_plus_one(t_player *player)
{
	player->score++;
	player->reset_score_string();
}

void		player_score_plus_five(t_player *player)
{
	player->score += 5;
	player->reset_score_string();
}

void		player_score_plus_ten(t_player *player)
{
	player->score += 10;
	player->reset_score_string();
}

void		player_move_reset(t_player *player)
{
	player->move.value += player->move.max;
	player->reset_move_string();
}

void		player_take_one_damage(t_player *player)
{
	player->hp.value--;
	player->reset_hp_string();
}

void		player_heal_two_damage(t_player *player)
{
	player->hp.value += 2;
	if (player->hp.value >= player->hp.max)
		player->hp.value = player->hp.max;
	player->reset_hp_string();
}

void		player_lose_one_move(t_player *player)
{
	player->move.value--;
	player->reset_move_string();
}
