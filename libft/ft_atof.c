/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:41:00 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 18:41:07 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float	ft_atof(char *nbr)
{
	float			res;
	unsigned int	i;
	int				sign;

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
