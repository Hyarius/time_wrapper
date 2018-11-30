#ifndef STRUCTURE_H
# define STRUCTURE_H

using namespace std;

#include "gui_object.h"

typedef struct		s_cell
{
	bool			obstacle;
	int				sprite;
	int				object;
	int				seen;
					s_cell();
					s_cell(bool p_obstacle, int p_sprite);
}					t_cell;

typedef struct		s_player
{
	t_vect			coord;
	int				sprite;
					s_player();
					s_player(t_vect p_coord, int p_sprite);
}					t_player;

typedef struct		s_ghost
{
	int				sprite;
	vector<t_vect>	coord_list;
					s_ghost(vector<t_vect> p_coord_list);
}					t_ghost;

typedef struct		s_game_engine
{
	int				score;
	int				move_left;
	int				life;

	int				index;

	t_tileset			tile;
	vector<vector<t_cell>>
					map;
	t_vect			map_size;
	t_player		player;
	vector<t_ghost>	ghost_list;
	vector<t_vect>	move_saved;
					s_game_engine(string p_path);
	void			draw_board();
	void			calc_level();
	void			place_vision();
	bool			check_near(t_vect coord, int size);
	void			move_actor(int move_x, int move_y);
}					t_game_engine;

#endif
