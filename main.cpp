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

		render_screen();

		if (SDL_PollEvent(&event) == 1)
		{
			if (event.type == SDL_QUIT)
				quit = true;
			else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
				quit = true;
		}
	}
	return 0;
}
