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

	while (quit == false)
	{
		prepare_screen();

		gui.draw_self();

		map.draw_board();

		render_screen();

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT ||
				(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE))
				quit = true;
			else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
				gui.click();
		}
	}
	return 0;
}
