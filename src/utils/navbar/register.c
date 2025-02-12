/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:13:43 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 18:13:45 by lroussel         ###   ########.fr       */
/*                                                                            */
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
	add_sbtn(sub, btn);
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
