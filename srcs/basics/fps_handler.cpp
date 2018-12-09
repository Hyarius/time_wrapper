#include "template.h"

using namespace std;

int				g_fps = 60000;

unsigned int	framedelay = 1000 / g_fps;

void			check_frame()
{
	int				frame_actual;
	static Uint32	framestart;
	static int		beginsecond = 0;
	static int		nb_frame;

	frame_actual = SDL_GetTicks();
	if (beginsecond == 0)
		beginsecond = frame_actual;
	if (frame_actual - beginsecond > 1000)
	{
		nb_frame = 0;
		beginsecond = 0;
	}
	else
		nb_frame++;
	if (framedelay > frame_actual - framestart)
		SDL_Delay(framedelay - (frame_actual - framestart));
	framestart = SDL_GetTicks();
}

void			check_frame(bool draw)
{
	unsigned int	framedelay;
	int				frame_actual;
	static Uint32	framestart;
	static int		beginsecond;
	static int		nb_frame;
	t_vect			coord;
	static string	str = "FPS";

	coord = t_vect(50, 50);
	framedelay = 1000 / g_fps;
	frame_actual = SDL_GetTicks();
	if (draw == true)
		draw_text(str.c_str(), 12, coord, WHITE);
	if (beginsecond == 0)
		beginsecond = frame_actual;
	if (frame_actual - beginsecond > 1000)
	{
		str = "FPS = " + to_string(nb_frame);
		nb_frame = 0;
		beginsecond = 0;
	}
	else
		nb_frame++;
	if (framedelay > frame_actual - framestart)
		SDL_Delay(framedelay - (frame_actual - framestart));
	framestart = SDL_GetTicks();
}
