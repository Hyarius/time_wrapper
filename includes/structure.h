#ifndef STRUCTURE_H
# define STRUCTURE_H

using namespace std;

#include "gui_object.h"

enum DIRECTION
{
	top = 0,
	right = 1,
	down = 2,
	left = 3,
};

typedef struct		s_cell
{
	bool			obstacle;
	int				sprite;
					s_cell();
					s_cell(bool p_obstacle, int p_sprite);
}					t_cell;

typedef struct		s_player
{
	t_vect			coord;
	DIRECTION		look;
	int				sprite;
					s_player();
					s_player(t_vect p_coord, int p_sprite);
}					t_player;

typedef struct		s_ghost
{
	int				sprite;
	vector<DIRECTION>
					look;
	vector<t_vect>	coord_list;
	int				index;
					s_ghost(vector<DIRECTION> p_look, vector<t_vect> p_coord_list);
}					t_ghost;

typedef struct		s_game_engine
{
	t_tileset			tile;
	vector<vector<t_cell>>
					map;
	t_player		player;
	vector<t_ghost>	ghost_list;
					s_game_engine(string p_path);
	void			draw_board();
}					t_game_engine;

#endif
