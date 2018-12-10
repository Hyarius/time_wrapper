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
	string			hp_string;
	t_stat			move;
	string			move_string;
	int				score;
	string			score_string;
					s_player();
					s_player(t_vect p_coord, int p_hp, int p_move, int p_sprite);
	void			reset_hp_string();
	void			reset_move_string();
	void			reset_score_string();
}					t_player;

typedef struct		s_enemy : s_actor
{
	int				index;
	int				vision;
					s_enemy();
					s_enemy(vector<t_vect> p_path, int p_sprite, int p_vision);
}					t_enemy;

typedef void		(*t_event)(t_player *player);

typedef struct		s_object
{
	int				sprite;
	t_event			event;
					s_object();
					s_object(t_event p_event, int p_sprite);
	void			on_walk(t_player *player);
}					t_object;

typedef struct		s_game_board
{
	t_vect			size;
	int				level;
	vector<vector<t_cell>>
					cell_layer;
	t_player		*player_ptr;
	vector<t_enemy *>
					ghost_list;
	vector<vector<t_object *>>
					object_layer;
	vector<t_object *>
					object_list;
	t_tileset		tile;
	t_vect			sprite_size;
	t_vect			offset;
					s_game_board();
					s_game_board(int size_x, int size_y);
	void 			draw_board();
	void			ascii_print();
	void			move_actor(int coord_x, int coord_y);
	void			place_object(int object, int nb);
	void			generate_map();
	void			place_player(t_player *player);
	void			reset_object();
	void			generate_level();

}					t_game_board;

typedef struct		s_game_engine
{
	t_game_board	board;
}					t_game_engine;

#endif
