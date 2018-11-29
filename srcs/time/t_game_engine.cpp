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
		if (map.size() < line.size() + 1)
			map.resize(line.size() + 1);
		int i = 0;
		while (i < line.size())
		{
			if (map[i].size() < j + 1)
				map[i].resize(j + 1);
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

	player = t_player(t_vect(1, 1), 4);
}

void 			s_game_engine::draw_board()
{
	int i = 0;
	while (i < map.size())
	{
		int j = 0;
		while (j < map[i].size())
		{
			tile.prepare_print(t_vect(50 * i, 50 * j), t_vect(50, 50), map[i][j].sprite);
			j++;
		}
		i++;
	}
	tile.prepare_print(player.coord * 50, t_vect(50, 50), player.sprite);
	render_triangle_texture(tile.texture_id);
}

void
