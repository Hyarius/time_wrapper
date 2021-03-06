#include "template.h"

static int type = -1;

void			draw_triangle_texture(t_point a, t_point b, t_point c)
{
	GLfloat g_vertex_buffer_data[] = {
		(float)a.x, (float)a.y, 0.0f,
		(float)b.x, (float)b.y, 0.0f,
		(float)c.x, (float)c.y, 0.0f,
	};

	GLfloat g_uv_buffer_data[] = {
		(float)a.r,  (float)a.g,
		(float)b.r,  (float)b.g,
		(float)c.r,  (float)c.g,
	};

	GLfloat g_alpha_buffer_data[] = {
		(float)a.b,
		(float)b.b,
		(float)c.b,
	};

	glBindVertexArray(get_vertex_array());

	glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, get_texture_buffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, get_alpha_buffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_alpha_buffer_data), g_alpha_buffer_data, GL_STATIC_DRAW);

	if (type != 0)
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glUseProgram(get_program_sprite());

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, get_texture_buffer());
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, get_alpha_buffer());
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, NULL);
		type = 0;
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void			draw_triangle_color(t_point a, t_point b, t_point c)
{
	GLfloat g_vertex_buffer_data[] = {
		(float)a.x, (float)a.y, 0.0f,
		(float)b.x, (float)b.y, 0.0f,
		(float)c.x, (float)c.y, 0.0f,
	};

	GLfloat g_color_buffer_data[] = {
		(float)a.r,  (float)a.g,  (float)a.b, (float)a.a,
		(float)b.r,  (float)b.g,  (float)b.b, (float)b.a,
		(float)c.r,  (float)c.g,  (float)c.b, (float)c.a,
	};

	glBindVertexArray(get_vertex_array());

	glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, get_color_buffer());
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	if (type != 1)
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glUseProgram(get_program_color());

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, get_color_buffer());
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		type = 1;
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

vector<GLfloat> g_vertex_vector_data;
vector<GLfloat> g_uv_vector_data;
vector<GLfloat> g_alpha_vector_data;
vector<GLfloat> g_color_vector_data;

void			add_triangle_texture(t_point a, t_point b, t_point c)
{
	g_vertex_vector_data.insert(g_vertex_vector_data.end(),{(float)(a.x),(float)(a.y),0.0f ,(float)(b.x),(float)(b.y),0.0f ,(float)(c.x),(float)(c.y),0.0f });
	g_uv_vector_data.insert(g_uv_vector_data.end(),{(float)(a.r),(float)(a.g) ,(float)(b.r),(float)(b.g) ,(float)(c.r),(float)(c.g) });
	g_alpha_vector_data.insert(g_alpha_vector_data.end(), {(float)(a.b), (float)(b.b), (float)(c.b)});
}

void			add_triangle_color(t_point a, t_point b, t_point c)
{
	g_vertex_vector_data.insert(g_vertex_vector_data.end(),{(float)(a.x),(float)(a.y),0.0f ,(float)(b.x),(float)(b.y),0.0f ,(float)(c.x),(float)(c.y),0.0f });
	g_color_vector_data.insert(g_uv_vector_data.end(),{(float)(a.r),(float)(a.g),(float)(a.b),(float)(a.a) ,(float)(b.r),(float)(b.g),(float)(b.b),(float)(b.a) ,(float)(c.r),(float)(c.g),(float)(c.b),(float)(c.a) });
}

void			render_triangle_texture(GLuint texture_id)
{
	if (g_vertex_vector_data.size() == 0 || g_uv_vector_data.size() == 0 || g_alpha_vector_data.size() == 0)
		return ;
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
	glBufferData(GL_ARRAY_BUFFER, g_vertex_vector_data.size() * sizeof(GLfloat), &g_vertex_vector_data.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, get_texture_buffer());
	glBufferData(GL_ARRAY_BUFFER, g_uv_vector_data.size() * sizeof(GLfloat), &g_uv_vector_data.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, get_alpha_buffer());
	glBufferData(GL_ARRAY_BUFFER, g_alpha_vector_data.size() * sizeof(GLfloat), &g_alpha_vector_data.front(), GL_STATIC_DRAW);

	if (type != 0)
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glUseProgram(get_program_sprite());

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, get_texture_buffer());
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, get_alpha_buffer());
		glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, NULL);
		type = 0;
	}

	glDrawArrays(GL_TRIANGLES, 0, g_vertex_vector_data.size());

	g_vertex_vector_data.clear();
	g_uv_vector_data.clear();
	g_alpha_vector_data.clear();
}

void			render_triangle_color()
{
	if (g_vertex_vector_data.size() == 0 || g_color_vector_data.size() == 0)
		return;

	glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
	glBufferData(GL_ARRAY_BUFFER, g_vertex_vector_data.size() * sizeof(GLfloat), &g_vertex_vector_data.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, get_color_buffer());
	glBufferData(GL_ARRAY_BUFFER, g_color_vector_data.size() * sizeof(GLfloat), &g_color_vector_data.front(), GL_STATIC_DRAW);

	if (type != 1)
	{
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		glUseProgram(get_program_color());

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, get_vertex_buffer());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, get_color_buffer());
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		type = 1;
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);

	g_vertex_vector_data.clear();
	g_color_vector_data.clear();
}
