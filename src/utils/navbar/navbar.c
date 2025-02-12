/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navbar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:49:27 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 17:44:39 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	active_navbar(int v)
{
	static int	active = 0;
	int			temp;

	temp = active;
	if (v == 0 || v == 1)
		active = v;
	if (v == 1 && temp == 0)
	{
		mlx_hook(get_fdf()->window, 6, 1L << 6, on_move_navbar, get_navbar());
		mlx_hook(get_fdf()->window, 4, 1L << 2, on_click_navbar, get_navbar());
	}
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

static int	cat_count(t_category **categories)
{
	int	i;

	if (!categories)
		return (0);
	i = 0;
	while (categories[i])
		i++;
	return (i);
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
	else
	{
		offset.x = 0;
		offset.y = 0;
	}
	category->main->offset = offset;
	get_navbar()->categories[count] = category;
	get_navbar()->categories[count + 1] = NULL;
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
			free(get_navbar()->categories[i]->main->name);
			free(get_navbar()->categories[i]->main);
			free_subs(get_navbar()->categories[i]->subs);
			free(get_navbar()->categories[i]);
			i++;
		}
		free(get_navbar()->categories);
	}
	free(get_navbar());
}
