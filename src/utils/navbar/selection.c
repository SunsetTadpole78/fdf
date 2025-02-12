/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:02:40 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 18:02:41 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	select_toolbar_button(t_button *button)
{
	int			i;
	t_category	**categories;

	i = 0;
	categories = get_navbar()->categories;
	while (categories[i])
	{
		categories[i]->main->selected = categories[i]->main->uniq_id
			== button->uniq_id;
		i++;
	}
}

void	unselect_others(t_button *button)
{
	int			i;
	t_button	**buttons;

	if (!button->category)
		return ;
	i = 0;
	buttons = button->category->buttons;
	while (buttons[i])
	{
		if (buttons[i]->uniq_id != button->uniq_id)
			buttons[i]->selected = 0;
		i++;
	}
}

int	check_outnav(int y, t_navbar *navbar)
{
	if (y > 150 && navbar->actual)
	{
		navbar->actual->main->selected = 0;
		navbar->actual = NULL;
		navbar->must_update = 1;
		return (1);
	}
	return (0);
}
