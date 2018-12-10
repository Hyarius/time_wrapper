#include "time_game.h"

s_object::s_object()
{

}

s_object::s_object(t_event p_event, int p_sprite)
{
	this->sprite = p_sprite;
	this->event = p_event;
}

void			s_object::on_walk(t_player *player)
{
	this->event(player);
}
