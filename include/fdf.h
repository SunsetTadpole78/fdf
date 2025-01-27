/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:05:01 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/27 11:23:39 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"

#include <stdio.h>

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <math.h>

# define HEIGHT 1040
# define WIDTH 1900

typedef struct s_vector2
{
	float	x;
	float	y;
}	t_vector2;

typedef struct s_vector3
{
	float	x;
	float	y;
	float	z;
}	t_vector3;

typedef struct s_point
{
	t_vector3	pos;
	int			color;
}	t_point;

typedef struct s_line
{
	t_point			point1;
	t_point			point2;
	struct s_line	*previous;
	struct s_line	*next;
}	t_line;

enum CategoryId {
	BG,
	LINES,
	CONTROLS,
	OTHER
};

enum ButtonId {
	NAV,
	BGG
};

enum ButtonType {
	NAVBAR,
	CIRCLE
};

typedef struct s_button
{
	enum ButtonId	id;
	int	uniq_id;
	enum ButtonType	type;
	t_vector2	size;
	t_vector2	offset;
	void	*color;
	void	*hover_color;
	void	*pressed_color;
	int	selected;
	int	hover;
	struct s_category	*category;
}	t_button;

typedef struct s_category
{
	enum CategoryId	id;
	t_button	*main;
	t_button	**buttons;
	char	*title;
}	t_category;

typedef struct s_display_data
{
	t_vector3	pivot_point;
	t_vector2	offset;
	t_vector3	rotate;
	float			zoom;
	float			zoom_v;
	void	*bg;
}	t_display_data;

typedef struct s_map
{
	t_vector3       size;
	int	min_y;
	int	max_y;
	t_point		**points;
}	t_map;

typedef struct s_navbar
{
	t_category		**categories;
	t_category		*actual;
	int		must_update;
}	t_navbar;

typedef struct s_fdf
{
	void			*mlx;
	void			*window;
	void			*img;
	void			*addr;
	int				bpp;
	int				ll;
	int				endian;
	t_map			*map;
	t_display_data		*display_data;
	int				must_update;
}	t_fdf;

typedef struct s_rgb
{
	int	t;
	int	r;
	int	g;
	int	b;
}	t_rgb;

int			on_update(t_fdf *fdf);

//hook.c
int			keys_hook(int keycode, t_fdf *fdf);
int			on_move(int x, int y, t_navbar *navbar);
int			on_click(int id, int x, int y, t_fdf *fdf);
int			rotate(int keycode, t_fdf *fdf);
int			translate(int keycode, t_fdf *fdf);
int			zoom(int keycode, t_fdf *fdf);

//destructor.c
void		destruct(t_fdf *fdf);

//lines_utils.c
void	set_map_data(char ***lines, t_map *map);

//lines.c
t_line		*build_line(char ***lines, t_vector2 p1, t_vector2 p2);
void		free_lines(char ****lines, int y);
int			add_line(char *line, char ****lines, int y);
int			init_lines(char *path, char ****lines, int *fd);

//map.c
void		free_map(t_map *map);
void		add_to_map(t_map *map, t_line *line);
t_map		*parse_map(char *path);

//mlx_manager.c
t_fdf		*create_window(t_map *map);
void		draw_map(t_fdf *fdf);

//points.c

//utils.c
float		chars_to_float(char *nbr);
int			ft_distance(t_vector2 v1, t_vector2 v2);

//vector.c
t_vector2	vector2(float x, float y);

//display_data.c
void		init_display_data(t_fdf *fdf);

//init/navbar.c
void		init_navbar(t_fdf *fdf);

//color.c
int			get_color(char *value);
int			create_color(float x, float y, float z, t_vector3 map_size);
int			color_between(int ca, int cb, float v, float t);

int			ft_abs(int v);

t_vector2	pixel_pos(t_fdf *fdf, t_vector3 v3);

int     black(void);
void		free_buttons(t_button **buttons);

int	rnb(t_vector2 v, int w, int h);
int ver(t_vector2 v, int w, int h);
int hor(t_vector2 v, int w, int h);
int diag(t_vector2 v, int w, int h);
int diag_m(t_vector2 v, int w, int h);
int circ(t_vector2 v, int w, int h);
int circ_m(t_vector2 v, int w, int h);
int rnb2(t_vector2 v, int w, int h);
int rnb2_m(t_vector2 v, int w, int h);
int spir(t_vector2 v, int w, int h);
int spir_m(t_vector2 v, int w, int h);

//utils/navbar/default_color.c
int	dark_gray(void);
int	gray(void);
int	light_gray(void);

int	put_pixel(t_fdf *fdf, t_vector2 pos, int color, float alpha);
void	draw_navbar(t_fdf *fdf);
void	draw_button(t_fdf *fdf, t_button *button);
void	draw_buttons(t_fdf *fdf, t_button **buttons);

void	update_navbar_text(t_fdf *fdf);

//button.c
t_button	*set_color(t_button *button, void *default_color, void *hover_color, void *pressed_color);
t_button	*create_button(enum ButtonId id, enum ButtonType type, t_vector2 size, t_vector2 offset);
int	buttons_count(t_button **buttons);

//utils/navbar
void	add_category(enum CategoryId id, char *title);
void	add_button(t_category *category, t_button *button);
t_navbar	*get_navbar(void);
int	active_navbar(int v);
void		free_navbar(void);
t_category	*get_navbar_category(enum CategoryId id);

#endif
