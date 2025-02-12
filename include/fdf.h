/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:05:01 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 23:24:14 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <math.h>

# ifndef WINDOW_SIZE
#  define WINDOW_SIZE 1
# endif

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

typedef struct s_line_data
{
	t_vector2	delta;
	t_vector2	s;
	float		e;
	float		e2;
	float		cur;
	float		tot;
	float		step;
}	t_line_data;

typedef struct s_pixel_data
{
	t_vector2	pos;
	float		depth;
	int			color;
}	t_pixel_data;

typedef struct s_point
{
	t_vector3	pos;
	int			color;
	int			hardcoded_color;
	int			can_mirror;
}	t_point;

enum e_CategoryId
{
	BG,
	LINES,
	CONTROLS,
	OTHER
};

enum e_SubCategoryId
{
	CONTROLS_ISO,
	CONTROLS_CONIC,
	CONTROLS_PARALLEL,
	OTHER_ISO,
	OTHER_CONIC,
	OTHER_PARALLEL
};

enum e_ButtonId
{
	NAV,
	TIT,
	BGG,
	LINE,
	I_AXIS,
	I_MIRROR,
	I_ONLY_POINTS,
	C_MIRROR,
	C_ONLY_POINTS,
	P_AXIS,
	P_MIRROR,
	P_ONLY_POINTS,
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

enum e_ButtonType
{
	NAVBAR,
	TITLE,
	CIRCLE,
	CUBE,
	TOGGLE,
	KEYBOX
};

typedef struct s_button
{
	enum e_ButtonId		id;
	int					uniq_id;
	enum e_ButtonType	type;
	char				*name;
	t_vector2			size;
	t_vector2			offset;
	void				*color;
	void				*hover_color;
	void				*pressed_color;
	int					selected;
	int					hover;
	struct s_category	*category;
}	t_button;

typedef struct s_subcategory
{
	enum e_SubCategoryId	id;
	void					*showable;
	t_button				**buttons;
	struct s_category		*category;
}	t_subcategory;

typedef struct s_category
{
	enum e_CategoryId	id;
	t_button			*main;
	t_button			**buttons;
	t_subcategory		**subs;
	char				*title;
}	t_category;

typedef struct s_display_data
{
	t_vector3	pivot_point;
	t_vector2	offset;
	t_vector3	rotate;
	float		zoom;
	float		zoom_v;
	t_img		bg;
	void		*bg_color;
	int			axis;
	int			mirror;
	t_img		**backgrounds;
}	t_display_data;

typedef struct s_map
{
	t_vector3	size;
	float		min_y;
	float		max_y;
	t_point		**points;
}	t_map;

typedef struct s_navbar
{
	t_category	**categories;
	t_category	*actual;
	int			must_update;
}	t_navbar;

enum e_KeyId
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
	int				id;
	enum e_KeyId	key_id;
	int				v;
	enum e_ButtonId	button;
	int				pressed;
}	t_key;

typedef struct s_edit
{
	t_key		old_key;
	t_key		new_key;
}	t_edit;

enum e_ViewType
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

typedef struct s_controls
{
	t_key	**keys;
	t_e		edit;
}	t_controls;

typedef struct s_isometric
{
	t_controls	controls;
	t_vector2	offset;
	t_vector3	rotation;
	float		zoom;
	float		zoom_base;
	int			axis;
	int			mirror;
	float		y_amplifier;
	int			only_points;
}	t_isometric;

typedef struct s_conic
{
	t_controls	controls;
	t_vector3	camera;
	float		default_z;
	t_vector3	rotation;
	float		fov;
	float		yaw;
	float		pitch;
	float		zoom;
	float		zoom_base;
	int			mirror;
	float		y_amplifier;
	int			only_points;
}	t_conic;

typedef struct s_parallel
{
	t_controls	controls;
	t_vector2	offset;
	t_vector2	rotation;
	float		zoom;
	float		zoom_base;
	int			axis;
	int			mirror;
	float		y_amplifier;
	int			only_points;
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
	float			**depth;
	t_vector2		screen;
	enum e_ViewType	type;
	void			*position_adr;
	t_isometric		isometric;
	t_conic			conic;
	t_parallel		parallel;
	t_vector3		pivot_point;
	t_background	*background;
	t_img			**backgrounds;
	t_key			*edit_key;
	int				keys;
}	t_fdf;

//drawers/axes.c
void			draw_axes(t_fdf *fdf);

//drawers/background.c
void			change_background(t_fdf *fdf,
					int (color)(t_vector2, int, int, int));
void			draw_background(t_fdf *fdf);

//drawers/line.c
void			process_line(t_fdf *fdf, t_pixel_data p1, t_pixel_data p2);
void			draw_line(t_fdf *fdf, t_point a, t_point b, int mirror);

//drawers/map.c
void			draw_map(t_fdf *fdf);

//events/conic/press.c
void			conic_key_event(t_fdf *fdf);

//events/isometric/press.c
void			isometric_key_event(t_fdf *fdf);

//events/parallel/press.c
void			parallel_key_event(t_fdf *fdf);
void			rotate_parallel(t_parallel *parallel,
					t_controls controls, int keycode);

//events/controls_events.c
int				on_press_controls(int keycode, t_fdf *fdf);

//events/events.c
int				on_press(int keycode, t_fdf *fdf);
int				on_release(int keycode, t_fdf *fdf);
int				on_expose(t_fdf *fdf);

//events/navbar_events.c
int				on_move_navbar(int x, int y, t_navbar *navbar);
int				check_outnav(int y, t_navbar *navbar);
int				on_click_navbar(int id, int x, int y, t_navbar *navbar);

//initialization/navbar/controls.c
void			register_iso_controls_buttons(t_subcategory *c,
					t_controls ic);
t_subcategory	*register_sub_controls(enum e_SubCategoryId id, void *fn);
void			register_conic_controls_buttons(t_subcategory *c,
					t_controls cc);
void			register_parallel_controls_buttons(t_subcategory *c,
					t_controls pc);

//initialization/navbar/comsetic.c
void			register_background_buttons(void);
void			register_lines_buttons(void);

//initialization/navbar/navbar.c
void			init_navbar(t_fdf *fdf);

//initialization/navbar/other.c
void			register_iso_other_buttons(void);
void			register_conic_other_buttons(void);
void			register_parallel_other_buttons(void);

//initialization/backgrounds.c
void			init_backgrounds(t_fdf *fdf);
void			free_backgrounds(t_fdf *fdf);

//initialization/views/conic.c
void			init_conic(t_fdf *fdf);

//initialization/views/isometric.c
void			init_isometric(t_fdf *fdf);

//initialization/views/parallel.c
void			init_parallel(t_fdf *fdf);

//initialization/backgrounds.c
void			init_backgrounds(t_fdf *fdf);
void			free_backgrounds(t_fdf *fdf);

//initialization/data.c
t_fdf			*init_fdf(void);
void			init_mlx(t_fdf *fdf, t_map *map);

//initialization/file_lines.c
int				add_line(char *line, char ****lines, int y);
int				init_lines(char *path, char ****lines, int *fd);

//initialization/map.c
t_map			*init_map(char ***lines);
t_map			*parse_map(char *path);
void			set_map_data(char ***lines, t_map *map);

//utils/buttons/button.c
t_button		*create_button(enum e_ButtonId id, enum e_ButtonType type,
					t_vector2 size, t_vector2 offset);
int				buttons_count(t_button **buttons);
void			free_buttons(t_button **buttons);
int				is_button(t_vector2 v, t_button *button);
int				get_button_color(t_vector2 cpos,
					t_button *button, t_vector2 size);

//utils/buttons/drawer.c
void			draw_button(t_fdf *fdf, t_button *button);
void			draw_buttons(t_fdf *fdf, t_button **buttons);

//utils/buttons/set_data.c
t_button		*set_color(t_button *button, void *default_color,
					void *hover_color, void *pressed_color);
void			set_button_name(t_button *button, char *name, int must_be_free);
t_button		**create_array(t_button *buttons[2], t_button *button);

//utils/controls/controls.c
void			init_controls(t_controls *controls);
t_controls		*get_controls(t_fdf *fdf);
void			add_key(t_controls *controls, enum e_KeyId id,
					int key, enum e_ButtonId button);
void			free_contr(t_controls controls);

//utils/controls/keys.c
int				is_pressed(t_controls controls, enum e_KeyId id);
t_key			*get_key(t_controls controls, enum e_KeyId id);
t_key			*get_key_with_code(t_controls controls, int keycode);
t_key			*get_key_from(t_controls *controls, enum e_ButtonId id);

//utils/controls/update.c
void			change_key(t_fdf *fdf, int keycode);
char			*get_name_for(int key);

//utils/cosmetic/backgrounds/backgrounds1.c
int				rnb(t_vector2 v, int w, int h);
int				diag(t_vector2 v, int w, int h);
int				test(t_vector2 v, int w, int h);
int				gakarbou(t_vector2 v, int w, int h);
int				montain(t_vector2 v, int w, int h);

//utils/cosmetic/backgrounds/backgrounds2.c
int				neon(t_vector2 v, int w, int h);
int				win(t_vector2 v, int w, int h);
int				ft(t_vector2 v, int w, int h);
int				rick(t_vector2 v, int w, int h);
int				larry(t_vector2 v, int w, int h);

//utils/cosmetic/backgrounds/backgrounds3.c
int				hello_kitty(t_vector2 v, int w, int h);

//utils/cosmetic/lines/lines1.c
int				wtop(t_vector3 v, t_vector2 mimay);
int				btob(t_vector3 v, t_vector2 mimay);
int				heat(t_vector3 v);
int				rgb(t_vector3 v, t_vector2 mimay, t_vector3 size);
int				ground(t_vector3 v);

//utils/cosmetic/lines/lines2.c
int				mars(t_vector3 v);
int				btow(t_vector3 v);
int				btoy(t_vector3 v, t_vector2 mimay);
int				sin_col(t_vector3 v);

//utils/navbar/buttons.c
void			add_btn(t_category *category, t_button *button);
void			add_sbtn(t_subcategory *sub, t_button *button);
void			navbutton_click(t_button *button);
void			check_buttons(t_button **buttons, t_vector2 pos);

//utils/navbar/category.c
void			add_category(enum e_CategoryId id, char *title);
t_category		*get_category(enum e_CategoryId id);

//utils/navbar/drawer.c
void			draw_navbar(t_fdf *fdf);

//utils/navbar/navbar.c
int				active_navbar(int v);
t_navbar		*get_navbar(void);
void			add_to_navbar(t_category *category);
void			free_navbar(void);

//utils/navbar/register.c
void			add_title(t_subcategory *sub, char *title,
					int offsetx, int offsety);
t_button		*next_b(t_button *button, char *name, int x, int y);
t_button		*next_bm(t_button *button, char *name, t_vector2 offset);

//utils/navbar/selection.c
void			select_toolbar_button(t_button *button);
void			unselect_others(t_button *button);

//utils/navbar/subcategory.c
int				is_showable(t_subcategory *sub);
void			add_subcategory(t_category *category,
					enum e_SubCategoryId id, int (showable)(void));
t_subcategory	*get_sub(t_category *category, enum e_SubCategoryId id);
void			free_subs(t_subcategory **subs);

//utils/navbar/text.c
void			update_navbar_texts(t_fdf *fdf);

//utils/templates/circle.c
void			draw_circle(t_fdf *fdf, t_button *button);

//utils/templates/cube.c
void			draw_cube(t_fdf *fdf, t_button *button);

//utils/templates/keybox.c
int				keybox_color(t_vector2 v, int w, int h);
int				keybox_color_hover(t_vector2 v, int w, int h, int selected);
int				keybox_color_pressed(t_vector2 v, int w, int h);
void			draw_keybox(t_fdf *fdf, t_button *button);

//utils/templates/square.c
void			draw_square(t_fdf *fdf, t_button *button);

//utils/templates/toggle.c
int				toggle_color(t_vector2 v, int w, int h);
int				toggle_color_hover(t_vector2 v, int w, int h, int selected);
int				toggle_color_pressed(t_vector2 v, int w, int h);
void			draw_toggle(t_fdf *fdf, t_button *button);

//utils/cohen_sutherland_clip.c
int				cohen_sutherland_clip(t_vector2 *v1, t_vector2 *v2);

//utils/color.c
int				get_color(char *el);
void			update_colors(t_fdf *fdf,
					int (color)(t_vector3, t_vector2, t_vector3));

//utils/default_color.c
int				white(void);
int				black(void);
int				dark_gray(void);
int				gray(void);
int				light_gray(void);

//utils/image.c
int				from_img(t_vector2 v, t_img *img, t_vector2 size);

//utils/pixel.c
int				put_pixel(t_fdf *fdf, t_vector2 pos, int color, float alpha);
int				is_outside(t_vector2 v);
t_pixel_data	get_pdata(t_fdf *fdf, t_point p, int mirror);

//utils/resolution.c
int				height(void);
int				width(void);

//utils/updator.c
void			define_fdf(t_fdf *v);
t_fdf			*get_fdf(void);
void			update_keys(t_fdf *fdf);
int				on_update(t_fdf *fdf);

//views/conic.c
int				is_conic(void);
t_pixel_data	conic_data(t_fdf *fdf, t_vector3 v3, int mirror);

//views/isometric.c
int				is_isometric(void);
t_pixel_data	isometric_data(t_fdf *fdf, t_vector3 v3, int mirror);

//views/parallel.c
int				is_parallel(void);
t_pixel_data	parallel_data(t_fdf *fdf, t_vector3 v3, int mirror);

//views/switcher.c
void			switch_view(t_fdf *fdf);

//depth_manager.c
void			init_depth(t_fdf *fdf);
void			clear_depth(t_fdf *fdf);
void			free_depth(t_fdf *fdf);

//destructor.c
void			destruct(t_fdf *fdf);
int				on_close(t_fdf *fdf);
void			free_lines(char ****lines, int y);
void			free_map(t_map *map);

#endif
