#include "time_wrapper.h"

int main(int argc, char **argv)
{
	bool quit = false;
	SDL_Event	event;

	if (argc != 1)
		return (1);

	window_initialisation(argv[0]);

	s_game_engine test = s_game_engine("ressources/maps/map_test.map");

	while (quit == false)
	{
		prepare_screen(t_color(0.2, 0.2, 0.2));

		test.draw_board();

		render_screen(false);

		if (SDL_PollEvent(&event) == 1)
		{
			if (event.type == SDL_QUIT)
				quit = true;
			else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
				quit = true;
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
				test.move_actor(0, -1);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
				test.move_actor(0, 1);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
				test.move_actor(-1, 0);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
				test.move_actor(1, 0);
			else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
				test.move_actor(0, 0);
		}
	}
	return 0;
}
