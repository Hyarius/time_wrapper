#ifndef TEMPLATE_GUI_H
# define TEMPLATE_GUI_H

# include "template_gui_structure.h"

using namespace std;

typedef struct		s_gui_obj
{
	virtual void	draw_self() = 0;
	virtual void	click(t_vect mouse) = 0;
	virtual void	verify();
	virtual 		~s_gui_obj() {}
}					t_gui_obj;

typedef struct		s_button : t_gui_obj
{
	t_button_comp	*button;

					s_button(t_button_comp *p_button, gui_funct p_funct, t_data p_data);
					s_button(t_button_comp *p_button, gui_funct p_funct, t_data p_data, d_funct p_draw_funct);
	void			draw_self();
	void			click(t_vect mouse);
}					t_button;

typedef struct		s_entry : t_gui_obj
{
	t_entry_comp	*entry;
	string			text;

					s_entry(t_entry_comp *p_entry);
	void			draw_self();
	void			click(t_vect mouse);
}					t_entry;

typedef struct		s_gui
{
	vector<vector<t_gui_obj *>>
					object_list;
	t_entry_comp	*entry;
	t_vect			unit;

					s_gui();
					s_gui(int x, int y);
	void			add(t_gui_obj *object);
	void			add(int rep, t_gui_obj *object);
	void			verify_ID_object(int ID_OBJ);
	void			draw_self();
	void			click();
}					t_gui;

#endif
