/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:48:53 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/04 11:54:51 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <X11/Xlib.h>

int	*get_resolution(void)
{
    static int resolution[2];

    Display *display = XOpenDisplay(NULL);
    if (!display)
	    return (NULL);
    resolution[0] = DisplayWidth(display, 0);
    resolution[1] = DisplayHeight(display, 0);
    XCloseDisplay(display);
    return resolution;
}

int	get_swidth(void)
{
	return get_fdf()->screen.x;
}

int	get_sheight(void)
{
	return get_fdf()->screen.y;
}
