/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:03:51 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/11 16:38:43 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	switch_view(t_fdf *fdf)
{
	if (fdf->type == ISOMETRIC)
	{
		fdf->type = CONIC;
		fdf->pixel_pos = cpp;
	}
	else if (fdf->type == CONIC)
	{
		fdf->type = PARALLEL;
		fdf->pixel_pos = ppp;
	}
	else
	{
		fdf->type = ISOMETRIC;
		fdf->pixel_pos = ipp;
	}
	fdf->must_update = 1;
}

int	on_press(int keycode, t_fdf *fdf)
{
	t_c	controls;
	t_key	*key;

	if(on_press_controls(keycode, fdf))
		return (1);

	if (keycode == XK_Escape)
	{
		destruct(fdf);
		return (1);
	}
	if (keycode == XK_space)
		switch_view(fdf);
	if (fdf->type == ISOMETRIC)
		controls = fdf->isometric.controls;
	else if (fdf->type == CONIC)
		controls = fdf->conic.controls;
	else
	{
		controls = fdf->parallel.controls;
		rotate_parallel(&fdf->parallel, controls, keycode);
	}
	key = get_key_with_code(controls, keycode);
	if (key)
	{
		key->pressed = 1;
		fdf->keys++;
	}
	return (1);
}

int	on_release(int keycode, t_fdf *fdf)
{
	t_c	controls;
	t_key	*key;

	if (fdf->type == ISOMETRIC)
		controls = fdf->isometric.controls;
	else if (fdf->type == CONIC)
		controls = fdf->conic.controls;
	else
		controls = fdf->parallel.controls;
	key = get_key_with_code(controls, keycode);
	if (key)
	{
		key->pressed = 0;
		fdf->keys--;
	}
	return (0);
}
