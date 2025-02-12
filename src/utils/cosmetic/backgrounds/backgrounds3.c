/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backgrounds3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:36:29 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 18:36:31 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	hello_kitty(t_vector2 v, int w, int h)
{
	return (from_img(v, get_fdf()->background->backgrounds[8]
			, ft_vector2(w, h)));
}
