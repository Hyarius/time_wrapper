#include "time_game.h"

void		player_score_plus_one(t_player *player);
void		player_score_plus_five(t_player *player);
void		player_score_plus_ten(t_player *player);
void		player_move_reset(t_player *player);
void		player_take_one_damage(t_player *player);
void		player_heal_two_damage(t_player *player);
void		player_lose_one_move(t_player *player);

static t_cell generate_cell(t_vect p_coord)
{
	t_cell	cell;
	cell.coord = p_coord;
	int type = generate_nbr(0, 100);

	if (type < 70)
	{
		cell.sprite = 1;
		cell.wall = false;
	}
	else
	{
		cell.sprite = 3;
		cell.wall = true;
	}
	return (cell);
}

static t_cell generate_cell(t_vect p_coord, int type)
{
	t_cell	cell;
	cell.coord = p_coord;

	if (type == 0)
	{
		cell.sprite = 0;
		cell.wall = false;
	}
	else if (type == 1)
	{
		cell.sprite = 1;
		cell.wall = false;
	}
	else if (type == 2)
	{
		cell.sprite = 2;
		cell.wall = true;
	}
	else
	{
		cell.sprite = 3;
		cell.wall = true;
	}
	return (cell);
}

void			s_game_board::place_object(int object, int nb)
{
	for (int c = 0; c < nb; c++)
	{
		int i = 0;
		int j = 0;
		while (this->cell_layer[i][j].wall == true ||
				(i == player_ptr->coord.x && j == player_ptr->coord.y) ||
				object_layer[i][j] != NULL)
		{
			i = generate_nbr(0, this->cell_layer[0].size());
			j = generate_nbr(0, this->cell_layer.size());
		}
		object_layer[i][j] = object_list[object];
	}
}

void			s_game_board::place_player(t_player *player)
{
	int i = -1;
	int j = -1;
	while (i != 1 && i != this->size.x - 2 && j != 1 && j != this->size.y - 2)
	{
		i = generate_nbr(1, this->size.x - 2);
		j = generate_nbr(1, this->size.y - 2);
	}
	this->player_ptr = player;
	player->move.value = player->move.max;
	player->reset_move_string();
	player->coord = t_vect(i, j);
}

void			s_game_board::generate_map()
{
	int i, j;
	this->cell_layer.resize(this->size.x);
	this->object_layer.resize(this->size.x);
	this->vision_layer.resize(this->size.x);
	for (i = 0; i < this->size.x; i++)
	{
		this->cell_layer[i].resize(this->size.y);
		this->object_layer[i].resize(this->size.y);
		this->vision_layer[i].resize(this->size.y);

		for (j = 0; j < this->size.y; j++)
		{
			if(i == 0 || i == this->size.x - 1 || j == 0 || j == this->size.y - 1)
				this->cell_layer[i][j] = generate_cell(t_vect(i, j), 2);
			else if(i == 1 || i == this->size.x - 2 || j == 1 || j == this->size.y - 2)
				this->cell_layer[i][j] = generate_cell(t_vect(i, j), 0);
			else
				this->cell_layer[i][j] = generate_cell(t_vect(i, j));
			this->object_layer[i][j] = NULL;
			this->vision_layer[i][j] = NULL;
		}
	}
	i = (get_win_size().x) / this->size.x;
	j = (get_win_size().y / 30 * 24) / this->size.y;
	this->sprite_size = t_vect((i > j ? j : i), (i > j ? j : i));
	this->offset = t_vect((double)((get_win_size().x - sprite_size.x * this->size.x) / 2.0),
					(double)(get_win_size().y / 30 * 24 - sprite_size.y * this->size.y) / 2);

}

void			s_game_board::set_object_list()
{
	this->object_list.resize(8);
	this->object_list[0] = new t_object(player_score_plus_one, 13);
	this->object_list[1] = new t_object(player_score_plus_five, 14);
	this->object_list[2] = new t_object(player_score_plus_ten, 15);
	this->object_list[3] = new t_object(player_move_reset, 16);
	this->object_list[4] = new t_object(player_heal_two_damage, 17);
	this->object_list[5] = new t_object(player_take_one_damage, 18);
	this->object_list[6] = new t_object(player_lose_one_move, 19);
	this->object_list[7] = new t_object(player_take_one_damage, 12);
}

void			s_game_board::reset_object()
{
	int i = 0;
	int j = 0;
	while (i < this->size.x)
	{
		j = 0;
		while (j < this->size.y)
		{
			this->object_layer[i][j] = NULL;
			j++;
		}
		i++;
	}
}

void			s_game_board::generate_level()
{
	//place_player(player_ptr);

	reset_object();

	place_object(0, 8);
	place_object(1, 4);
	place_object(2, 2);
	place_object(3, 2);
	place_object(4, 2);
	place_object(5, 4);
	place_object(6, 4);
}
