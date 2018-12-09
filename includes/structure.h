#ifndef STRUCTURE_H
# define STRUCTURE_H

using namespace std;

typedef struct		s_cell
{
	t_vect			coord;
	int				sprite;
	bool			wall;
					s_cell();
					s_cell(t_vect p_coord, int p_sprite, bool p_wall);
}					t_cell;

typedef struct		s_stat
{
	int				value;
	int				max;
					s_stat();
					s_stat(int p_max);
					s_stat(int p_value, int p_max);
}					t_stat;

typedef struct		s_actor
{
	t_vect			coord;
	int				sprite;
	int				dir;
	vector<t_vect>	path;
					s_actor();
					s_actor(int p_sprite);
}					t_actor;

typedef struct		s_player : s_actor
{
	t_stat			hp;
	t_stat			move;
	int				score;
					s_player();
					s_player(t_vect p_coord, int p_hp, int p_move, int p_sprite);
}					t_player;

typedef struct		s_enemy : s_actor
{
	int				index;
	int				vision;
					s_enemy();
					s_enemy(vector<t_vect> p_path, int p_sprite, int p_vision);
}					t_enemy;

typedef struct		s_object
{

					s_object();
}					t_object;

typedef struct		s_game_board
{
	vector<vector<t_cell>>
					cell_layer;
	vector<t_actor *>
					actor_list;
	vector<vector<t_object *>>
					object_layer;
	t_tileset		tile;
					s_game_board();
					s_game_board(int size_x, int size_y);
	void 			draw_board();
	void			ascii_print();
}					t_game_board;

typedef struct		s_game_engine
{
	t_game_board	board;
}					t_game_engine;

#endif
