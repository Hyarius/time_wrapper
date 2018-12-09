#include "template.h"

s_image_entry::s_image_entry(	string *p_desc, string *p_text, int p_text_color,
								t_entry_comp **p_selected_entry,
								t_image p_image, t_image p_selec_image,
								t_vect p_coord, t_vect p_size, int border)
{
	desc = p_desc;
	text = p_text;
	back = "";
	front = "";
	text_color = p_text_color;
	max_len = 16;
	coord[0] = p_coord;
	size[0] = p_size;
	coord[1] = p_coord + border;
	size[1] = p_size - (border * 2);
	coord[2] = coord[1] + t_vect(0, size[1].y / 2);
	if (desc != NULL && *desc != "")
		desc_size = calc_text_max_size(*desc, size[1] - border * 2);
	text_size = calc_text_max_size("M", size[1] - border * 2);
	selected_entry = p_selected_entry;
	image = p_image;
	selec_image = p_selec_image;
	draw_funct = draw_lined_text;
}

void		s_image_entry::draw_self()
{
	if (*(selected_entry) == this)
		selec_image.draw_self(coord[0], size[0]);
	else
		image.draw_self(coord[0], size[0]);
	if (text != NULL && *text == "" && desc != NULL && *desc != "")
		this->draw_funct(*desc, desc_size, coord[2], text_color);
	if (text != NULL && *text != "")
		this->draw_funct(front + *text + back, text_size, coord[2], text_color);
}
