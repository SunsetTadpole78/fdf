/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   navbar.c                                           :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lroussel <lroussel@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/27 08:48:43 by lroussel		  #+#	#+#			 */
/*   Updated: 2025/02/07 10:01:53 by lroussel         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "fdf.h"

void	add_title(t_subcategory *sub, char *title, int offsetx, int offsety)
{
	t_vector2	size;
	t_vector2	offset;

	size.x = 0.0f;
	size.y = 0.0f;
	offset.x = offsetx;
	offset.y = offsety;
	add_subbutton(sub, create_button(TIT, TITLE, title, size, offset));
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
	size.x = 40.0f;
	size.y = 40.0f;
	o.x = 100.0f;
	o.y = 100.0f;
	btn = create_button(BGG, CIRCLE, "black", size, o);
	btn->selected = 1;
	add_button(bg, btn);
	add_button(bg, set_color(next_b(btn, "", 200.0f, 100.0f), rnb, rnb, rnb));
	add_button(bg, set_color(next_b(btn, "", 300.0f, 100.0f), diag, diag, diag));
	add_button(bg, set_color(next_b(btn, "", 400.0f, 100.0f), gakarbou, gakarbou, gakarbou));
	add_button(bg, set_color(next_b(btn, "", 500.0f, 100.0f), test, test, test));
	add_button(bg, set_color(next_b(btn, "", 600.0f, 100.0f), montain, montain, montain));
	add_button(bg, set_color(next_b(btn, "", 700.0f, 100.0f), neon, neon, neon));
	add_button(bg, set_color(next_b(btn, "", 800.0f, 100.0f), win, win, win));
	add_button(bg, set_color(next_b(btn, "", 900.0f, 100.0f), ft, ft, ft));
	add_button(bg, set_color(next_b(btn, "", 1000.0f, 100.0f), rick, rick, rick));
	add_button(bg, set_color(next_b(btn, "", 1100.0f, 100.0f), larry, larry, larry));
	add_button(bg, set_color(next_b(btn, "", 1200.0f, 100.0f), hello_kitty, hello_kitty, hello_kitty));
}

void	register_lines_buttons(void)
{
	t_category	*lines;
	t_vector2	size;
	t_vector2	o;
	t_button	*btn;

	lines = get_navbar_category(LINES);
	size.x = 40.0f;
	size.y = 40.0f;
	o.x = 100.0f;
	o.y = 100.0f;
	btn = create_button(LINE, CUBE, "", size, o);
	btn->selected = 1;
	add_button(lines, set_color(btn, white, white, white));
	add_button(lines, set_color(next_b(btn, "", 200.0f, 100.0f), subject, subject, subject));
	add_button(lines, set_color(next_b(btn, "", 300.0f, 100.0f), blue, blue, blue));
	add_button(lines, set_color(next_b(btn, "", 400.0f, 100.0f), relief, relief, relief));
	add_button(lines, set_color(next_b(btn, "", 500.0f, 100.0f), rgb, rgb, rgb));
	add_button(lines, set_color(next_b(btn, "", 600.0f, 100.0f), pays, pays, pays));
	add_button(lines, set_color(next_b(btn, "", 700.0f, 100.0f), mars, mars, mars));
	add_button(lines, set_color(next_b(btn, "", 800.0f, 100.0f), black_and_white, black_and_white, black_and_white));
	add_button(lines, set_color(next_b(btn, "", 900.0f, 100.0f), blue_and_yellow, blue_and_yellow, blue_and_yellow));
	add_button(lines, set_color(next_b(btn, "", 1000.0f, 100.0f), random_c, random_c, random_c));
}

char	*to_chars(char c)
{
	return (ft_strdup(&c));
}

void	register_controls_buttons(t_fdf *fdf)
{(void)fdf;
	t_category      *controls;
	t_subcategory	*iso;
	t_vector2	size;
	t_vector2	o;
	t_button	*btn;
	t_c	ic;

	controls = get_navbar_category(CONTROLS);
	add_sub(controls, CONTROLS_ISO, is_isometric);
	iso = get_sub(controls, CONTROLS_ISO);
	controls = get_navbar_category(CONTROLS);
	ic = fdf->isometric.controls;
	add_title(iso, "Translation:", 100.0f, 100.0f);
	size.x = 40.0f;
	size.y = 40.0f;
	o.x = 200.0f;
	o.y = 60.0f;
	char *name = get_name_for(get_key(ic, I_UP)->v);
	btn = create_button(CTRL_UP, KEYBOX, name, size, o);
	free(name);
	set_color(btn, keybox_color, keybox_color_hover, keybox_color_pressed);
	add_subbutton(iso, btn);
	btn = next_bm(btn, get_name_for(get_key(ic, I_DOWN)->v), 200.0f, 100.0f);
	btn->id = CTRL_DOWN;
	add_subbutton(iso, btn);
	btn = next_bm(btn, get_name_for(get_key(ic, I_LEFT)->v), 160.0f, 100.0f);
	btn->id = CTRL_LEFT;
	add_subbutton(iso, btn);
	btn = next_bm(btn, get_name_for(get_key(ic, I_RIGHT)->v), 240.0f, 100.0f);
	btn->id = CTRL_RIGHT;
	add_subbutton(iso, btn);
	add_title(iso, "Rotation X:", 440.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(ic, I_REDUCE_X)->v), 497.0f, 60.0f);
	btn->id = CTRL_REDUCE_X;
	add_subbutton(iso, btn);
	btn = next_bm(btn, get_name_for(get_key(ic, I_ADD_X)->v), 497.0f, 100.0f);
	btn->id = CTRL_ADD_X;
	add_subbutton(iso, btn);
	add_title(iso, "Rotation Y:", 702.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(ic, I_REDUCE_Y)->v), 759.0f, 60.0f);
	btn->id = CTRL_REDUCE_Y;
	add_subbutton(iso, btn);
	btn = next_bm(btn, get_name_for(get_key(ic, I_ADD_Y)->v), 759.0f, 100.0f);
	btn->id = CTRL_ADD_Y;
	add_subbutton(iso, btn);
	add_title(iso, "Rotation Z:", 962.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(ic, I_REDUCE_Z)->v), 1019.0f, 60.0f);
	btn->id = CTRL_REDUCE_Z;
	add_subbutton(iso, btn);
	btn = next_bm(btn, get_name_for(get_key(ic, I_ADD_Z)->v), 1019.0f, 100.0f);
	btn->id = CTRL_ADD_Z;
	add_subbutton(iso, btn);
	add_title(iso, "Zoom :", 1207.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(ic, I_ZOOM)->v), 1249.0f, 60.0f);
	btn->id = CTRL_ZOOM;
	add_subbutton(iso, btn);
	btn = next_bm(btn, get_name_for(get_key(ic, I_UNZOOM)->v), 1249.0f, 100.0f);
	btn->id = CTRL_UNZOOM;
	add_subbutton(iso, btn);
}

void	register_other_buttons(void)
{
	t_category	*other;
	t_vector2	size;
	t_vector2	o;
	t_button	*btn;

	other = get_navbar_category(OTHER);
	size.x = 30.0f;
	size.y = 30.0f;
	o.x = 100.0f;
	o.y = 85.0f;
	btn = create_button(AXIS, TOGGLE, "Axes", size, o);
	set_color(btn, toggle_color, toggle_color_hover, toggle_color_pressed);
	btn->selected = 1;
	add_button(other, btn);
	btn = next_b(btn, "Mirror", 200.0f, 85.0f);
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
