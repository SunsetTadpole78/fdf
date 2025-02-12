/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subcategory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 17:46:26 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 17:46:27 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_showable(t_subcategory *sub)
{
	int	(*fn)(void);

	fn = sub->showable;
	return (fn());
}

static int	subs_count(t_subcategory **subs)
{
	int	i;

	i = 0;
	while (subs[i])
		i++;
	return (i);
}

void	add_subcategory(t_category *category,
	enum e_SubCategoryId id, int (showable)(void))
{
	int	count;

	count = subs_count(category->subs);
	category->subs = ft_realloc(
			category->subs,
			sizeof(t_subcategory *) * (count + 1),
			sizeof(t_subcategory *) * (count + 2));
	category->subs[count] = malloc(sizeof (t_subcategory));
	category->subs[count]->id = id;
	category->subs[count]->showable = showable;
	category->subs[count]->buttons = malloc(sizeof(t_button *));
	category->subs[count]->buttons[0] = NULL;
	category->subs[count]->category = category;
	category->subs[count + 1] = NULL;
}

t_subcategory	*get_sub(t_category *category, enum e_SubCategoryId id)
{
	int	i;

	i = 0;
	while (category->subs[i])
	{
		if (category->subs[i]->id == id)
			return (category->subs[i]);
		i++;
	}
	return (NULL);
}

void	free_subs(t_subcategory **subs)
{
	int	i;

	i = 0;
	while (subs[i])
	{
		free_buttons(subs[i]->buttons);
		free(subs[i]);
		i++;
	}
	free(subs);
}
