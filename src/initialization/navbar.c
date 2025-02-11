/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   navbar.c                                           :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lroussel <lroussel@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/27 08:48:43 by lroussel		  #+#	#+#			 */
/*   Updated: 2025/02/11 16:35:22 by lroussel         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "fdf.h"

void	add_title(t_subcategory *sub, char *title, int offsetx, int offsety)
{
	t_vector2	size;
	t_vector2	offset;
	t_button	*btn;

	size.x = 0;
	size.y = 0;
	offset.x = offsetx;
	offset.y = offsety;
	btn = create_button(TIT, TITLE, size, offset);
	set_button_name(btn, title, 0);
	add_sb(sub, btn);
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
	btn = create_button(button->id, button->type, button->size, offset);
	set_button_name(btn, name, 0);
	set_color(btn, button->color, button->hover_color, button->pressed_color);
	return (btn);
}

t_button	*next_bm(t_button *button, char *name, t_vector2 offset)
{
	t_button	*btn;

	btn = create_button(button->id, button->type, button->size, offset);
	set_button_name(btn, name, 0);
	free(name);
	set_color(btn, button->color, button->hover_color, button->pressed_color);
	return (btn);
}

t_button	*bg_btn(t_vector2 offset, void *color, int select)
{
	static t_button	*btn = NULL;
	t_vector2		size;

	size.x = 40;
	size.y = 40;
	if (!btn)
		btn = create_button(BGG, CIRCLE, size, offset);
	else
		btn = next_b(btn, "", offset.x, offset.y);
	set_color(btn, color, color, color);
	btn->selected = select;
	return (btn);
}

t_button	*line_btn(t_vector2 offset, void *color)
{
	static t_button	*btn = NULL;
	t_vector2		size;

	size.x = 40;
	size.y = 40;
	if (!btn)
		btn = create_button(LINE, CUBE, size, offset);
	else
		btn = next_b(btn, "", offset.x, offset.y);
	set_color(btn, color, color, color);
	return (btn);
}

void	register_background_buttons(void)
{
	t_category	*bg;

	bg = get_navbar_category(BG);
	add_b(bg, bg_btn((t_vector2){100, 100}, black, 1));
	add_b(bg, bg_btn((t_vector2){200, 100}, rnb, 0));
	add_b(bg, bg_btn((t_vector2){300, 100}, diag, 0));
	add_b(bg, bg_btn((t_vector2){400, 100}, gakarbou, 0));
	add_b(bg, bg_btn((t_vector2){500, 100}, test, 0));
	add_b(bg, bg_btn((t_vector2){600, 100}, montain, 0));
	add_b(bg, bg_btn((t_vector2){700, 100}, neon, 0));
	add_b(bg, bg_btn((t_vector2){800, 100}, win, 0));
	add_b(bg, bg_btn((t_vector2){900, 100}, ft, 0));
	add_b(bg, bg_btn((t_vector2){1000, 100}, rick, 0));
	add_b(bg, bg_btn((t_vector2){1100, 100}, larry, 0));
	add_b(bg, bg_btn((t_vector2){1200, 100}, hello_kitty, 0));
}

void	register_lines_buttons(void)
{
	t_category	*lines;

	lines = get_navbar_category(LINES);
	add_b(lines, line_btn((t_vector2){100, 100}, white));
	add_b(lines, line_btn((t_vector2){200, 100}, subject));
	add_b(lines, line_btn((t_vector2){300, 100}, blue));
	add_b(lines, line_btn((t_vector2){400, 100}, relief));
	add_b(lines, line_btn((t_vector2){500, 100}, rgb));
	add_b(lines, line_btn((t_vector2){600, 100}, pays));
	add_b(lines, line_btn((t_vector2){700, 100}, mars));
	add_b(lines, line_btn((t_vector2){800, 100}, black_and_white));
	add_b(lines, line_btn((t_vector2){900, 100}, blue_and_yellow));
	add_b(lines, line_btn((t_vector2){1000, 100}, random_c));
}

char	*to_chars(char c)
{
	return (ft_strdup(&c));
}

t_button	*ctrl_btn(enum e_ButtonId id, t_c c, enum e_KeyId key,
	t_vector2 offset)
{
	static t_button	*btn = NULL;
	t_vector2		size;

	size.x = 40;
	size.y = 40;
	if (!btn)
	{
		btn = create_button(id, KEYBOX, size, offset);
		set_button_name(btn, get_name_for(get_key(c, key)->v), 1);
		set_color(btn, keybox_color, keybox_color_hover, keybox_color_pressed);
	}
	else
		btn = next_bm(btn, get_name_for(get_key(c, key)->v), offset);
	btn->id = id;
	return (btn);
}

void	register_iso_controls_buttons(t_subcategory *c, t_c ic)
{
	add_title(c, "Translation:", 100, 100);
	add_sb(c, ctrl_btn(CTRLI_UP, ic, I_UP, (t_vector2){200, 60}));
	add_sb(c, ctrl_btn(CTRLI_DOWN, ic, I_DOWN, (t_vector2){200, 100}));
	add_sb(c, ctrl_btn(CTRLI_LEFT, ic, I_LEFT, (t_vector2){160, 100}));
	add_sb(c, ctrl_btn(CTRLI_RIGHT, ic, I_RIGHT, (t_vector2){240, 100}));
	add_title(c, "X Rotation:", 440, 100);
	add_sb(c, ctrl_btn(CTRLI_RX1, ic, I_RX1, (t_vector2){497, 60}));
	add_sb(c, ctrl_btn(CTRLI_RX2, ic, I_RX2, (t_vector2){497, 100}));
	add_title(c, "Y Rotation:", 697, 100);
	add_sb(c, ctrl_btn(CTRLI_RY1, ic, I_RY1, (t_vector2){754, 60}));
	add_sb(c, ctrl_btn(CTRLI_RY2, ic, I_RY2, (t_vector2){754, 100}));
	add_title(c, "Z Rotation:", 954, 100);
	add_sb(c, ctrl_btn(CTRLI_RZ1, ic, I_RZ1, (t_vector2){1011, 60}));
	add_sb(c, ctrl_btn(CTRLI_RZ2, ic, I_RZ2, (t_vector2){1011, 100}));
	add_title(c, "Zoom :", 1196, 100);
	add_sb(c, ctrl_btn(CTRLI_ZOOM, ic, I_ZOOM, (t_vector2){1238, 60}));
	add_sb(c, ctrl_btn(CTRLI_UNZOOM, ic, I_UNZOOM, (t_vector2){1238, 100}));
	add_title(c, "Y Amplifier :", 1444, 100);
	add_sb(c, ctrl_btn(CTRLI_YA1, ic, I_YA1, (t_vector2){1507, 60}));
	add_sb(c, ctrl_btn(CTRLI_YA2, ic, I_YA2, (t_vector2){1507, 100}));
}

t_subcategory	*register_sub_controls(enum e_SubCategoryId id, void *fn)
{
	t_category	*cat;

	cat = get_navbar_category(CONTROLS);
	add_subcategory(cat, id, fn);
	return (get_sub(cat, id));
}

void	register_conic_controls_buttons(t_subcategory *c, t_c cc)
{
	add_title(c, "Movements:", 94, 100);
	add_sb(c, ctrl_btn(CTRLC_FRONT, cc, C_FRONT, (t_vector2){188, 60}));
	add_sb(c, ctrl_btn(CTRLC_BEHIND, cc, C_BEHIND, (t_vector2){188, 100}));
	add_sb(c, ctrl_btn(CTRLC_LEFT, cc, C_LEFT, (t_vector2){148, 100}));
	add_sb(c, ctrl_btn(CTRLC_RIGHT, cc, C_RIGHT, (t_vector2){228, 100}));
	add_title(c, "Up / Down:", 425, 100);
	add_sb(c, ctrl_btn(CTRLC_UP, cc, C_UP, (t_vector2){479, 60}));
	add_sb(c, ctrl_btn(CTRLC_DOWN, cc, C_DOWN, (t_vector2){479, 100}));
	add_title(c, "X Rotation:", 679, 100);
	add_sb(c, ctrl_btn(CTRLC_RX1, cc, C_RX1, (t_vector2){736, 60}));
	add_sb(c, ctrl_btn(CTRLC_RX2, cc, C_RX2, (t_vector2){736, 100}));
	add_title(c, "Y Rotation:", 936, 100);
	add_sb(c, ctrl_btn(CTRLC_RY1, cc, C_RY1, (t_vector2){993, 60}));
	add_sb(c, ctrl_btn(CTRLC_RY2, cc, C_RY2, (t_vector2){993, 100}));
	add_title(c, "Z Rotation:", 1193, 100);
	add_sb(c, ctrl_btn(CTRLC_RZ1, cc, C_RZ1, (t_vector2){1250, 60}));
	add_sb(c, ctrl_btn(CTRLC_RZ2, cc, C_RZ2, (t_vector2){1250, 100}));
	add_title(c, "FOV :", 1432, 100);
	add_sb(c, ctrl_btn(CTRLC_FOV1, cc, C_FOV1, (t_vector2){1471, 60}));
	add_sb(c, ctrl_btn(CTRLC_FOV2, cc, C_FOV2, (t_vector2){1471, 100}));
	add_title(c, "Y Amplifier :", 1677, 100);
	add_sb(c, ctrl_btn(CTRLC_YA1, cc, C_YA1, (t_vector2){1740, 60}));
	add_sb(c, ctrl_btn(CTRLC_YA2, cc, C_YA2, (t_vector2){1740, 100}));
}

void	register_parallel_controls_buttons(t_subcategory *c, t_c pc)
{
	add_title(c, "Translation:", 100, 100);
	add_sb(c, ctrl_btn(CTRLP_UP, pc, P_UP, (t_vector2){200, 60}));
	add_sb(c, ctrl_btn(CTRLP_DOWN, pc, P_DOWN, (t_vector2){200, 100}));
	add_sb(c, ctrl_btn(CTRLP_LEFT, pc, P_LEFT, (t_vector2){160, 100}));
	add_sb(c, ctrl_btn(CTRLP_RIGHT, pc, P_RIGHT, (t_vector2){240, 100}));
	add_title(c, "X Rotation:", 440, 100);
	add_sb(c, ctrl_btn(CTRLP_RX1, pc, P_RX1, (t_vector2){497, 60}));
	add_sb(c, ctrl_btn(CTRLP_RX2, pc, P_RX2, (t_vector2){497, 100}));
	add_title(c, "Y Rotation:", 697, 100);
	add_sb(c, ctrl_btn(CTRLP_RY1, pc, P_RY1, (t_vector2){754, 60}));
	add_sb(c, ctrl_btn(CTRLP_RY2, pc, P_RY2, (t_vector2){754, 100}));
	add_title(c, "Zoom :", 939, 100);
	add_sb(c, ctrl_btn(CTRLP_ZOOM, pc, P_ZOOM, (t_vector2){981, 60}));
	add_sb(c, ctrl_btn(CTRLP_UNZOOM, pc, P_UNZOOM, (t_vector2){981, 100}));
	add_title(c, "Y Amplifier :", 1187, 100);
	add_sb(c, ctrl_btn(CTRLP_YA1, pc, P_YA1, (t_vector2){1250, 60}));
	add_sb(c, ctrl_btn(CTRLP_YA2, pc, P_YA2, (t_vector2){1250, 100}));
}

void	register_iso_other_buttons(void)
{
	t_category		*other;
	t_subcategory	*iso;
	t_vector2		size;
	t_vector2		o;
	t_button		*btn;

	other = get_navbar_category(OTHER);
	add_subcategory(other, OTHER_ISO, is_isometric);
	iso = get_sub(other, OTHER_ISO);
	size.x = 30;
	size.y = 30;
	o.x = 100;
	o.y = 85;
	btn = create_button(I_AXIS, TOGGLE, size, o);
	set_button_name(btn, "Axes", 0);
	set_color(btn, toggle_color, toggle_color_hover, toggle_color_pressed);
	btn->selected = 1;
	add_sb(iso, btn);
	btn = next_b(btn, "Mirror", 200, 85);
	btn->id = MIRROR;
	add_sb(iso, btn);
}

void	register_parallel_other_buttons(void)
{
	t_category		*other;
	t_subcategory	*parallel;
	t_vector2		size;
	t_vector2		o;
	t_button		*btn;

	other = get_navbar_category(OTHER);
	add_subcategory(other, OTHER_PARALLEL, is_parallel);
	parallel = get_sub(other, OTHER_PARALLEL);
	size.x = 30;
	size.y = 30;
	o.x = 100;
	o.y = 85;
	btn = create_button(P_AXIS, TOGGLE, size, o);
	set_button_name(btn, "Axes", 0);
	set_color(btn, toggle_color, toggle_color_hover, toggle_color_pressed);
	btn->selected = 1;
	add_sb(parallel, btn);
}

void	init_navbar(t_fdf *fdf)
{
	active_navbar(1);
	register_categories();
	register_background_buttons();
	register_lines_buttons();
	register_iso_controls_buttons(
		register_sub_controls(CONTROLS_ISO, is_isometric),
		fdf->isometric.controls);
	register_conic_controls_buttons(
		register_sub_controls(CONTROLS_CONIC, is_conic),
		fdf->conic.controls);
	register_parallel_controls_buttons(
		register_sub_controls(CONTROLS_PARALLEL, is_parallel),
		fdf->parallel.controls);
	register_iso_other_buttons();
	register_parallel_other_buttons();
}
