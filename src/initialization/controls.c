/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:38:03 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/07 17:05:29 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	next_id(void)
{
	static int	id = -1;

	id++;
	return (id);
}

t_key	key(int v, enum ButtonId id)
{
	t_key	k;
	if (v == -1)
		k.id = -1;
	else
		k.id = next_id();
	k.v = v;
	k.button = id;
	return (k);
}

char	*get_name_for(int key)
{
	char	c;

	if (key == XK_Left)
		return ft_strdup("<-");
	else if (key == XK_Right)
		return ft_strdup("->");
	else if (key == XK_Up)
		return ft_strdup("^\n|");
	else if (key == XK_Down)
		return ft_strdup("|\nv");
	else if (key < 32 || key > 126)
		return ft_strdup("<?>");
	c = key;
	return (ft_substr(&c, 0, 1));
}

/*void	change_key(t_fdf *fdf)
{(void)fdf;
	int	old;
	t_category	*category;
	int	i;
	t_controls	controls;

	controls = fdf->isometric.controls;
	old = controls.edit.old_key.id;
	if (old == controls.up.id)
		controls.up.v = controls.edit.new_key.v;
	else if (old == controls.down.id)
		controls.down.v = controls.edit.new_key.v;
	else if (old == controls.left.id)
		controls.left.v = controls.edit.new_key.v;
	else if (old == controls.right.id)
		controls.right.v = controls.edit.new_key.v;
	else if (old == controls.reduce_x.id)
		controls.reduce_x.v = controls.edit.new_key.v;
	else if (old == controls.add_x.id)
		controls.add_x.v = controls.edit.new_key.v;
	else if (old == controls.reduce_y.id)
		controls.reduce_y.v = controls.edit.new_key.v;
	else if (old == controls.add_y.id)
		controls.add_y.v = controls.edit.new_key.v;
	else if (old == controls.reduce_z.id)
		controls.reduce_z.v = controls.edit.new_key.v;
	else if (old == controls.add_z.id)
		controls.add_z.v = controls.edit.new_key.v;
	else if (old == controls.zoom.id)
		controls.zoom.v = controls.edit.new_key.v;
	else if (old == controls.unzoom.id)
		controls.unzoom.v = controls.edit.new_key.v;

	category = get_navbar_category(CONTROLS);
	if (category)
	{
		i = 0;
		while (category->buttons[i])
		{
			if (category->buttons[i]->id == controls.edit.old_key.button)
			{
				free(category->buttons[i]->name);
				category->buttons[i]->name = get_name_for(controls.edit.new_key.v);
			}
			if (category->buttons[i]->selected)
				category->buttons[i]->selected = 0;
			i++;
		}
	}
	controls.edit.old_key.id = -1;
	controls.edit.new_key.id = -1;
	fdf->must_update = 1;
}*/

/*t_key	get_key_from(t_fdf *fdf, enum ButtonId id)
{(void)fdf;(void)id;
	t_controls	controls;

	controls = fdf->isometric.controls;
	if (id == controls.up.button)
		return (controls.up);
	if (id == controls.down.button)
		return (controls.down);
	if (id == controls.left.button)
		return (controls.left);
	if (id == controls.right.button)
		return (controls.right);
	if (id == controls.reduce_x.button)
		return (controls.reduce_x);
	if (id == controls.add_x.button)
		return (controls.add_x);
	if (id == controls.reduce_y.button)
		return (controls.reduce_y);
	if (id == controls.add_y.button)
		return (controls.add_y);
	if (id == controls.reduce_z.button)
		return (controls.reduce_z);
	if (id == controls.add_z.button)
		return (controls.add_z);
	if (id == controls.zoom.button)
		return (controls.zoom);
	return (controls.unzoom);

	t_key	k;
	k.v = 0;
	return k;
}*/
