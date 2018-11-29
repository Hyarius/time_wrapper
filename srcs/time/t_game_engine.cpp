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
		if (map.size() < j + 1)
			map.resize(j + 1);
		line = get_str(&myfile);
		int i = 0;
		while (i < line.size())
		{
			if (map[j].size() < i + 1)
				map[j].resize(i + 1);
			if (line[i] == '0')
				map[j][i] = s_cell(t_vect(j, i), false, 0);
			if (line[i] == '1')
				map[j][i] = s_cell(t_vect(j, i), true, 1);
			if (line[i] == '2')
				map[j][i] = s_cell(t_vect(j, i), false, 2);
			if (line[i] == '3')
				map[j][i] = s_cell(t_vect(j, i), true, 3);
			i++;
		}
		j++;
	}
	player = t_player(t_vect(1, 1), 4);
}
