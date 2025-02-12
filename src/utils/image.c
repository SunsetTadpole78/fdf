/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:35:55 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 18:35:56 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	from_img(t_vector2 v, t_img *img, t_vector2 size)
{
	char	*pixel;
	float	scale;

	if ((float)img->width / size.x < (float)img->height / size.y)
		scale = (float)img->width / size.x;
	else
		scale = (float)img->height / size.y;
	v.x = (v.x - size.x / 2) * scale + img->width / 2;
	v.y = (v.y - size.y / 2) * scale + img->height / 2;
	if (v.x < 0 || v.x >= img->width || v.y < 0 || v.y >= img->height)
		return (0);
	pixel = img->addr + ((int)v.y * img->ll + (int)v.x * (img->bpp / 8));
	return (*(unsigned int *)pixel);
}
