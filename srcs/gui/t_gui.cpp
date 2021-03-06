#include "template.h"

s_gui::s_gui()
{
	entry = NULL;
	unit = t_vect(get_win_size().x / 15, get_win_size().y / 10);
}

s_gui::s_gui(int x, int y)
{
	entry = NULL;
	unit = t_vect(get_win_size().x / x, get_win_size().y / y);
}

void		s_gui::draw_self()
{
	size_t i = 0;
	size_t j;

	while (i < object_list.size())
	{
		j = 0;
		while (j < object_list[i].size())
		{
			object_list[i].at(j)->draw_self();
			j++;
		}
		i++;
	}
}

void		s_gui::click()
{
	size_t i = 0;
	size_t j = 0;
	t_vect mouse = get_mouse_coord();

	if (entry != NULL)
	{
		entry = NULL;
		SDL_StopTextInput();
	}
	while (i < object_list.size())
	{
		j = 0;
		while (j < object_list[i].size())
		{
			object_list[i].at(j)->click(mouse);
			j++;
		}
		i++;
	}
}

void		s_gui::add(int rep, t_gui_obj *object)
{
	if (object_list.size() < (size_t)(rep + 1))
		object_list.resize(rep + 1);
	object_list[rep].push_back(object);
}

void		s_gui::add(t_gui_obj *object)
{
	if (object_list.size() < 1)
		object_list.resize(1);
	object_list[0].push_back(object);
}

void		s_gui::verify_ID_object(int ID_OBJ)
{
	size_t i = 0;
	while (i < this->object_list[ID_OBJ].size())
	{
		this->object_list[ID_OBJ][i]->verify();
		i++;
	}
}
