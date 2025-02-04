/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:05:01 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/04 12:53:53 by lroussel         ###   ########.fr       */
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

# define HEIGHT 2000
# define WIDTH 2000
//# define HEIGHT (get_swidth() - 40)
//# define WIDTH (get_sheight() - 20)

typedef struct s_mimg
{
	void			*img;
	void			*addr;
	int				bpp;
	int				ll;
	int				endian;
	int				width;
	int				height;
}	t_img;

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

typedef	struct s_pixel_data
{
	t_vector2	pos;
	float	depth;
}	t_pixel_data;

typedef struct s_point
{
	t_vector3	pos;
	int			color;
	int			can_mirror;
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
	TIT,
	BGG,
	AXIS,
	MIRROR,
	CTRL_UP,
	CTRL_DOWN,
	CTRL_LEFT,
	CTRL_RIGHT,
	CTRL_REDUCE_X,
	CTRL_ADD_X,
	CTRL_REDUCE_Y,
	CTRL_ADD_Y,
	CTRL_REDUCE_Z,
	CTRL_ADD_Z,
	CTRL_ZOOM,
	CTRL_UNZOOM
};

enum ButtonType {
	NAVBAR,
	TITLE,
	CIRCLE,
	TOGGLE,
	KEYBOX
};

typedef struct s_button
{
	enum ButtonId	id;
	int	uniq_id;
	enum ButtonType	type;
	char	*name;
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
	t_img	bg;
	void	*bg_color;
	int	axis;
	int	mirror;
	t_img	**backgrounds;
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

typedef struct s_key
{
	int	id;
	int	v;
	enum ButtonId	button;
}	t_key;

typedef struct s_edit
{
	t_key	old_key;
	t_key	new_key;
}	t_edit;

typedef struct s_controls
{
	t_key	up;
	t_key	down;
	t_key	left;
	t_key	right;
	t_key	reduce_x;
	t_key	add_x;
	t_key	reduce_y;
	t_key	add_y;
	t_key	reduce_z;
	t_key	add_z;
	t_key	zoom;
	t_key	unzoom;
	t_edit	edit;
}	t_controls;

typedef struct s_view
{
	float	yaw;
	float	pitch;
	float	roll;
	float	fov;
}	t_view;

typedef struct s_fdf
{
	void			*mlx;
	void			*window;
	t_img			img;
	t_map			*map;
	t_display_data		*display_data;
	t_controls		controls;
	int				must_update;
	t_vector3	camera;
	int	camerai;
	t_view	view;
	float	**depth;
	t_vector2	par;
	t_vector2	screen;
}	t_fdf;

typedef struct s_rgb
{
	int	t;
	int	r;
	int	g;
	int	b;
}	t_rgb;

int			on_update(t_fdf *fdf);
t_fdf	*f(t_fdf *v);

//hook.c
int			keys_hook(int keycode, t_fdf *fdf);
int			on_move(int x, int y, t_navbar *navbar);
int			on_click(int id, int x, int y, t_fdf *fdf);
int			rotatation_check(int keycode, t_fdf *fdf);
int			translation_check(int keycode, t_fdf *fdf);
int			zoom_check(int keycode, t_fdf *fdf);

//destructor.c
void		destruct(t_fdf *fdf);
int			on_close(t_fdf *fdf);

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

//backgrounds.c
void		init_backgrounds(t_fdf *fdf);
void		free_backgrounds(t_fdf *fdf);

//init/navbar.c
void		init_navbar(t_fdf *fdf);

//color.c
int			get_color(char *value);
int			create_color(float x, float y, float z, t_vector3 map_size);
int			color_between(int ca, int cb, float v, float t);

int			ft_abs(int v);

t_pixel_data	pixel_pos(t_fdf *fdf, t_vector3 v3, int mirror);

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
int test(t_vector2 v);
int gakarbou(t_vector2 v);

//utils/navbar/default_color.c
int	dark_gray(void);
int	gray(void);
int	light_gray(void);

int	put_pixel(t_fdf *fdf, t_vector2 pos, int color, float alpha);
void	draw_navbar(t_fdf *fdf);
void	draw_button(t_fdf *fdf, t_button *button);
void	draw_buttons(t_fdf *fdf, t_button **buttons);

void	update_buttons_texts(t_fdf *fdf);

//button.c
t_button	*set_color(t_button *button, void *default_color, void *hover_color, void *pressed_color);
t_button	*create_button(enum ButtonId id, enum ButtonType type, char *name, t_vector2 size, t_vector2 offset);
int	buttons_count(t_button **buttons);

//utils/navbar
void	add_category(enum CategoryId id, char *title);
void	add_button(t_category *category, t_button *button);
t_navbar	*get_navbar(void);
int	active_navbar(int v);
void		free_navbar(void);
t_category	*get_navbar_category(enum CategoryId id);

//templates/keybox.c
void	draw_keybox(t_fdf *fdf, t_button *button);
int	keybox_color(t_vector2 v, int w, int h);
int	keybox_color_hover(t_vector2 v, int w, int h, int selected);
int	keybox_color_pressed(t_vector2 v, int w, int h);

//templates/toggle.c
void	draw_toggle(t_fdf *fdf, t_button *button);
int	toggle_color(t_vector2 v, int w, int h);
int	toggle_color_hover(t_vector2 v, int w, int h, int selected);
int	toggle_color_pressed(t_vector2 v, int w, int h);

void	draw_square(t_fdf *fdf, t_button *button);

//initialization/controls.c
void	init_controls(t_fdf *fdf);
void	change_key(t_fdf *fdf);
char	*get_name_for(int key);
t_key	get_key_from(t_fdf *fdf, enum ButtonId id);

void    change_background(t_fdf *fdf, int (color)(t_vector2, int, int, int));

t_fdf	*get_fdf(void);

void    init_depth(t_fdf *fdf);
void    clear_depth(t_fdf *fdf);
void    free_depth(t_fdf *fdf);

int cohenSutherlandClip(t_vector2 *v1, t_vector2 *v2);

int	*get_resolution(void);
int	get_swidth(void);
int	get_sheight(void);
#endif
