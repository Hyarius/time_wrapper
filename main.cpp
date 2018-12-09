#include "time_game.h"

int main(int argc, char **argv)
{
	t_gui		gui = t_gui(30, 20);
	SDL_Event	event;
	bool		quit = false;

	if (argc != 1)
		return (1);
	window_initialisation(argv[0]);

	s_game_board map = s_game_board(20, 12);


	while (quit == false)
	{
		prepare_screen();

		map.draw_board();

		gui.draw_self();

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
