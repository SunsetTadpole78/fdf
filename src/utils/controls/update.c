/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:48:59 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 15:49:00 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	update_button(t_fdf *fdf, enum e_ButtonId id, t_subcategory *sub)
{
	int	i;
	int	updated;

	i = 0;
	updated = 0;
	while (sub->buttons[i])
	{
		if (sub->buttons[i]->id == id)
		{
			free(sub->buttons[i]->name);
			sub->buttons[i]->name = get_name_for(fdf->edit_key->v);
			updated = 1;
		}
		if (sub->buttons[i]->selected)
			sub->buttons[i]->selected = 0;
		i++;
	}
	return (updated);
}

void	change_key(t_fdf *fdf, int keycode)
{
	t_category	*cat;

	fdf->edit_key->v = keycode;
	cat = get_category(CONTROLS);
	update_button(fdf, fdf->edit_key->button, get_sub(cat, CONTROLS_ISO));
	update_button(fdf, fdf->edit_key->button, get_sub(cat, CONTROLS_CONIC));
	update_button(fdf, fdf->edit_key->button, get_sub(cat, CONTROLS_PARALLEL));
	fdf->edit_key = NULL;
	fdf->must_update = 1;
}

char	*get_name_for(int key)
{
	char	c;

	if (key == XK_Left)
		return (ft_strdup("<-"));
	else if (key == XK_Right)
		return (ft_strdup("->"));
	else if (key == XK_Up)
		return (ft_strdup("^\n|"));
	else if (key == XK_Down)
		return (ft_strdup("|\nv"));
	else if (key < 32 || key > 126)
		return (ft_strdup("<?>"));
	c = key;
	return (ft_substr(&c, 0, 1));
}
