/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:21:24 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/11 16:30:25 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	on_press_controls(int keycode, t_fdf *fdf)
{
	if (fdf->edit_key)
	{
		change_key(fdf, keycode);
		return (1);
	}
	return (0);
}
