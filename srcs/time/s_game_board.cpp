#include "time_game.h"

void		player_score_plus_one(t_player *player);
void		player_score_plus_five(t_player *player);
void		player_score_plus_ten(t_player *player);
void		player_move_reset(t_player *player);
void		player_take_one_damage(t_player *player);
void		player_heal_two_damage(t_player *player);
void		player_lose_one_move(t_player *player);

s_game_board::s_game_board()
{

}

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
	for (i = 0; i < this->size.x; i++)
	{
		this->cell_layer[i].resize(this->size.y);
		this->object_layer[i].resize(this->size.y);
		for (j = 0; j < this->size.y; j++)
		{
			if(i == 0 || i == this->size.x - 1 || j == 0 || j == this->size.y - 1)
				this->cell_layer[i][j] = generate_cell(t_vect(i, j), 2);
			else if(i == 1 || i == this->size.x - 2 || j == 1 || j == this->size.y - 2)
				this->cell_layer[i][j] = generate_cell(t_vect(i, j), 0);
			else
				this->cell_layer[i][j] = generate_cell(t_vect(i, j));
			this->object_layer[i][j] = NULL;
		}
	}
	i = (get_win_size().x) / this->size.x;
	j = (get_win_size().y / 30 * 24) / this->size.y;
	this->sprite_size = t_vect((i > j ? j : i), (i > j ? j : i));
	this->offset = t_vect((double)((get_win_size().x - sprite_size.x * this->size.x) / 2.0),
					(double)(get_win_size().y / 30 * 24 - sprite_size.y * this->size.y) / 2);
}

static void		set_object_list(vector <t_object *> *object_list)
{
	object_list->resize(7);
	(*object_list)[0] = new t_object(player_score_plus_one, 8);
	(*object_list)[1] = new t_object(player_score_plus_five, 9);
	(*object_list)[2] = new t_object(player_score_plus_ten, 10);
	(*object_list)[3] = new t_object(player_move_reset, 11);
	(*object_list)[4] = new t_object(player_heal_two_damage, 12);
	(*object_list)[5] = new t_object(player_take_one_damage, 13);
	(*object_list)[6] = new t_object(player_lose_one_move, 14);
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
	place_player(player_ptr);

	reset_object();

	place_object(0, 8);
	place_object(1, 4);
	place_object(2, 2);
	place_object(3, 2);
	place_object(4, 2);
	place_object(5, 4);
	place_object(6, 4);
}

s_game_board::s_game_board(int size_x, int size_y)
{
	tile = s_tileset("ressources/assets/texture.png", t_vect(4, 4));
	this->size = t_vect(size_x, size_y);
	this->level = 0;
	set_object_list(&(this->object_list));

	generate_map();

	this->player_ptr = new t_player(t_vect(-1, -1), 5, 30, 4);

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

void 			s_game_board::draw_board()
{
	int i = 0, j;
	while (i < cell_layer.size())
	{
		j = 0;
		while (j < cell_layer[i].size())
		{
			this->tile.prepare_print(t_vect(sprite_size.x * i, sprite_size.y * j) + offset, sprite_size, cell_layer[i][j].sprite);
			if (object_layer[i][j] != NULL)
				this->tile.prepare_print(t_vect(sprite_size.x * i, sprite_size.y * j) + offset, sprite_size, object_layer[i][j]->sprite);
			j++;
		}
		i++;
	}
	this->tile.prepare_print(player_ptr->coord * sprite_size + offset, sprite_size, player_ptr->sprite);
	render_triangle_texture(this->tile.texture_id);
}

void			s_game_board::move_actor(int coord_x, int coord_y)
{
	if (cell_layer[player_ptr->coord.x + coord_x][player_ptr->coord.y + coord_y].wall == false)
	{
		player_ptr->coord = t_vect(player_ptr->coord.x + coord_x, player_ptr->coord.y + coord_y);
		player_ptr->move.value--;
		player_ptr->reset_move_string();
		if (object_layer[player_ptr->coord.x][player_ptr->coord.y] != NULL)
		{
			object_layer[player_ptr->coord.x][player_ptr->coord.y]->on_walk(player_ptr);
			if (object_layer[player_ptr->coord.x][player_ptr->coord.y] != this->object_list[5] &&
				object_layer[player_ptr->coord.x][player_ptr->coord.y] != this->object_list[6])
			object_layer[player_ptr->coord.x][player_ptr->coord.y] = NULL;
		}
		if (player_ptr->move.value == 0)
		{
			if (player_ptr->score / 100 > level)
			{
				generate_map();
				level = player_ptr->score / 100;
			}
			generate_level();
		}
	}
}
