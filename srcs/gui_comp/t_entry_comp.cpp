#include "template.h"

void			t_entry_comp::add_text(string new_text)
{
	if (text != NULL)
		if (text->size() < max_len)
			if (calc_text_len(*text + new_text, text_size) <= size[1].x)
				*text += new_text;
}

void			t_entry_comp::delete_text()
{
	if (text != NULL)
		if (text->size() != 0)
			text->pop_back();
}

void			t_entry_comp::click(t_vect mouse)
{
	if (mouse > coord[0] && mouse < coord[0] + size[0])
	{
		*(selected_entry) = this;
		SDL_StartTextInput();
	}
}

void			t_entry_comp::set_funct_param(gui_funct p_funct, t_data p_data, d_funct p_draw_funct)
{

}

void		t_entry_comp::set_back(string p_back)
{
	back = p_back;
}

void		t_entry_comp::set_front(string p_front)
{
	front = p_front;
}
