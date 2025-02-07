/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   navbar.c                                           :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lroussel <lroussel@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/27 08:48:43 by lroussel		  #+#	#+#			 */
/*   Updated: 2025/02/07 10:36:53 by lroussel         ###   ########.fr       */
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
	btn = create_button(BGG, CIRCLE, "", size, o);
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
{
	t_category      *controls;
	t_subcategory	*iso;
	t_vector2	size;
	t_vector2	o;
	t_button	*btn;
	t_c	ic;

	controls = get_navbar_category(CONTROLS);
	add_sub(controls, CONTROLS_ISO, is_isometric);
	iso = get_sub(controls, CONTROLS_ISO);
	ic = fdf->isometric.controls;
	add_title(iso, "Translation:", 100.0f, 100.0f);
	size.x = 40.0f;
	size.y = 40.0f;
	o.x = 200.0f;
	o.y = 60.0f;
	char *name = get_name_for(get_key(ic, I_UP)->v);
	btn = create_button(CTRLI_UP, KEYBOX, name, size, o);
	free(name);
	set_color(btn, keybox_color, keybox_color_hover, keybox_color_pressed);
	add_subbutton(iso, btn);
	btn = next_bm(btn, get_name_for(get_key(ic, I_DOWN)->v), 200.0f, 100.0f);
	btn->id = CTRLI_DOWN;
	add_subbutton(iso, btn);
	btn = next_bm(btn, get_name_for(get_key(ic, I_LEFT)->v), 160.0f, 100.0f);
	btn->id = CTRLI_LEFT;
	add_subbutton(iso, btn);
	btn = next_bm(btn, get_name_for(get_key(ic, I_RIGHT)->v), 240.0f, 100.0f);
	btn->id = CTRLI_RIGHT;
	add_subbutton(iso, btn);
	add_title(iso, "X Rotation:", 440.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(ic, I_RX1)->v), 497.0f, 60.0f);
	btn->id = CTRLI_RX1;
	add_subbutton(iso, btn);
	btn = next_bm(btn, get_name_for(get_key(ic, I_RX2)->v), 497.0f, 100.0f);
	btn->id = CTRLI_RX2;
	add_subbutton(iso, btn);
	add_title(iso, "Y Rotation:", 697.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(ic, I_RY1)->v), 754.0f, 60.0f);
	btn->id = CTRLI_RY1;
	add_subbutton(iso, btn);
	btn = next_bm(btn, get_name_for(get_key(ic, I_RY2)->v), 754.0f, 100.0f);
	btn->id = CTRLI_RY2;
	add_subbutton(iso, btn);
	add_title(iso, "Z Rotation:", 954.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(ic, I_RZ1)->v), 1011.0f, 60.0f);
	btn->id = CTRLI_RZ2;
	add_subbutton(iso, btn);
	btn = next_bm(btn, get_name_for(get_key(ic, I_RZ2)->v), 1011.0f, 100.0f);
	btn->id = CTRLI_RZ2;
	add_subbutton(iso, btn);
	add_title(iso, "Zoom :", 1196.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(ic, I_ZOOM)->v), 1238.0f, 60.0f);
	btn->id = CTRLI_ZOOM;
	add_subbutton(iso, btn);
	btn = next_bm(btn, get_name_for(get_key(ic, I_UNZOOM)->v), 1238.0f, 100.0f);
	btn->id = CTRLI_UNZOOM;
	add_subbutton(iso, btn);
	add_title(iso, "Y Amplifier :", 1444.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(ic, I_YA1)->v), 1507.0f, 60.0f);
	btn->id = CTRLI_YA1;
	add_subbutton(iso, btn);
	btn = next_bm(btn, get_name_for(get_key(ic, I_YA2)->v), 1507.0f, 100.0f);
	btn->id = CTRLI_YA2;
	add_subbutton(iso, btn);
}

void	register_conic_controls_buttons(t_fdf *fdf)
{
	t_category      *controls;
	t_subcategory	*conic;
	t_vector2	size;
	t_vector2	o;
	t_button	*btn;
	t_c	cc;

	controls = get_navbar_category(CONTROLS);
	add_sub(controls, CONTROLS_CONIC, is_conic);
	conic = get_sub(controls, CONTROLS_CONIC);
	cc = fdf->conic.controls;
	add_title(conic, "Movements:", 94.0f, 100.0f);
	size.x = 40.0f;
	size.y = 40.0f;
	o.x = 188.0f;
	o.y = 60.0f;
	char *name = get_name_for(get_key(cc, C_FRONT)->v);
	btn = create_button(CTRLC_FRONT, KEYBOX, name, size, o);
	free(name);
	set_color(btn, keybox_color, keybox_color_hover, keybox_color_pressed);
	add_subbutton(conic, btn);
	btn = next_bm(btn, get_name_for(get_key(cc, C_BEHIND)->v), 188.0f, 100.0f);
	btn->id = CTRLC_BEHIND;
	add_subbutton(conic, btn);
	btn = next_bm(btn, get_name_for(get_key(cc, C_LEFT)->v), 148.0f, 100.0f);
	btn->id = CTRLC_LEFT;
	add_subbutton(conic, btn);
	btn = next_bm(btn, get_name_for(get_key(cc, C_RIGHT)->v), 228.0f, 100.0f);
	btn->id = CTRLC_RIGHT;
	add_subbutton(conic, btn);
	add_title(conic, "Up / Down:", 425.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(cc, C_UP)->v), 479.0f, 60.0f);
	btn->id = CTRLC_UP;
	add_subbutton(conic, btn);
	btn = next_bm(btn, get_name_for(get_key(cc, C_DOWN)->v), 479.0f, 100.0f);
	btn->id = CTRLC_DOWN;
	add_subbutton(conic, btn);
	
	add_title(conic, "X Rotation:", 679.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(cc, C_RX1)->v), 736.0f, 60.0f);
	btn->id = CTRLC_RX1;
	add_subbutton(conic, btn);
	btn = next_bm(btn, get_name_for(get_key(cc, C_RX2)->v), 736.0f, 100.0f);
	btn->id = CTRLC_RX2;
	add_subbutton(conic, btn);

	add_title(conic, "Y Rotation:", 936.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(cc, C_RY1)->v), 993.0f, 60.0f);
	btn->id = CTRLC_RY1;
	add_subbutton(conic, btn);
	btn = next_bm(btn, get_name_for(get_key(cc, C_RY2)->v), 993.0f, 100.0f);
	btn->id = CTRLC_RY2;
	add_subbutton(conic, btn);
	add_title(conic, "Z Rotation:", 1193.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(cc, C_RZ1)->v), 1250.0f, 60.0f);
	btn->id = CTRLC_RZ1;
	add_subbutton(conic, btn);
	btn = next_bm(btn, get_name_for(get_key(cc, C_RZ2)->v), 1250.0f, 100.0f);
	btn->id = CTRLC_RZ2;
	add_subbutton(conic, btn);
	add_title(conic, "FOV :", 1432.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(cc, C_FOV1)->v), 1471.0f, 60.0f);
	btn->id = CTRLC_FOV1;
	add_subbutton(conic, btn);
	btn = next_bm(btn, get_name_for(get_key(cc, C_FOV2)->v), 1471.0f, 100.0f);
	btn->id = CTRLC_FOV2;
	add_subbutton(conic, btn);
	add_title(conic, "Y Amplifier :", 1677.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(cc, C_YA1)->v), 1740.0f, 60.0f);
	btn->id = CTRLC_YA1;
	add_subbutton(conic, btn);
	btn = next_bm(btn, get_name_for(get_key(cc, C_YA2)->v), 1740.0f, 100.0f);
	btn->id = CTRLC_YA2;
	add_subbutton(conic, btn);
}

void	register_parallel_controls_buttons(t_fdf *fdf)
{
	t_category      *controls;
	t_subcategory	*parallel;
	t_vector2	size;
	t_vector2	o;
	t_button	*btn;
	t_c	pc;

	controls = get_navbar_category(CONTROLS);
	add_sub(controls, CONTROLS_PARALLEL, is_parallel);
	parallel = get_sub(controls, CONTROLS_PARALLEL);
	pc = fdf->parallel.controls;
	add_title(parallel, "Translation:", 100.0f, 100.0f);
	size.x = 40.0f;
	size.y = 40.0f;
	o.x = 200.0f;
	o.y = 60.0f;
	char *name = get_name_for(get_key(pc, P_UP)->v);
	btn = create_button(CTRLP_UP, KEYBOX, name, size, o);
	free(name);
	set_color(btn, keybox_color, keybox_color_hover, keybox_color_pressed);
	add_subbutton(parallel, btn);
	btn = next_bm(btn, get_name_for(get_key(pc, P_DOWN)->v), 200.0f, 100.0f);
	btn->id = CTRLP_DOWN;
	add_subbutton(parallel, btn);
	btn = next_bm(btn, get_name_for(get_key(pc, P_LEFT)->v), 160.0f, 100.0f);
	btn->id = CTRLP_LEFT;
	add_subbutton(parallel, btn);
	btn = next_bm(btn, get_name_for(get_key(pc, P_RIGHT)->v), 240.0f, 100.0f);
	btn->id = CTRLP_RIGHT;
	add_subbutton(parallel, btn);
	add_title(parallel, "X Rotation:", 440.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(pc, P_RX1)->v), 497.0f, 60.0f);
	btn->id = CTRLP_RX1;
	add_subbutton(parallel, btn);
	btn = next_bm(btn, get_name_for(get_key(pc, P_RX2)->v), 497.0f, 100.0f);
	btn->id = CTRLP_RX2;
	add_subbutton(parallel, btn);
	add_title(parallel, "Y Rotation:", 697.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(pc, P_RY1)->v), 754.0f, 60.0f);
	btn->id = CTRLP_RY1;
	add_subbutton(parallel, btn);
	btn = next_bm(btn, get_name_for(get_key(pc, P_RY2)->v), 754.0f, 100.0f);
	btn->id = CTRLP_RY2;
	add_subbutton(parallel, btn);
	add_title(parallel, "Zoom :", 939.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(pc, P_ZOOM)->v), 981.0f, 60.0f);
	btn->id = CTRLP_ZOOM;
	add_subbutton(parallel, btn);
	btn = next_bm(btn, get_name_for(get_key(pc, P_UNZOOM)->v), 981.0f, 100.0f);
	btn->id = CTRLP_UNZOOM;
	add_subbutton(parallel, btn);
	add_title(parallel, "Y Amplifier :", 1187.0f, 100.0f);
	btn = next_bm(btn, get_name_for(get_key(pc, P_YA1)->v), 1250.0f, 60.0f);
	btn->id = CTRLP_YA1;
	add_subbutton(parallel, btn);
	btn = next_bm(btn, get_name_for(get_key(pc, P_YA2)->v), 1250.0f, 100.0f);
	btn->id = CTRLP_YA2;
	add_subbutton(parallel, btn);
}

void	register_other_buttons(void)
{
	t_category	*other;
	t_subcategory	*iso;
	t_subcategory	*parallel;
	t_vector2	size;
	t_vector2	o;
	t_button	*btn;

	other = get_navbar_category(OTHER);
	add_sub(other, OTHER_ISO, is_isometric);
	add_sub(other, OTHER_PARALLEL, is_parallel);
	iso = get_sub(other, OTHER_ISO);
	parallel = get_sub(other, OTHER_PARALLEL);
	size.x = 30.0f;
	size.y = 30.0f;
	o.x = 100.0f;
	o.y = 85.0f;
	btn = create_button(I_AXIS, TOGGLE, "Axes", size, o);
	set_color(btn, toggle_color, toggle_color_hover, toggle_color_pressed);
	btn->selected = 1;
	add_subbutton(iso, btn);
	btn = create_button(P_AXIS, TOGGLE, "Axes", size, o);
	set_color(btn, toggle_color, toggle_color_hover, toggle_color_pressed);
	btn->selected = 1;
	add_subbutton(parallel, btn);
	btn = next_b(btn, "Mirror", 200.0f, 85.0f);
	btn->id = MIRROR;
	add_subbutton(iso, btn);
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
	register_conic_controls_buttons(fdf);
	register_parallel_controls_buttons(fdf);
	register_other_buttons();
}
