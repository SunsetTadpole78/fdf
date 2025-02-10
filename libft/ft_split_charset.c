/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:59:09 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/10 09:21:25 by lroussel         ###   ########.fr       */
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

static char	**free_all(char **splited, unsigned int max)
{
	unsigned int	i;

	i = 0;
	while (i < max)
	{
		free(splited[i]);
		i++;
	}
	free(splited);
	return (NULL);
}

static char	*get_word(char const *s, int start, char *c)
{
	int		end;

	end = start;
	while (s[end] && !is_charset(s[end], c))
		end++;
	return (ft_substr(s, start, end - start));
}

char	**ft_split_charset(char const *s, char *c)
{
	char			**res;
	unsigned int	i;
	unsigned int	j;

	res = malloc(sizeof(char *) * (ft_count_words_charset(s, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(s))
	{
		while (is_charset(s[i], c))
			i++;
		if (i < ft_strlen(s))
		{
			res[j] = get_word(s, i, c);
			if (!res[j])
				return (free_all(res, j));
			i += ft_strlen(res[j]) + 1;
			j++;
		}
	}
	res[j] = 0;
	return (res);
}
