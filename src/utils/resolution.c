/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:48:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 22:24:46 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/Xlib.h>

int	height(void)
{
	static int	h = -1;

	if (h == -1)
		h = (get_fdf()->screen.y * 0.9) * WINDOW_SIZE;
	return (h);
}

int	width(void)
{
	static int	w = -1;

	if (w == -1)
		w = (get_fdf()->screen.x - 20) * WINDOW_SIZE;
	return (w);
}
