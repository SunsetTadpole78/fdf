/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words_charset.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:27:46 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/10 09:20:21 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

unsigned int	ft_count_words_charset(char const *s, char *c)
{
	unsigned int	count;
	int				in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (!is_charset(*s, c) && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (is_charset(*s, c))
			in_word = 0;
		s++;
	}
	return (count);
}
