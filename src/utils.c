/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:42:35 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/16 14:42:36 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	chars_to_float(char *nbr)
{
	float			res;
	unsigned int	i;
	unsigned int	sign;

	res = 0;
	i = 0;
	sign = 1;
	if (nbr[0] == '-')
	{
		i = 1;
		sign = -1;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		res = res * 10 + (nbr[i] - '0');
		i++;
	}
	return (res * sign);
}
