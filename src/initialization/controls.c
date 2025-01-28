/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 09:38:03 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/28 11:42:30 by lroussel         ###   ########.fr       */
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

void	init_controls(t_fdf *fdf)
{
	fdf->controls.up = key('w', CTRL_UP);
	fdf->controls.down = key('s', CTRL_DOWN);
	fdf->controls.left = key('a', CTRL_LEFT);
	fdf->controls.right = key('d', CTRL_RIGHT);
	fdf->controls.reduce_x = key('u', CTRL_REDUCE_X);
	fdf->controls.add_x = key('j', CTRL_ADD_X);
	fdf->controls.reduce_y = key('i', CTRL_REDUCE_Y);
	fdf->controls.add_y = key('k', CTRL_ADD_Y);
	fdf->controls.reduce_z = key('o', CTRL_REDUCE_Z);
	fdf->controls.add_z = key('l', CTRL_ADD_Z);
	fdf->controls.zoom = key('=', CTRL_ZOOM);
	fdf->controls.unzoom = key('-', CTRL_UNZOOM);
	fdf->controls.edit.old_key = key(-1, CTRL_UP);
	fdf->controls.edit.new_key = key(-1, CTRL_UP);
}

char	*get_name_for(int key)
{
	char	c;

	if (key == XK_Left)
		return ft_strdup("<");
	else if (key == XK_Right)
		return ft_strdup(">");
	else if (key == XK_Up)
		return ft_strdup("^");
	else if (key == XK_Down)
		return ft_strdup("v");
	else if (key < 32 || key > 126)
		return ft_strdup("<?>");
	c = key;
	return (ft_strdup(&c));
}

void	change_key(t_fdf *fdf)
{
	int	old;
	t_category	*category;
	int	i;

	old = fdf->controls.edit.old_key.id;
	if (old == fdf->controls.up.id)
		fdf->controls.up.v = fdf->controls.edit.new_key.v;
	else if (old == fdf->controls.down.id)
		fdf->controls.down.v = fdf->controls.edit.new_key.v;
	else if (old == fdf->controls.left.id)
		fdf->controls.left.v = fdf->controls.edit.new_key.v;
	else if (old == fdf->controls.right.id)
		fdf->controls.right.v = fdf->controls.edit.new_key.v;
	else if (old == fdf->controls.reduce_x.id)
		fdf->controls.reduce_x.v = fdf->controls.edit.new_key.v;
	else if (old == fdf->controls.add_x.id)
		fdf->controls.add_x.v = fdf->controls.edit.new_key.v;
	else if (old == fdf->controls.reduce_y.id)
		fdf->controls.reduce_y.v = fdf->controls.edit.new_key.v;
	else if (old == fdf->controls.add_y.id)
		fdf->controls.add_y.v = fdf->controls.edit.new_key.v;
	else if (old == fdf->controls.reduce_z.id)
		fdf->controls.reduce_z.v = fdf->controls.edit.new_key.v;
	else if (old == fdf->controls.add_z.id)
		fdf->controls.add_z.v = fdf->controls.edit.new_key.v;
	else if (old == fdf->controls.zoom.id)
		fdf->controls.zoom.v = fdf->controls.edit.new_key.v;
	else if (old == fdf->controls.unzoom.id)
		fdf->controls.unzoom.v = fdf->controls.edit.new_key.v;

	category = get_navbar_category(CONTROLS);
	if (category)
	{
		i = 0;
		while (category->buttons[i])
		{
			if (category->buttons[i]->id == fdf->controls.edit.old_key.button)
			{
				free(category->buttons[i]->name);
				category->buttons[i]->name = get_name_for(fdf->controls.edit.new_key.v);
			}
			if (category->buttons[i]->selected)
				category->buttons[i]->selected = 0;
			i++;
		}
	}
	fdf->controls.edit.old_key.id = -1;
	fdf->controls.edit.new_key.id = -1;
	fdf->must_update = 1;
}

t_key	get_key_from(t_fdf *fdf, enum ButtonId id)
{
	if (id == fdf->controls.up.button)
		return (fdf->controls.up);
	if (id == fdf->controls.down.button)
		return (fdf->controls.down);
	if (id == fdf->controls.left.button)
		return (fdf->controls.left);
	if (id == fdf->controls.right.button)
		return (fdf->controls.right);
	if (id == fdf->controls.reduce_x.button)
		return (fdf->controls.reduce_x);
	if (id == fdf->controls.add_x.button)
		return (fdf->controls.add_x);
	if (id == fdf->controls.reduce_y.button)
		return (fdf->controls.reduce_y);
	if (id == fdf->controls.add_y.button)
		return (fdf->controls.add_y);
	if (id == fdf->controls.reduce_z.button)
		return (fdf->controls.reduce_z);
	if (id == fdf->controls.add_z.button)
		return (fdf->controls.add_z);
	if (id == fdf->controls.zoom.button)
		return (fdf->controls.zoom);
	return (fdf->controls.unzoom);

}
