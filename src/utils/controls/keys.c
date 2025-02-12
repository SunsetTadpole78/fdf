/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:49:08 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 15:49:09 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_pressed(t_controls controls, enum e_KeyId id)
{
	t_key	*key;

	key = get_key(controls, id);
	if (!key)
		return (0);
	return (key->pressed);
}

t_key	*get_key(t_controls controls, enum e_KeyId id)
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

t_key	*get_key_with_code(t_controls controls, int keycode)
{
	int	i;

	i = 0;
	while (controls.keys[i])
	{
		if (keycode == controls.keys[i]->v)
			return (controls.keys[i]);
		i++;
	}
	return (NULL);
}

t_key	*get_key_from(t_controls *controls, enum e_ButtonId id)
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
