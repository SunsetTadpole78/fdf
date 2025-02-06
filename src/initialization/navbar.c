/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   navbar.c                                           :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lroussel <lroussel@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/27 08:48:43 by lroussel		  #+#	#+#			 */
/*   Updated: 2025/02/06 17:28:22 by lroussel         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "fdf.h"

void	add_title(t_category *category, char *title, int offsetx, int offsety)
{
	t_vector2	size;
	t_vector2	offset;

	size.x = 0;
	size.y = 0;
	offset.x = offsetx;
	offset.y = offsety;
	add_button(category, create_button(TIT, TITLE, title, size, offset));
}

void	register_categories(void)
{
	add_category(BG, "Background");
	add_category(LINES, "Lines");
	add_category(CONTROLS, "Controls");
	add_category(OTHER, "Other");
}

t_button	*next_b(t_button *button, char *name, int x, int y)
{
	t_vector2	offset;
	t_button	*btn;

	offset.x = x;
	offset.y = y;
	btn = create_button(button->id, button->type, name, button->size, offset);
	set_color(btn, button->color, button->hover_color, button->pressed_color);
	return (btn);
}

t_button	*next_bm(t_button *button, char *name, int x, int y)
{
	t_vector2	offset;
	t_button	*btn;

	offset.x = x;
	offset.y = y;
	btn = create_button(button->id, button->type, name, button->size, offset);
	free(name);
	set_color(btn, button->color, button->hover_color, button->pressed_color);
	return (btn);
}

void	register_background_buttons(void)
{
	t_category	*bg;
	t_vector2	size;
	t_vector2	o;
	t_button	*btn;

	bg = get_navbar_category(BG);
	size.x = 40;
	size.y = 40;
	o.x = 100;
	o.y = 100;
	btn = create_button(BGG, CIRCLE, "black", size, o);
	btn->selected = 1;
	add_button(bg, btn);
	add_button(bg, set_color(next_b(btn, "rnbw", 200, 100), rnb, rnb, rnb));
	add_button(bg, set_color(next_b(btn, "rnbw2", 300, 100), diag, diag, diag));
	add_button(bg, set_color(next_b(btn, "gakarbou", 400, 100), gakarbou, gakarbou, gakarbou));
	add_button(bg, set_color(next_b(btn, "blue", 500, 100), test, test, test));
	add_button(bg, set_color(next_b(btn, "montain", 600, 100), montain, montain, montain));
	add_button(bg, set_color(next_b(btn, "neon", 700, 100), neon, neon, neon));
	add_button(bg, set_color(next_b(btn, "windows", 800, 100), win, win, win));
	add_button(bg, set_color(next_b(btn, "42", 900, 100), ft, ft, ft));
	add_button(bg, set_color(next_b(btn, "rick roll", 1000, 100), rick, rick, rick));
	add_button(bg, set_color(next_b(btn, "larry", 1100, 100), larry, larry, larry));
	add_button(bg, set_color(next_b(btn, "hello kitty", 1200, 100), hello_kitty, hello_kitty, hello_kitty));
}

void	register_lines_buttons(void)
{
	t_category	*lines;
	t_vector2	size;
	t_vector2	o;
	t_button	*btn;

	lines = get_navbar_category(LINES);
	size.x = 40;
	size.y = 40;
	o.x = 100;
	o.y = 100;
	btn = create_button(LINE, CUBE, "", size, o);
	btn->selected = 1;
	add_button(lines, set_color(btn, white, white, white));
	add_button(lines, set_color(next_b(btn, "", 200, 100), subject, subject, subject));
	add_button(lines, set_color(next_b(btn, "", 300, 100), blue, blue, blue));
	add_button(lines, set_color(next_b(btn, "", 400, 100), relief, relief, relief));
	add_button(lines, set_color(next_b(btn, "", 500, 100), rgb, rgb, rgb));
	add_button(lines, set_color(next_b(btn, "", 600, 100), pays, pays, pays));
	add_button(lines, set_color(next_b(btn, "", 700, 100), mars, mars, mars));
	add_button(lines, set_color(next_b(btn, "", 800, 100), black_and_white, black_and_white, black_and_white));
	add_button(lines, set_color(next_b(btn, "", 900, 100), blue_and_yellow, blue_and_yellow, blue_and_yellow));
	add_button(lines, set_color(next_b(btn, "", 1000, 100), random_c, random_c, random_c));
}

char	*to_chars(char c)
{
	return (ft_strdup(&c));
}

void	register_controls_buttons(t_fdf *fdf)
{(void)fdf;
	t_category      *controls;

	controls = get_navbar_category(CONTROLS);
	add_sub(controls, CONTROLS_ISO, is_isometric);
	/*
	t_category	*controls;
	t_vector2	size;
	t_vector2	o;
	t_button	*btn;

	controls = get_navbar_category(CONTROLS);
	add_title(controls, "Translation:", 100, 100);
	size.x = 40;
	size.y = 40;
	o.x = 200;
	o.y = 60;
	char *name = get_name_for(fdf->isometric.controls.up.v);
	btn = create_button(CTRL_UP, KEYBOX, name, size, o);
	free(name);
	set_color(btn, keybox_color, keybox_color_hover, keybox_color_pressed);
	add_button(controls, btn);
	btn = next_bm(btn, get_name_for(fdf->isometric.controls.down.v), 200, 100);
	btn->id = CTRL_DOWN;
	add_button(controls, btn);
	btn = next_bm(btn, get_name_for(fdf->isometric.controls.left.v), 160, 100);
	btn->id = CTRL_LEFT;
	add_button(controls, btn);
	btn = next_bm(btn, get_name_for(fdf->isometric.controls.right.v), 240, 100);
	btn->id = CTRL_RIGHT;
	add_button(controls, btn);
	add_title(controls, "Rotation X:", 440, 100);
	btn = next_bm(btn, get_name_for(fdf->isometric.controls.reduce_x.v), 497, 60);
	btn->id = CTRL_REDUCE_X;
	add_button(controls, btn);
	btn = next_bm(btn, get_name_for(fdf->isometric.controls.add_x.v), 497, 100);
	btn->id = CTRL_ADD_X;
	add_button(controls, btn);
	add_title(controls, "Rotation Y:", 702, 100);
	btn = next_bm(btn, get_name_for(fdf->isometric.controls.reduce_y.v), 759, 60);
	btn->id = CTRL_REDUCE_Y;
	add_button(controls, btn);
	btn = next_bm(btn, get_name_for(fdf->isometric.controls.add_y.v), 759, 100);
	btn->id = CTRL_ADD_Y;
	add_button(controls, btn);
	add_title(controls, "Rotation Z:", 962, 100);
	btn = next_bm(btn, get_name_for(fdf->isometric.controls.reduce_z.v), 1019, 60);
	btn->id = CTRL_REDUCE_Z;
	add_button(controls, btn);
	btn = next_bm(btn, get_name_for(fdf->isometric.controls.add_z.v), 1019, 100);
	btn->id = CTRL_ADD_Z;
	add_button(controls, btn);
	add_title(controls, "Zoom :", 1207, 100);
	btn = next_bm(btn, get_name_for(fdf->isometric.controls.zoom.v), 1249, 60);
	btn->id = CTRL_ZOOM;
	add_button(controls, btn);
	btn = next_bm(btn, get_name_for(fdf->isometric.controls.unzoom.v), 1249, 100);
	btn->id = CTRL_UNZOOM;
	add_button(controls, btn);
*/}

void	register_other_buttons(void)
{
	t_category	*other;
	t_vector2	size;
	t_vector2	o;
	t_button	*btn;

	other = get_navbar_category(OTHER);
	size.x = 30;
	size.y = 30;
	o.x = 100;
	o.y = 85;
	btn = create_button(AXIS, TOGGLE, "Axes", size, o);
	set_color(btn, toggle_color, toggle_color_hover, toggle_color_pressed);
	btn->selected = 1;
	add_button(other, btn);
	btn = next_b(btn, "Mirror", 200, 85);
	btn->id = MIRROR;
	btn->selected = 0;
	add_button(other, btn);
}

void	init_navbar(t_fdf *fdf)
{
	active_navbar(1);
	mlx_hook(fdf->window, 6, 1L << 6, on_move, get_navbar());
	mlx_hook(fdf->window, 4, 1L << 2, on_click, fdf);
	register_categories();
	register_background_buttons();
	register_lines_buttons();
	register_controls_buttons(fdf);
	register_other_buttons();
}
