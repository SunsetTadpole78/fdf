/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmax_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:47:31 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/09 10:53:15 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstmax(t_list *list)
{
	int		max;
	t_list	*cur;

	max = *((int *)list->content);
	cur = list->next;
	while (cur)
	{
		if (*((int *)cur->content) > max)
			max = *((int *)cur->content);
		cur = cur->next;
	}
	return (max);
}
