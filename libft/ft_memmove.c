/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:14:17 by lroussel          #+#    #+#             */
/*   Updated: 2024/11/05 12:29:40 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*t;
	unsigned char	*r;
	unsigned int	i;

	t = (unsigned char *)dest;
	r = (unsigned char *)src;
	i = n;
	if (t == r)
		return (t);
	if (r < t)
	{
		while (i-- > 0)
		{
			t[i] = r[i];
		}
	}
	else
	{
		while (i > 0)
		{
			t[n - i] = r[n - i];
			i--;
		}
	}
	return (t);
}
