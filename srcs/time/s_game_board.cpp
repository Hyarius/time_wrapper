#include "time_game.h"

s_game_board::s_game_board()
{

}

s_game_board::s_game_board(int size_x, int size_y)
{
	tile = s_tileset("ressources/assets/texture.png", t_vect(4, 5));
	this->size = t_vect(size_x, size_y);
	this->level = 0;
	this->count = 0;
	set_object_list();

	generate_map();

	this->player_ptr = new t_player(t_vect(-1, -1), 5, 30, 4);

	place_player(player_ptr);

	generate_level();
}

void		s_game_board::ascii_print()
{
	int i = 0;
	int j = 0;
	while (i < this->size.x)
	{
		j = 0;
		while (j < this->size.y)
		{
			if (this->cell_layer[j][i].sprite == 2 || this->cell_layer[j][i].sprite == 3)
				cout << "\e[0;31m";
			else
				cout << "\e[1;34m";
			cout << this->cell_layer[j][i].sprite;
			j++;
		}
		cout << "\n";
		i++;
	}
}

void			s_game_board::draw_ghost()
{
	int i = 0;

	while(i < ghost_list.size())
	{
		this->tile.prepare_print(player_ptr->path[ghost_list[i]->index] * sprite_size + offset, sprite_size,
			ghost_list[i]->sprite + player_ptr->dir_list[ghost_list[i]->index]);
		i++;
	}
}

void 			s_game_board::draw_board()
{
	int i = 0, j;
	while (i < cell_layer.size())
	{
		j = 0;
		while (j < cell_layer[i].size())
		{
			this->tile.prepare_print(t_vect(sprite_size.x * i, sprite_size.y * j) + offset, sprite_size, cell_layer[i][j].sprite);
			if (vision_layer[i][j] != NULL)
				this->tile.prepare_print(t_vect(sprite_size.x * i, sprite_size.y * j) + offset, sprite_size, vision_layer[i][j]->sprite);
			if (object_layer[i][j] != NULL)
				this->tile.prepare_print(t_vect(sprite_size.x * i, sprite_size.y * j) + offset, sprite_size, object_layer[i][j]->sprite);
				j++;
		}
		i++;
	}
	this->tile.prepare_print(player_ptr->coord * sprite_size + offset, sprite_size, player_ptr->sprite + player_ptr->dir);
	draw_ghost();
	render_triangle_texture(this->tile.texture_id);
}

void			s_game_board::reset_ghost_vision()
{
	int i = 0, j;
	while (i < vision_layer.size())
	{
		j = 0;
		while (j < vision_layer[i].size())
		{
			vision_layer[i][j] = NULL;
			j++;
		}
		i++;
	}
}

void			s_game_board::calc_ghost_vision(int i)
{
	vector<t_vect>	to_calc;
	vector<int>		distance;

	to_calc.push_back(player_ptr->path[ghost_list[i]->index]);
	distance.push_back(0);
	int j = 0;
	while (j < to_calc.size())
	{
		vision_layer[to_calc[j].x][to_calc[j].y] = this->object_list[7];
		if (distance[j] <= ghost_list[i]->vision &&
			cell_layer[to_calc[j].x + 1][to_calc[j].y].wall == false)
		{
			to_calc.push_back(t_vect(to_calc[j].x + 1, to_calc[j].y));
			distance.push_back(distance[j] + 1);
		}
		if (distance[j] <= ghost_list[i]->vision &&
			cell_layer[to_calc[j].x - 1][to_calc[j].y].wall == false)
		{
			to_calc.push_back(t_vect(to_calc[j].x - 1, to_calc[j].y));
			distance.push_back(distance[j] + 1);
		}
		if (distance[j] <= ghost_list[i]->vision &&
			cell_layer[to_calc[j].x][to_calc[j].y + 1].wall == false)
		{
			to_calc.push_back(t_vect(to_calc[j].x, to_calc[j].y + 1));
			distance.push_back(distance[j] + 1);
		}
		if (distance[j] <= ghost_list[i]->vision &&
			cell_layer[to_calc[j].x][to_calc[j].y - 1].wall == false)
		{
			to_calc.push_back(t_vect(to_calc[j].x, to_calc[j].y - 1));
			distance.push_back(distance[j] + 1);
		}
		j++;
	}
}

void			s_game_board::move_ghost()
{
	int i = 0;

	reset_ghost_vision();
	while(i < ghost_list.size())
	{
		ghost_list[i]->index++;
		calc_ghost_vision(i);
		i++;
	}
}

void			s_game_board::move_actor(int coord_x, int coord_y)
{
	if (cell_layer[player_ptr->coord.x + coord_x][player_ptr->coord.y + coord_y].wall == false)
	{
		player_ptr->coord = t_vect(player_ptr->coord.x + coord_x, player_ptr->coord.y + coord_y);
		player_ptr->move.value--;
		player_ptr->path.push_back(player_ptr->coord);
		if (coord_x == 1)
		{
			player_ptr->dir = 1;
			player_ptr->dir_list.push_back(1);
		}
		else if (coord_y == -1)
		{
			player_ptr->dir = 0;
			player_ptr->dir_list.push_back(0);
		}
		else if (coord_x == -1)
		{
			player_ptr->dir = 3;
			player_ptr->dir_list.push_back(3);
		}
		else if (coord_y == 1)
		{
			player_ptr->dir = 2;
			player_ptr->dir_list.push_back(2);
		}
		player_ptr->reset_move_string();
		move_ghost();
		if (object_layer[player_ptr->coord.x][player_ptr->coord.y] != NULL)
		{
			object_layer[player_ptr->coord.x][player_ptr->coord.y]->on_walk(player_ptr);
			if (object_layer[player_ptr->coord.x][player_ptr->coord.y] != this->object_list[5] &&
				object_layer[player_ptr->coord.x][player_ptr->coord.y] != this->object_list[6])
			object_layer[player_ptr->coord.x][player_ptr->coord.y] = NULL;
		}
		if (vision_layer[player_ptr->coord.x][player_ptr->coord.y] != NULL)
			vision_layer[player_ptr->coord.x][player_ptr->coord.y]->on_walk(player_ptr);
	}
}

void			s_game_board::check_turn(t_gui *old_gui)
{
	if (player_ptr->move.value <= 0)
	{
		if (player_ptr->score / 10 > level)
		{
			message_next_level(old_gui, this);
			generate_map();
			ghost_list.push_back(new s_enemy(8, 1));
			count = 0;
			level = player_ptr->score / 100;
		}
		generate_level();
		player_ptr->reset_move_count();
	}
	if (player_ptr->hp.value <= 0)
	{
		message_game_over(old_gui, this);
	}
}
