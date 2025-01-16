/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:01:50 by lroussel          #+#    #+#             */
/*   Updated: 2024/11/06 12:36:34 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*t;
	unsigned char	*r;

	i = 0;
	t = (unsigned char *)dest;
	r = (unsigned char *)src;
	if (n == 0)
		return (t);
	if (!t && !r)
		return (NULL);
	while (i < n)
	{
		t[i] = r[i];
		i++;
	}
	return (t);
}
