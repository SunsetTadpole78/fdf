/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   category.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:54:35 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 17:54:36 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	add_category(enum e_CategoryId id, char *title)
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
	set_button_name(category->main, title, 0);
	set_color(category->main, dark_gray, light_gray, gray);
	category->main->category = category;
	category->id = id;
	category->title = title;
	category->buttons = malloc(sizeof(t_button *));
	category->buttons[0] = NULL;
	category->subs = malloc(sizeof(t_subcategory *));
	category->subs[0] = NULL;
	add_to_navbar(category);
}

t_category	*get_category(enum e_CategoryId id)
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
