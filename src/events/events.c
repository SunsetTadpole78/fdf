/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:03:51 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 23:12:04 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	default_keys(int keycode, t_fdf *fdf)
{
	if (keycode == XK_Escape)
	{
		destruct(fdf);
		return (1);
	}
	if (keycode == XK_space)
	{
		switch_view(fdf);
		return (1);
	}
	if (on_press_controls(keycode, fdf))
		return (1);
	return (0);
}

int	on_press(int keycode, t_fdf *fdf)
{
	t_controls		controls;
	int				i;

	if (default_keys(keycode, fdf))
		return (1);
	if (fdf->type == ISOMETRIC)
		controls = fdf->isometric.controls;
	else if (fdf->type == CONIC)
		controls = fdf->conic.controls;
	else
	{
		controls = fdf->parallel.controls;
		rotate_parallel(&fdf->parallel, controls, keycode);
	}
	i = 0;
	while (controls.keys[i])
	{
		if (controls.keys[i]->v == keycode)
		{
			controls.keys[i]->pressed = 1;
			fdf->keys++;
		}
		i++;
	}
	return (1);
}

int	on_release(int keycode, t_fdf *fdf)
{
	t_controls		controls;
	int				i;

	if (fdf->type == ISOMETRIC)
		controls = fdf->isometric.controls;
	else if (fdf->type == CONIC)
		controls = fdf->conic.controls;
	else
		controls = fdf->parallel.controls;
	i = 0;
	while (controls.keys[i])
	{
		if (controls.keys[i]->v == keycode)
		{
			controls.keys[i]->pressed = 0;
			fdf->keys--;
			if (fdf->keys < 0)
				fdf->keys = 0;
		}
		i++;
	}
	return (0);
}

int	on_expose(t_fdf *fdf)
{
	fdf->must_update = 1;
	return (1);
}
