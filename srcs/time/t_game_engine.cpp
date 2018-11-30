	#include "time_wrapper.h"

				s_game_engine::s_game_engine(string p_path)
{
	ifstream		myfile;
	string			line;

	myfile.open(p_path.c_str());
	tile = t_tileset(get_strsplit(&myfile, ":", 2)[1], t_vect(4, 3));
	int j = 0;
	while (myfile.eof() == false)
	{
		line = get_str(&myfile);
		if (map.size() < line.size())
		{
			map.resize(line.size());
			map_size.x = line.size();
		}
		int i = 0;
		while (i < line.size())
		{
			if (map[i].size() < j + 1)
			{
				map[i].resize(j + 1);
				map_size.y = j + 1;
			}
			if (line[i] == '0')
				map[i][j] = s_cell(false, 0);
			if (line[i] == '1')
				map[i][j] = s_cell(true, 1);
			if (line[i] == '2')
				map[i][j] = s_cell(false, 2);
			if (line[i] == '3')
				map[i][j] = s_cell(true, 3);
			i++;
		}
		j++;
	}
	calc_level();
	score = 0;
	life = 3;
}

static int		generate_objet()
{
	int result = random_int(0, 100);

	if (result >= 85 && result < 92)
		return (0);
	else if (result >= 92 && result < 97)
		return (1);
	else if (result >= 97 && result < 98)
		return (2);
	else if (result >= 98 && result < 100)
		return (3);
	else
		return (-1);
}

void			s_game_engine::calc_level()
{
	move_left = 10;
	index = 0;
	if (move_saved.size() > 0)
	{
		ghost_list.push_back(s_ghost(move_saved));
		move_saved.clear();
	}
	int i = 0, j;
	while (i < map_size.x)
	{
		j = 0;
		while (j < map_size.y)
		{
			map[i][j].object = -1;
			j++;
		}
		i++;
	}
	int x = random_int(0, map_size.x - 1), y = random_int(0, map_size.y - 1);
	while (map[x][y].obstacle == true || check_near(t_vect(x, y), 2) == 1)
	{
		x = random_int(0, map_size.x - 1);
		y = random_int(0, map_size.y - 1);
	}
	player = t_player(t_vect(x, y), 4);
	move_saved.push_back(player.coord);
	i = 0;
	while (i < map_size.x)
	{
		j = 0;
		while (j < map_size.y)
		{
			if (map[i][j].obstacle == false)
				map[i][j].object = generate_objet();
			j++;
		}
		i++;
	}
}

void 			s_game_engine::draw_board()
{
	int i = 0, j;
	while (i < map.size())
	{
		j = 0;
		while (j < map[i].size())
		{
			tile.prepare_print(t_vect(50 * i, 50 * j), t_vect(50, 50), map[i][j].sprite);
			if (map[i][j].object != -1)
				tile.prepare_print(t_vect(50 * i, 50 * j), t_vect(50, 50), t_vect(map[i][j].object, 2));
			if (map[i][j].obstacle == false && map[i][j].seen == 1)
				tile.prepare_print(t_vect(50 * i, 50 * j), t_vect(50, 50), t_vect(3, 1));
			j++;
		}
		i++;
	}
	tile.prepare_print(player.coord * 50, t_vect(50, 50), player.sprite);
	i = 0;
	while (i < ghost_list.size())
	{
		j = (index < ghost_list[i].coord_list.size() - 1 ? index : ghost_list[i].coord_list.size() - 1);
		tile.prepare_print(ghost_list[i].coord_list[j] * 50, t_vect(50, 50), ghost_list[i].sprite);
		i++;
	}
	render_triangle_texture(tile.texture_id);
}

void			s_game_engine::move_actor(int move_x, int move_y)
{
	int i = player.coord.x + move_x;
	int j = player.coord.y + move_y;

	if (map[i][j].obstacle == false)
	{
		player.coord = t_vect(i, j);
		move_saved.push_back(player.coord);
		move_left--;
		if (map[i][j].seen == 1)
			life--;
		if (map[i][j].object != -1)
		{
			if (map[i][j].object == 0)
				score++;
			if (map[i][j].object == 1)
				score += 5;
			if (map[i][j].object == 2)
				life++;
			if (map[i][j].object == 3)
				move_left += 30;
			map[i][j].object = -1;
		}
		index++;
	}
	place_vision();
	if (move_left == 0)
		calc_level();
}

void			s_game_engine::place_vision()
{
	int i;
	int j;

	i = 0;
	while (i < map.size())
	{
		j = 0;
		while (j < map[i].size())
		{
			map[i][j].seen = 0;
			j++;
		}
		i++;
	}

	i = 0;
	while (i < ghost_list.size())
	{
		t_vect coord = ghost_list[i].coord_list[index];
		int k;
		int l;
		k = 0;
		while (k < 3)
		{
			bool a = true, b = true, c = true, d = true;
			l = 0;
			while (l + k < 3)
			{
				if (a == true && coord.x + k < map_size.x && coord.y + l < map_size.y)
					map[coord.x + k][coord.y + l].seen = 1;
				else
					a = false;
				if (b == true && coord.x + k < map_size.x && coord.y - l >= 0)
					map[coord.x + k][coord.y - l].seen = 1;
				else
					b = false;
				if (c == true && coord.x + k >= 0 && coord.y + l < map_size.y)
					map[coord.x - k][coord.y + l].seen = 1;
				else
					c = false;
				if (d == true && coord.x + k >= 0 && coord.y + l >= 0)
					map[coord.x - k][coord.y - l].seen = 1;
				else
					d = false;
				l++;
			}
			a = true;
			b = true;
			c = true;
			d = true;
			k++;
		}
		i++;
	}
}

bool			s_game_engine::check_near(t_vect coord, int size)
{
	int i;
	int j;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j + i < size)
		{
			if (map[coord.x + i][coord.y + j].seen == 1)
				return (1);
			if (map[coord.x + i][coord.y - j].seen == 1)
				return (1);
			if (map[coord.x - i][coord.y + j].seen == 1)
				return (1);
			if (map[coord.x - i][coord.y - j].seen == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
