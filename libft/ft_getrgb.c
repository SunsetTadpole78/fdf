/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getrgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:02:00 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 22:02:12 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_rgb	ft_torgb(int v)
{
	t_rgb	rgb;

	rgb.t = (v >> 24) & 0xFF;
	rgb.r = (v >> 16) & 0xFF;
	rgb.g = (v >> 8) & 0xFF;
	rgb.b = v & 0xFF;
	return (rgb);
}
