/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cosmetic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:14:09 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 18:14:10 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_button	*bg_btn(t_vector2 offset, void *color, int select)
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

static t_button	*line_btn(t_vector2 offset, void *color)
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

	bg = get_category(BG);
	add_btn(bg, bg_btn((t_vector2){100, 100}, black, 1));
	add_btn(bg, bg_btn((t_vector2){200, 100}, rnb, 0));
	add_btn(bg, bg_btn((t_vector2){300, 100}, diag, 0));
	add_btn(bg, bg_btn((t_vector2){400, 100}, gakarbou, 0));
	add_btn(bg, bg_btn((t_vector2){500, 100}, test, 0));
	add_btn(bg, bg_btn((t_vector2){600, 100}, montain, 0));
	add_btn(bg, bg_btn((t_vector2){700, 100}, neon, 0));
	add_btn(bg, bg_btn((t_vector2){800, 100}, win, 0));
	add_btn(bg, bg_btn((t_vector2){900, 100}, ft, 0));
	add_btn(bg, bg_btn((t_vector2){1000, 100}, rick, 0));
	add_btn(bg, bg_btn((t_vector2){1100, 100}, larry, 0));
	add_btn(bg, bg_btn((t_vector2){1200, 100}, hello_kitty, 0));
}

void	register_lines_buttons(void)
{
	t_category	*lines;

	lines = get_category(LINES);
	add_btn(lines, line_btn((t_vector2){100, 100}, white));
	add_btn(lines, line_btn((t_vector2){200, 100}, wtop));
	add_btn(lines, line_btn((t_vector2){300, 100}, btob));
	add_btn(lines, line_btn((t_vector2){400, 100}, heat));
	add_btn(lines, line_btn((t_vector2){500, 100}, rgb));
	add_btn(lines, line_btn((t_vector2){600, 100}, ground));
	add_btn(lines, line_btn((t_vector2){700, 100}, mars));
	add_btn(lines, line_btn((t_vector2){800, 100}, btow));
	add_btn(lines, line_btn((t_vector2){900, 100}, btoy));
	add_btn(lines, line_btn((t_vector2){1000, 100}, sin_col));
}
