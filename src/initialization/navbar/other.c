/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:14:03 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 23:07:52 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	register_iso_other_buttons(void)
{
	t_category		*other;
	t_subcategory	*iso;
	t_vector2		size;
	t_vector2		o;
	t_button		*btn;

	other = get_category(OTHER);
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
	add_sbtn(iso, btn);
	btn = next_b(btn, "Mirror", 287, 85);
	btn->id = I_MIRROR;
	add_sbtn(iso, btn);
	btn = next_b(btn, "Only Points", 486, 85);
	btn->id = I_ONLY_POINTS;
	add_sbtn(iso, btn);
}

void	register_conic_other_buttons(void)
{
	t_category		*other;
	t_subcategory	*conic;
	t_vector2		size;
	t_vector2		o;
	t_button		*btn;

	other = get_category(OTHER);
	add_subcategory(other, OTHER_CONIC, is_conic);
	conic = get_sub(other, OTHER_CONIC);
	size.x = 30;
	size.y = 30;
	o.x = 100;
	o.y = 85;
	btn = create_button(C_MIRROR, TOGGLE, size, o);
	set_button_name(btn, "Mirror", 0);
	set_color(btn, toggle_color, toggle_color_hover, toggle_color_pressed);
	btn->selected = 0;
	add_sbtn(conic, btn);
	btn = next_b(btn, "Only Points", 299, 85);
	btn->id = C_ONLY_POINTS;
	add_sbtn(conic, btn);
}

void	register_parallel_other_buttons(void)
{
	t_category		*other;
	t_subcategory	*parallel;
	t_vector2		size;
	t_vector2		o;
	t_button		*btn;

	other = get_category(OTHER);
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
	add_sbtn(parallel, btn);
	btn = next_b(btn, "Mirror", 287, 85);
	btn->id = P_MIRROR;
	add_sbtn(parallel, btn);
	btn = next_b(btn, "Only Points", 486, 85);
	btn->id = P_ONLY_POINTS;
	add_sbtn(parallel, btn);
}
