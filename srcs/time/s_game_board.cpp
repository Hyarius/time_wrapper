#include "time_game.h"

s_game_board::s_game_board()
{
	this->cell_layer.resize(0);
	this->actor_list.resize(0);
	this->object_layer.resize(0);
	for (int i = 0; i < 0; i++)
	{
		this->cell_layer[i].resize(0);
		this->object_layer[i].resize(0);
	}
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

s_game_board::s_game_board(int size_x, int size_y)
{
	tile = s_tileset("ressources/assets/texture.png", t_vect(4, 5));
	int i, j;
	this->cell_layer.resize(size_x);
	this->object_layer.resize(size_x);
	for (i = 0; i < size_x; i++)
	{
		this->cell_layer[i].resize(size_y);
		this->object_layer[i].resize(size_y);
		for (j = 0; j < size_y; j++)
		{
			if(i == 0 || i == size_x - 1 || j == 0 || j == size_y - 1)
				this->cell_layer[i][j] = generate_cell(t_vect(i, j), 2);
			else if(i == 1 || i == size_x - 2 || j == 1 || j == size_y - 2)
				this->cell_layer[i][j] = generate_cell(t_vect(i, j), 0);
			else
				this->cell_layer[i][j] = generate_cell(t_vect(i, j));
			this->object_layer[i][j] = NULL;
		}
	}
	i = 0;
	j = 0;
	while (this->cell_layer[i][j].wall == true)
	{
		i = generate_nbr(0, size_x);
		j = generate_nbr(0, size_y);
	}
	this->actor_list.push_back(new t_player(t_vect(i, j), 5, 30, 4));
}

void		s_game_board::ascii_print()
{
	int i = 0;
	int j = 0;
	while (i < this->cell_layer[0].size())
	{
		j = 0;
		while (j < this->cell_layer.size())
		{
			if (this->cell_layer[j][i].sprite == 2 || this->cell_layer[j][i].sprite == 3)
				printf("\e[0;31m");
			else
				printf("\e[1;34m");
			printf("%d", this->cell_layer[j][i].sprite);
			j++;
		}
		printf("\n");
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
			this->tile.prepare_print(t_vect(50 * i, 50 * j), t_vect(50, 50), cell_layer[i][j].sprite);
			j++;
		}
		i++;
	}
	this->tile.prepare_print(actor_list[0]->coord * 50, t_vect(50, 50), actor_list[0]->sprite);
	render_triangle_texture(this->tile.texture_id);
}
