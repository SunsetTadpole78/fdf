/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmin_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:50:06 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/09 10:54:09 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstmin(t_list *list)
{
	int		min;
	t_list	*cur;

	min = *((int *)list->content);
	cur = list->next;
	while (cur)
	{
		if (*((int *)cur->content) < min)
			min = *((int *)cur->content);
		cur = cur->next;
	}
	return (min);
}
