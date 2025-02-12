/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backgrounds1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:36:19 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 18:36:21 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	rnb(t_vector2 v, int w, int h)
{
	return (((int)v.x * 255) / w
		+ ((((w - (int)v.x) * 255) / w) << 16)
		+ ((((int)v.y * 255) / h) << 8));
}

int	diag(t_vector2 v, int w, int h)
{
	return ((((int)v.x * 255) / w)
		| ((255 - (((int)v.x + (int)v.y) * 255) / (w + h)) << 8)
		| ((((int)v.y * 255) / h) << 16));
}

int	test(t_vector2 v, int w, int h)
{
	return (from_img(v, get_fdf()->background->backgrounds[0]
			, ft_vector2(w, h)));
}

int	gakarbou(t_vector2 v, int w, int h)
{
	return (from_img(v, get_fdf()->background->backgrounds[1]
			, ft_vector2(w, h)));
}

int	montain(t_vector2 v, int w, int h)
{
	return (from_img(v, get_fdf()->background->backgrounds[2]
			, ft_vector2(w, h)));
}
