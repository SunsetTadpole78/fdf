/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:05:01 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/07 16:41:27 by lroussel         ###   ########.fr       */
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

# define HEIGHT (get_swidth() - 40)
# define WIDTH (get_sheight() - 20)

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
	int			hardcoded_color;
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

enum SubCategoryId {
	CONTROLS_ISO,
	CONTROLS_CONIC,
	CONTROLS_PARALLEL,
	OTHER_PARALLEL,
	OTHER_ISO
};

enum ButtonId {
	NAV,
	TIT,
	BGG,
	LINE,
	I_AXIS,
	P_AXIS,
	MIRROR,
	CTRLI_UP,
	CTRLI_DOWN,
	CTRLI_LEFT,
	CTRLI_RIGHT,
	CTRLI_RX1,
	CTRLI_RX2,
	CTRLI_RY1,
	CTRLI_RY2,
	CTRLI_RZ1,
	CTRLI_RZ2,
	CTRLI_ZOOM,
	CTRLI_UNZOOM,
	CTRLI_YA1,
	CTRLI_YA2,
	CTRLC_FRONT,
	CTRLC_BEHIND,
	CTRLC_LEFT,
	CTRLC_RIGHT,
	CTRLC_UP,
	CTRLC_DOWN,
	CTRLC_RX1,
	CTRLC_RX2,
	CTRLC_RY1,
	CTRLC_RY2,
	CTRLC_RZ1,
	CTRLC_RZ2,
	CTRLC_FOV1,
	CTRLC_FOV2,
	CTRLC_YA1,
	CTRLC_YA2,
	CTRLP_UP,
	CTRLP_DOWN,
	CTRLP_LEFT,
	CTRLP_RIGHT,
	CTRLP_RX1,
	CTRLP_RX2,
	CTRLP_RY1,
	CTRLP_RY2,
	CTRLP_ZOOM,
	CTRLP_UNZOOM,
	CTRLP_YA1,
	CTRLP_YA2
};

enum ButtonType {
	NAVBAR,
	TITLE,
	CIRCLE,
	CUBE,
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

typedef struct s_subcategory
{
	enum SubCategoryId	id;
	void	*showable;
	t_button	**buttons;
	struct s_category	*category;
}	t_subcategory;

typedef struct s_category
{
	enum CategoryId	id;
	t_button	*main;
	t_button	**buttons;
	t_subcategory	**subs;
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
	float	min_y;
	float	max_y;
	t_point		**points;
}	t_map;

typedef struct s_navbar
{
	t_category		**categories;
	t_category		*actual;
	int		must_update;
}	t_navbar;

enum KeyId
{
	I_UP,
	I_DOWN,
	I_LEFT,
	I_RIGHT,
	I_RX1,
	I_RX2,
	I_RY1,
	I_RY2,
	I_RZ1,
	I_RZ2,
	I_ZOOM,
	I_UNZOOM,
	I_YA1,
	I_YA2,
	C_FRONT,
	C_BEHIND,
	C_LEFT,
	C_RIGHT,
	C_UP,
	C_DOWN,
	C_RX1,
	C_RX2,
	C_RY1,
	C_RY2,
	C_RZ1,
	C_RZ2,
	C_FOV1,
	C_FOV2,
	C_YA1,
	C_YA2,
	P_UP,
	P_DOWN,
	P_LEFT,
	P_RIGHT,
	P_RX1,
	P_RX2,
	P_RY1,
	P_RY2,
	P_ZOOM,
	P_UNZOOM,
	P_YA1,
	P_YA2
};

typedef struct s_key
{
	int	id;
	enum KeyId	key_id;
	int	v;
	enum ButtonId	button;
}	t_key;

typedef struct s_edit
{
	t_key	old_key;
	t_key	new_key;
}	t_edit;
/* 
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
 */
enum ViewType
{
	ISOMETRIC,
	CONIC,
	PARALLEL
};

typedef struct s_e
{
	t_key	*old_key;
	t_key	*new_key;
}	t_e;

typedef struct s_c
{
	t_key	**keys;
	t_e	edit;
}	t_c;

typedef struct s_isometric
{
	t_c		controls;
	t_vector2	offset;
	t_vector3	rotation;
	float			zoom;
	float			zoom_base;
	int	axis;
	int	mirror;
	float	y_amplifier;
}	t_isometric;

typedef struct s_conic
{
	t_c		controls;
	t_vector3	camera;
	float	default_z;
	t_vector3	rotation;
	float	fov;
	float	yaw;
	float	pitch;
	float			zoom;
	float			zoom_base;
	float	y_amplifier;
}	t_conic;

typedef struct s_parallel
{
	t_c		controls;
	t_vector2	offset;
	t_vector2	rotation;
	float			zoom;
	float			zoom_base;
	int	axis;
	float	y_amplifier;
}	t_parallel;

typedef struct s_background
{
	t_img	bg;
	void	*bg_color;
	t_img	**backgrounds;
}	t_background;

typedef struct s_fdf
{
	void			*mlx;
	void			*window;
	t_img			img;
	t_map			*map;
	int				must_update;
	float	**depth;
	t_vector2	screen;
	enum ViewType		type;
	void	*pixel_pos;
	t_isometric	isometric;
	t_conic		conic;
	t_parallel		parallel;
	t_vector3	pivot_point;
	t_background	*background;
	t_img	**backgrounds;
	int	only_points;
	t_key	*edit_key;
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

void		init_isometric(t_fdf *fdf);
void		init_conic(t_fdf *fdf);
void		init_parallel(t_fdf *fdf);

t_key   key(int v, enum ButtonId id);

//backgrounds.c
void		init_backgrounds(t_fdf *fdf);
void		free_backgrounds(t_fdf *fdf);

//init/navbar.c
void		init_navbar(t_fdf *fdf);

//color.c
int			get_color(char *value);
int			from_rgb(t_rgb rgb);
int			color_between(int ca, int cb, float v, float t);
void	update_colors(t_fdf *fdf, int (color)(t_vector3, t_vector2, t_vector3));

int			ft_abs(int v);

int	is_isometric(void);
int	is_conic(void);
int	is_parallel(void);

t_pixel_data	pixel_pos(t_fdf *fdf, t_vector3 v3, int mirror);
t_pixel_data	ipp(t_fdf *fdf, t_vector3 v3, int mirror);
t_pixel_data	cpp(t_fdf *fdf, t_vector3 v3, int mirror);
t_pixel_data	ppp(t_fdf *fdf, t_vector3 v3, int mirror);

int     black(void);
void		free_buttons(t_button **buttons);

int	rnb(t_vector2 v, int w, int h);
int diag(t_vector2 v, int w, int h);
int gakarbou(t_vector2 v, int w, int h);
int test(t_vector2 v, int w, int h);
int montain(t_vector2 v, int w, int h);
int neon(t_vector2 v, int w, int h);
int win(t_vector2 v, int w, int h);
int ft(t_vector2 v, int w, int h);
int rick(t_vector2 v, int w, int h);
int larry(t_vector2 v, int w, int h);
int hello_kitty(t_vector2 v, int w, int h);

int white(void);
int subject(t_vector3 v, t_vector2 mimay);
int blue(t_vector3 v, t_vector2 mimay);
int relief(t_vector3 v);
int rgb(t_vector3 v, t_vector2 mimay, t_vector3 size);
int pays(t_vector3 v);
int mars(t_vector3 v);
int black_and_white(t_vector3 v);
int blue_and_yellow(t_vector3 v, t_vector2 mimay);
int random_c(t_vector3 v);

//utils/navbar/default_color.c
int	dark_gray(void);
int	gray(void);
int	light_gray(void);

int	put_pixel(t_fdf *fdf, t_vector2 pos, int color, float alpha);
void	draw_navbar(t_fdf *fdf);
void	draw_button(t_fdf *fdf, t_button *button);
void	draw_buttons(t_fdf *fdf, t_button **buttons);

void	update_navbar_texts(t_fdf *fdf);

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

void	add_subbutton(t_subcategory *sub, t_button *button);
void	add_sub(t_category *category, enum SubCategoryId id, int (showable)(void));
t_subcategory	*get_sub(t_category *category, enum SubCategoryId id);

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

void	draw_cube(t_fdf *fdf, t_button *button);

//initialization/controls.c
void	change_key(t_fdf *fdf, int keycode);
char	*get_name_for(int key);

void    change_background(t_fdf *fdf, int (color)(t_vector2, int, int, int));

t_fdf	*get_fdf(void);

void    init_depth(t_fdf *fdf);
void    clear_depth(t_fdf *fdf);
void    free_depth(t_fdf *fdf);

int cohenSutherlandClip(t_vector2 *v1, t_vector2 *v2);

int	*get_resolution(void);
int	get_swidth(void);
int	get_sheight(void);

int	outside_p(t_vector2 v);

void	init_contr(t_c *controls);
t_c	*get_controls(t_fdf *fdf);
void	add_key(t_c *controls, enum KeyId id, int key, enum ButtonId button);
int	is_key(t_c controls, enum KeyId id, int keycode);
t_key	*get_key(t_c controls, enum KeyId id);
t_key	*get_key_from(t_c *controls, enum ButtonId id);
void	free_contr(t_c controls);

void	algo(t_fdf *fdf, t_vector2 po1, t_vector2 po2, int d1, int d2, int ca, int cb);

#endif
