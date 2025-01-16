/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:52:14 by lroussel          #+#    #+#             */
/*   Updated: 2024/11/07 17:17:59 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_count_digits(int n)
{
	unsigned int	count;

	if (n == MIN_INT)
		return (10);
	if (n == 0)
		return (1);
	if (n < 0)
		n *= -1;
	count = 0;
	while (n / 10 != 0 || n % 10 != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}
