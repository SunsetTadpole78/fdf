/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navbar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:49:27 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/27 11:41:00 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_top(t_fdf *fdf)
{
	t_vector2	pos;

	pos.y = 0;
	while (pos.y < 51)
	{
		pos.x = 0;
		while (pos.x < WIDTH)
		{
			if (pos.y == 50)
				put_pixel(fdf, pos, 0x2F2F33, 0.9);
			else
				put_pixel(fdf, pos, 0x1C1C1E, 0.9);
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_open_category(t_fdf *fdf)
{
	t_vector2	pos;

	pos.y = 51;
	while (pos.y < 151)
	{
		pos.x = 0;
		while (pos.x < WIDTH)
		{
			if (pos.y == 150)
				put_pixel(fdf, pos, 0x2F2F33, 0.9);
			else
				put_pixel(fdf, pos, 0x1C1C1E, 0.9);
			pos.x++;
		}
		pos.y++;
	}
}

void	draw_category(t_fdf *fdf, t_category *category)
{
	t_vector2	pos;

	draw_button(fdf, category->main);
	pos = category->main->offset;
	pos.x += category->main->size.x;
	while (pos.y < category->main->size.y)
	{
		put_pixel(fdf, pos, 0x2F2F33, 1);
		pos.y++;
	}
	if (get_navbar()->actual && category == get_navbar()->actual)
	{
		draw_open_category(fdf);
		draw_buttons(fdf, category->buttons);
	}
}

void	update_navbar_text(t_fdf *fdf)
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
		offset.x = category->main->offset.x + category->main->size.x / 2
			- ((ft_strlen(category->title) * 6) / 2);
		offset.y = category->main->offset.y + category->main->size.y / 2 + 4;
		mlx_string_put(fdf->mlx, fdf->window, offset.x, offset.y,
			0xFFFFFF, category->title);
		i++;
	}
}

void	draw_navbar(t_fdf *fdf)
{
	int	i;

	if (!active_navbar(2))
		return ;
	draw_top(fdf);
	if (!get_navbar()->categories)
		return ;
	i = 0;
	while (get_navbar()->categories[i])
	{
		draw_category(fdf, get_navbar()->categories[i]);
		i++;
	}
}

int	cat_count(t_category **categories)
{
	int	i;

	if (!categories)
		return (0);
	i = 0;
	while (categories[i])
		i++;
	return (i);
}

void	free_navbar(void)
{
	int	i;

	if (!active_navbar(2))
		return ;
	i = 0;
	if (get_navbar()->categories)
	{
		while (get_navbar()->categories[i])
		{
			free_buttons(get_navbar()->categories[i]->buttons);
			free(get_navbar()->categories[i]->main);
			free(get_navbar()->categories[i]);
			i++;
		}
		free(get_navbar()->categories);
	}
	free(get_navbar());
}

void	add_to_navbar(t_category *category)
{
	t_vector2	offset;
	int			count;

	count = cat_count(get_navbar()->categories);
	get_navbar()->categories = ft_realloc(get_navbar()->categories,
		(count + 1) * sizeof(t_category *),
		(count + 2) * sizeof(t_category *));
	if (count != 0)
	{
		offset = get_navbar()->categories[count - 1]->main->offset;
		offset.x += get_navbar()->categories[count - 1]->main->size.x + 1;
	}
	category->main->offset = offset;
	get_navbar()->categories[count] = category;
	get_navbar()->categories[count + 1] = NULL;
}

void	add_category(enum CategoryId id, char *title)
{
	t_category	*category;
	t_vector2	size;
	t_vector2	offset;

	if (!active_navbar(2))
		return ;
	category = malloc(sizeof(t_category));
	if (!category)
		return ;
	size.x = 150;
	size.y = 50;
	offset.x = 0;
	offset.y = 0;
	category->main = create_button(NAV, NAVBAR, size, offset);
	set_color(category->main, dark_gray, light_gray, gray);
	category->main->category = category;
	category->id = id;
	category->title = title;
	category->buttons = malloc(sizeof(t_button *));
	category->buttons[0] = NULL;
	add_to_navbar(category);
}

t_category	*get_navbar_category(enum CategoryId id)
{
	int			i;
	t_category	**categories;

	if (!active_navbar(2))
		return (NULL);
	i = 0;
	categories = get_navbar()->categories;
	while (categories[i])
	{
		if (categories[i]->id == id)
			return (categories[i]);
		i++;
	}
	return (NULL);
}

void	add_button(t_category *category, t_button *button)
{
	int			count;

	if (!category)
	{
		free(button);
		return ;
	}
	button->category = category;
	count = buttons_count(category->buttons);
	category->buttons = ft_realloc(category->buttons,
			(count + 1) * sizeof(t_button *),
			(count + 2) * sizeof(t_button *));
	category->buttons[count] = button;
	category->buttons[count + 1] = NULL;
}

int	active_navbar(int v)
{
	static int	active;

	if (v == 0 || v == 1)
		active = v;
	return (active);
}

t_navbar	*get_navbar(void)
{
	static t_navbar	*navbar = NULL;

	if (!active_navbar(2))
		return (NULL);
	if (!navbar)
	{
		navbar = malloc(sizeof(t_navbar));
		navbar->categories = malloc(sizeof(t_category *));
		navbar->categories[0] = NULL;
		navbar->actual = NULL;
		navbar->must_update = 0;
	}
	return (navbar);
}
