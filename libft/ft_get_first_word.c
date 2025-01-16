/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_first_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:51:26 by lroussel          #+#    #+#             */
/*   Updated: 2024/11/07 15:40:07 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_first_word(const char *s, const char *charset)
{
	unsigned int	start;
	unsigned int	i;

	start = 0;
	while (ft_strchr(charset, s[start]))
		start++;
	i = 0;
	while (s[i + start] && !ft_strchr(charset, s[i + start]))
		i++;
	return (ft_substr(s, start, i));
}
