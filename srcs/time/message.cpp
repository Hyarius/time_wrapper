#include "time_game.h"

void			message_next_level(t_gui *old_gui, t_game_board *board)
{
	t_gui gui = t_gui(30, 20);
	SDL_Event	event;

	string text = "Next level ! press enter to continu";

	gui.add(new s_button(new s_text_button( &text, BLACK, //text info
									gui.unit * t_vect(7.5, 7.5), gui.unit * t_vect(15, 5), 9, //object info
									t_color(0.7, 0.7, 0.7), t_color(0.9, 0.9, 0.9)), NULL, NULL));

	bool continu = true;

	while (continu == true)
	{
		prepare_screen();

		old_gui->draw_self();

		board->draw_board();

		gui.draw_self();

		render_screen(true);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT ||
				(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) ||
				(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN))
				continu = false;
			}
	}
}

void			message_game_over(t_gui *old_gui, t_game_board *board)
{
	t_gui gui = t_gui(30, 20);
	SDL_Event	event;

	string text = "GAME OVER ! press enter to quit";

	gui.add(new s_button(new s_text_button( &text, BLACK, //text info
									gui.unit * t_vect(7.5, 7.5), gui.unit * t_vect(15, 5), 9, //object info
									t_color(0.7, 0.7, 0.7), t_color(0.9, 0.9, 0.9)), NULL, NULL));

	bool continu = true;

	while (continu == true)
	{
		prepare_screen();

		old_gui->draw_self();

		board->draw_board();

		gui.draw_self();

		render_screen(true);

		if (SDL_PollEvent(&(event)) == 1)
		{
			if (event.type == SDL_QUIT ||
				(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE) ||
				(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RETURN))
				exit(0);
			}
	}
}
