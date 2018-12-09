#include "template.h"

s_image_button::s_image_button(string *p_text, int p_text_color,
					t_image p_image, t_vect p_coord, t_vect p_size, int border)
{
	text = p_text;
	text_color = p_text_color;
	coord[0] = p_coord;
	size[0] = p_size;
	coord[1] = p_coord + border;
	size[1] = p_size - (border * 2);
	coord[2] = coord[1] + size[1] / 2;
	if (text != NULL && *text != "")
	{
		text_size = calc_text_size(*text, size[1]);
		surface = TTF_RenderText_Blended(get_font(text_size), p_text->c_str(), get_color(p_text_color));
		if (surface == NULL)
			error_exit("can't create the text to image_button", 3567);
		text_image = new t_image(surface);
		image_coord = t_vect(coord[2].x - text_image->surface->w / 2, coord[2].y - text_image->surface->h / 2);
		image_size = t_vect(text_image->surface->w, text_image->surface->h);
	}
	else
	{
		text_size = -1;
		text_image = NULL;
	}
	image = p_image;
	funct = NULL;
	data = NULL;
	draw_funct = draw_centred_text;
}

s_image_button::s_image_button(t_image p_image, t_vect p_coord, t_vect p_size)
{
	text = NULL;
	coord[0] = p_coord;
	size[0] = p_size;
	image = p_image;
	text_image = NULL;
	funct = NULL;
	data = NULL;
}

void		s_image_button::draw_self()
{
	image.draw_self(coord[0], size[0]);
	if (text_image != NULL)
		text_image->draw_self(image_coord, image_size);
	else if (text != NULL && *text != "")
	{
		if (text_size == -1 || size[1].x > calc_text_len(*text, text_size)
							|| size[1].y > get_char(text_size, BLACK, 'M')->surface->h)
			text_size = calc_text_size(*text, size[1]);
		this->draw_funct(*text, text_size, coord[2], text_color);
	}
}
