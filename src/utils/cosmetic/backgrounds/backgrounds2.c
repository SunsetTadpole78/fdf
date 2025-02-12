/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backgrounds2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:36:22 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 18:36:28 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	neon(t_vector2 v, int w, int h)
{
	return (from_img(v, get_fdf()->background->backgrounds[3]
			, ft_vector2(w, h)));
}

int	win(t_vector2 v, int w, int h)
{
	return (from_img(v, get_fdf()->background->backgrounds[4]
			, ft_vector2(w, h)));
}

int	ft(t_vector2 v, int w, int h)
{
	return (from_img(v, get_fdf()->background->backgrounds[5]
			, ft_vector2(w, h)));
}

int	rick(t_vector2 v, int w, int h)
{
	return (from_img(v, get_fdf()->background->backgrounds[6]
			, ft_vector2(w, h)));
}

int	larry(t_vector2 v, int w, int h)
{
	return (from_img(v, get_fdf()->background->backgrounds[7]
			, ft_vector2(w, h)));
}
