/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:47:46 by lroussel          #+#    #+#             */
/*   Updated: 2024/11/06 10:08:24 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ss;
	size_t	sd;
	size_t	i;
	size_t	j;

	ss = ft_strlen(src);
	if (size == 0)
		return (ss);
	sd = ft_strlen(dst);
	if (size <= sd)
		return (ss + size);
	i = sd;
	j = 0;
	while (src[j] && j <= size - sd - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if ((sd + j) == size && sd < size)
		dst[i - 1] = '\0';
	else
		dst[i] = '\0';
	return (ss + sd);
}
