/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:11:38 by lroussel          #+#    #+#             */
/*   Updated: 2024/11/06 10:06:24 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	llen;

	if (!little[0])
		return ((char *)big);
	i = 0;
	j = 0;
	llen = ft_strlen(little);
	while (big[i] && i < len)
	{
		if (big[i] == little[j])
			j++;
		else
		{
			if (j > 0)
				i -= j;
			j = 0;
		}
		if (j == llen)
			return ((char *)(big + i - j + 1));
		i++;
	}
	return (NULL);
}
