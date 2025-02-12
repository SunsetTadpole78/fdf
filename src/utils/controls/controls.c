/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:04:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 23:10:53 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_controls(t_controls *controls)
{
	controls->keys = malloc(sizeof(t_key *));
	controls->keys[0] = NULL;
}

t_controls	*get_controls(t_fdf *fdf)
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

void	add_key(t_controls *controls, enum e_KeyId id,
		int key, enum e_ButtonId button)
{
	int	count;

	count = count_keys(controls->keys);
	controls->keys = ft_realloc(
			controls->keys,
			sizeof(t_key *) * (count + 1),
			sizeof(t_key *) * (count + 2));
	controls->keys[count] = malloc(sizeof(t_key));
	controls->keys[count]->id = ft_nextid();
	controls->keys[count]->key_id = id;
	controls->keys[count]->v = key;
	controls->keys[count]->button = button;
	controls->keys[count]->pressed = 0;
	controls->keys[count + 1] = NULL;
}

void	free_contr(t_controls controls)
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
