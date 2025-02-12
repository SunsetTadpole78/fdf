/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:47:39 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 18:47:43 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	c_hex(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (10 + c - 'a');
	if (c >= 'A' && c <= 'F')
		return (10 + c - 'A');
	return (-1);
}

int	ft_atoh(char *value)
{
	int	res;
	int	i;

	res = 0;
	i = 2;
	while (value[i] && value[i] != ' ' && value[i] != '\n')
	{
		res = res * 16 + c_hex(value[i]);
		i++;
	}
	return (res);
}
