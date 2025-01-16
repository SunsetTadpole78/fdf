/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:36:04 by lroussel          #+#    #+#             */
/*   Updated: 2024/11/06 13:02:22 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_wspace(int c)
{
	return (c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f' || c == ' ');
}

int	ft_atoi(const char *nptr)
{
	int			i;
	short int	s;
	int			result;

	i = 0;
	s = 1;
	result = 0;
	while (is_wspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			s = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * s);
}
