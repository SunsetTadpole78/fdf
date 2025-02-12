/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:44:43 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 17:44:44 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_vector2	init_text_data(t_button *button)
{
	int			i;
	int			j;
	t_vector2	data;

	i = 0;
	j = 0;
	data.x = 0;
	data.y = 0;
	while (button->name[i])
	{
		if (j > data.x)
			data.x = j;
		if (button->name[i] == '\n')
		{
			j = 0;
			data.y++;
		}
		j++;
		i++;
	}
	return (data);
}

static t_vector2	get_text_offset(t_button *button)
{
	t_vector2	offset;
	t_vector2	data;

	data = init_text_data(button);
	if (button->type == CIRCLE)
	{
		offset.x = button->offset.x + button->size.x / 4
			- (((data.x + (1 * data.y == 0)) * 6) / 2) - 8;
		offset.y = button->offset.y + button->size.y / 4
			+ 8 - ((7 * data.y) / 2);
		return (offset);
	}
	offset.y = button->offset.y + button->size.y / 2 + 4 - ((7 * data.y) / 2);
	if (button->type == TOGGLE)
	{
		offset.x = button->offset.x + button->size.x + 7;
		return (offset);
	}
	offset.x = button->offset.x + button->size.x / 2
		- (((data.x + (1 * data.y == 0)) * 6) / 2);
	return (offset);
}

static void	text(t_fdf *fdf, t_vector2 offset, int color, char *text)
{
	int		i;
	int		base_x;
	char	*temp;

	if (!ft_strchr(text, '\n'))
	{
		mlx_string_put(fdf->mlx, fdf->window, offset.x, offset.y, color, text);
		return ;
	}
	i = -1;
	base_x = offset.x;
	while (text[i + 1])
	{
		i++;
		if (text[i] == '\n')
		{
			offset.x = base_x;
			offset.y += 7;
			continue ;
		}
		temp = ft_substr(text, i, i + 1);
		mlx_string_put(fdf->mlx, fdf->window, offset.x, offset.y, color, temp);
		free(temp);
		offset.x += 6;
	}
}

static void	update_texts(t_fdf *fdf, t_button **buttons)
{
	int			i;
	t_vector2	offset;

	i = 0;
	while (buttons[i])
	{
		offset = get_text_offset(buttons[i]);
		text(fdf, offset, 0xFFFFFF, buttons[i]->name);
		i++;
	}
}

void	update_navbar_texts(t_fdf *fdf)
{
	int			i;
	t_category	*category;
	t_vector2	offset;

	if (!active_navbar(2) || !get_navbar()->categories)
		return ;
	i = 0;
	while (get_navbar()->categories[i])
	{
		category = get_navbar()->categories[i];
		offset = get_text_offset(category->main);
		text(fdf, offset, 0xFFFFFF, category->main->name);
		i++;
	}
	if (get_navbar()->actual)
	{
		update_texts(fdf, get_navbar()->actual->buttons);
		i = 0;
		while (get_navbar()->actual->subs[i])
		{
			if (is_showable(get_navbar()->actual->subs[i]))
				update_texts(fdf, get_navbar()->actual->subs[i]->buttons);
			i++;
		}
	}
}
