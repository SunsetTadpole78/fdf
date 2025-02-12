/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colorbetween.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:09:02 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 22:09:17 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_colorbetween(int ca, int cb, float v, float t)
{
	t_rgb	rgb1;	
	t_rgb	rgb2;
	t_rgb	between;

	rgb1 = ft_torgb(ca);
	rgb2 = ft_torgb(cb);
	between.t = rgb1.t + (v / t * (rgb2.t - rgb1.t));
	between.r = rgb1.r + (v / t * (rgb2.r - rgb1.r));
	between.g = rgb1.g + (v / t * (rgb2.g - rgb1.g));
	between.b = rgb1.b + (v / t * (rgb2.b - rgb1.b));
	return (ft_fromrgb(between));
}
