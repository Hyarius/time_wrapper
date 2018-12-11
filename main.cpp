#include "time_game.h"

int main(int argc, char **argv)
{
	window_initialisation(argv[0]);

	SDL_Event	event;
	bool		quit = false;

	if (argc != 1)
		return (1);

	t_gui		gui = t_gui(30, 20);

	gui.add(new s_button(new s_image_button( t_image("ressources/assets/gui.png"), gui.unit * t_vect(5, 17), gui.unit * t_vect(20, 3)), NULL, NULL));

	s_game_board map = s_game_board(20, 20);

	t_player *player = map.player_ptr;

	gui.add(new s_button(new s_text_button( &(player->hp_string), BLACK, //text info
									gui.unit * t_vect(7, 18), gui.unit * t_vect(3, 1), 4, //object info
									t_color(0.7, 0.7, 0.7), t_color(0.9, 0.9, 0.9)), NULL, NULL));

	gui.add(new s_button(new s_text_button( &(player->score_string), BLACK, //text info
									gui.unit * t_vect(12, 18), gui.unit * t_vect(6, 1), 4, //object info
									t_color(0.7, 0.7, 0.7), t_color(0.9, 0.9, 0.9)), NULL, NULL));

	gui.add(new s_button(new s_text_button( &(player->move_string), BLACK, //text info
									gui.unit * t_vect(20, 18), gui.unit * t_vect(3, 1), 4, //object info
									t_color(0.7, 0.7, 0.7), t_color(0.9, 0.9, 0.9)), NULL, NULL));

	while (quit == false)
	{
		prepare_screen();

		gui.draw_self();

		map.draw_board();

		render_screen(true);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT ||
				(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				quit = true;
			else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
				gui.click();
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
				map.move_actor(0, -1);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
				map.move_actor(0, 1);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
				map.move_actor(1, 0);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
				map.move_actor(-1, 0);
			map.check_turn(&gui);
		}
	}
	return 0;
}
