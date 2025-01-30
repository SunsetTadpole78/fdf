/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   navbar.c                                           :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lroussel <lroussel@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/27 08:48:43 by lroussel		  #+#	#+#			 */
/*   Updated: 2025/01/30 11:21:25 by lroussel         ###   ########.fr       */
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
	btn = create_button(BGG, CIRCLE, "", size, o);
	btn->selected = 1;
	add_button(bg, btn);
	add_button(bg, set_color(next_b(btn, "", 200, 100), test, rnb, rnb));
	add_button(bg, set_color(next_b(btn, "", 300, 100), gakarbou, rnb2, rnb2));
	add_button(bg, set_color(next_b(btn, "", 400, 100), ver, ver, ver));
	add_button(bg, set_color(next_b(btn, "", 500, 100), hor, hor, hor));
	add_button(bg, set_color(next_b(btn, "", 600, 100), diag, diag, diag));
	add_button(bg, set_color(next_b(btn, "", 700, 100), circ, circ, circ));
	add_button(bg, set_color(next_b(btn, "", 800, 100), spir, spir, spir));
	add_button(bg, set_color(next_b(btn, "", 900, 100), rnb2_m, rnb2_m, rnb2_m));
	add_button(bg, set_color(next_b(btn, "", 1000, 100), diag_m, diag_m, diag_m));
	add_button(bg, set_color(next_b(btn, "", 1100, 100), circ_m, circ_m, circ_m));
	add_button(bg, set_color(next_b(btn, "", 1200, 100), spir_m, spir_m, spir_m));
}

char	*to_chars(char c)
{
	return (ft_strdup(&c));
}

void	register_controls_buttons(t_fdf *fdf)
{
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
	char *name = get_name_for(fdf->controls.up.v);
	btn = create_button(CTRL_UP, KEYBOX, name, size, o);
	free(name);
	set_color(btn, keybox_color, keybox_color_hover, keybox_color_pressed);
	add_button(controls, btn);
	btn = next_bm(btn, get_name_for(fdf->controls.down.v), 200, 100);
	btn->id = CTRL_DOWN;
	add_button(controls, btn);
	btn = next_bm(btn, get_name_for(fdf->controls.left.v), 160, 100);
	btn->id = CTRL_LEFT;
	add_button(controls, btn);
	btn = next_bm(btn, get_name_for(fdf->controls.right.v), 240, 100);
	btn->id = CTRL_RIGHT;
	add_button(controls, btn);
	add_title(controls, "Rotation X:", 440, 100);
	btn = next_bm(btn, get_name_for(fdf->controls.reduce_x.v), 497, 60);
	btn->id = CTRL_REDUCE_X;
	add_button(controls, btn);
	btn = next_bm(btn, get_name_for(fdf->controls.add_x.v), 497, 100);
	btn->id = CTRL_ADD_X;
	add_button(controls, btn);
	add_title(controls, "Rotation Y:", 702, 100);
	btn = next_bm(btn, get_name_for(fdf->controls.reduce_y.v), 759, 60);
	btn->id = CTRL_REDUCE_Y;
	add_button(controls, btn);
	btn = next_bm(btn, get_name_for(fdf->controls.add_y.v), 759, 100);
	btn->id = CTRL_ADD_Y;
	add_button(controls, btn);
	add_title(controls, "Rotation Z:", 962, 100);
	btn = next_bm(btn, get_name_for(fdf->controls.reduce_z.v), 1019, 60);
	btn->id = CTRL_REDUCE_Z;
	add_button(controls, btn);
	btn = next_bm(btn, get_name_for(fdf->controls.add_z.v), 1019, 100);
	btn->id = CTRL_ADD_Z;
	add_button(controls, btn);
	add_title(controls, "Zoom :", 1207, 100);
	btn = next_bm(btn, get_name_for(fdf->controls.zoom.v), 1249, 60);
	btn->id = CTRL_ZOOM;
	add_button(controls, btn);
	btn = next_bm(btn, get_name_for(fdf->controls.unzoom.v), 1249, 100);
	btn->id = CTRL_UNZOOM;
	add_button(controls, btn);
}

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
	register_controls_buttons(fdf);
	register_other_buttons();
}
