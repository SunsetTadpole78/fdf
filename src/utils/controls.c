/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:04:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/05 10:36:04 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_contr(t_c *controls)
{
	controls->keys = malloc(sizeof(t_key *));
	controls->keys[0] = NULL;
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
