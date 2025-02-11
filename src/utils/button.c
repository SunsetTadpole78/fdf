/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:45:04 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/11 16:31:16 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	next_id(void)
{
	static int	id = -1;

	id++;
	return (id);
}

t_button	*set_color(t_button *button, void *default_color,
				void *hover_color, void *pressed_color)
{
	button->color = default_color;
	button->hover_color = hover_color;
	button->pressed_color = pressed_color;
	return (button);
}

void	set_button_name(t_button *button, char *name, int must_be_free)
{
	if (button->name)
		free(button->name);
	button->name = ft_strdup(name);
	if (must_be_free)
		free(name);
}

t_button	*create_button(enum e_ButtonId id, enum e_ButtonType type,
	t_vector2 size, t_vector2 offset)
{
	t_button	*button;

	button = malloc(sizeof(t_button));
	if (!button)
		return (NULL);
	button->id = id;
	button->uniq_id = next_id();
	button->type = type;
	button->name = ft_strdup("");
	button->size = size;
	button->offset = offset;
	button->color = black;
	button->hover_color = black;
	button->pressed_color = black;
	button->selected = 0;
	button->hover = 0;
	button->category = NULL;
	return (button);
}

int	buttons_count(t_button **buttons)
{
	int	i;

	if (!buttons)
		return (0);
	i = 0;
	while (buttons[i])
		i++;
	return (i);
}

void	free_buttons(t_button **buttons)
{
	int	i;

	i = 0;
	while (buttons[i])
	{
		free(buttons[i]->name);
		free(buttons[i]);
		i++;
	}
	free(buttons);
}

int	is_button(t_vector2 v, t_button *button)
{
	t_vector2	offset;

	offset = button->offset;
	if (button->type == CIRCLE)
		return (ft_distance(offset, v) <= button->size.x);
	if (button->type == CUBE)
		return (v.x >= (offset.x - button->size.x * 1.5f) && v.x <= button->size.x * 0.5f + offset.x
				&& v.y >= (offset.y - button->size.y) && v.y <= button->size.y + offset.y);
	return (v.x >= offset.x && v.x <= button->size.x + offset.x
		&& v.y >= offset.y && v.y <= button->size.y + offset.y);
}
