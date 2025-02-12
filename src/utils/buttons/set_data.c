/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:00:59 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 16:01:32 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_button	**create_array(t_button *buttons[2], t_button *button)
{
	buttons[0] = button;
	buttons[1] = NULL;
	return (buttons);
}
