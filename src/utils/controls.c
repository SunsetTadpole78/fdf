/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:04:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/07 17:00:19 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_contr(t_c *controls)
{
	controls->keys = malloc(sizeof(t_key *));
	controls->keys[0] = NULL;
}

t_c	*get_controls(t_fdf *fdf)
{
	if (fdf->type == ISOMETRIC)
		return (&fdf->isometric.controls);
	if (fdf->type == CONIC)
		return (&fdf->conic.controls);
	if (fdf->type == PARALLEL)
		return (&fdf->parallel.controls);
	return (NULL);
}

static int	count_keys(t_key **keys)
{
	int	i;

	i = 0;
	while (keys[i])
		i++;
	return (i);
}

static int	next_id(void)
{
	static int	id = -1;

	id++;
	return (id);
}

void	add_key(t_c *controls, enum KeyId id, int key, enum ButtonId button)
{
	int	count;

	count = count_keys(controls->keys);
	controls->keys = ft_realloc(
		controls->keys,
		sizeof(t_key *) * (count + 1),
		sizeof(t_key *) * (count + 2)
	);
	controls->keys[count] = malloc(sizeof(t_key));
	controls->keys[count]->id = next_id();
	controls->keys[count]->key_id = id;
	controls->keys[count]->v = key;
	controls->keys[count]->button = button;
	controls->keys[count + 1] = NULL;
}

int	is_key(t_c controls, enum KeyId id, int keycode)
{
	int	i;

	i = 0;
	while (controls.keys[i])
	{
		if (id == controls.keys[i]->key_id && keycode == controls.keys[i]->v)
			return (1);
		i++;
	}
	return (0);
}

t_key	*get_key(t_c controls, enum KeyId id)
{
	int	i;

	i = 0;
	while (controls.keys[i])
	{
		if (id == controls.keys[i]->key_id)
			return (controls.keys[i]);
		i++;
	}
	return (NULL);
}

t_key	*get_key_from(t_c *controls, enum ButtonId id)
{
	int	i;

	i = 0;
	while (controls->keys[i])
	{
		if (controls->keys[i]->button == id)
			return (controls->keys[i]);
		i++;
	}
	return (NULL);
}

void	free_contr(t_c controls)
{
	int	i;

	i = 0;
	while (controls.keys[i])
	{
		free(controls.keys[i]);
		i++;
	}
	free(controls.keys);
}

void	change_key(t_fdf *fdf, int keycode)
{
	enum SubCategoryId	id;
	t_subcategory	*sub;
	int	i;

	fdf->edit_key->v = keycode;
	if (fdf->type == ISOMETRIC)
		id = CONTROLS_ISO;
	else if (fdf->type == CONIC)
		id = CONTROLS_CONIC;
	else
		id = CONTROLS_PARALLEL;

	sub = get_sub(get_navbar_category(CONTROLS), id);
	i = 0;
	while (sub->buttons[i])
	{
		if (sub->buttons[i]->id == fdf->edit_key->button)
		{
			free(sub->buttons[i]->name);
			sub->buttons[i]->name = get_name_for(fdf->edit_key->v);
		}
		if (sub->buttons[i]->selected)
			sub->buttons[i]->selected = 0;
		i++;
	}
	fdf->edit_key = NULL;
	fdf->must_update = 1;
}
