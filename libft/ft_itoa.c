/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:48:24 by lroussel          #+#    #+#             */
/*   Updated: 2024/11/07 17:18:15 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	unsigned int	size;
	char			*res;

	if (n == MIN_INT)
		return (ft_strdup("-2147483648"));
	size = ft_count_digits(n);
	if (n < 0)
		size++;
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	if (n < 0)
	{
		res[0] = '-';
		n *= -1;
	}
	res[size--] = '\0';
	while (n > 9)
	{
		res[size] = (n % 10) + '0';
		n /= 10;
		size--;
	}
	res[size] = n + '0';
	return (res);
}
