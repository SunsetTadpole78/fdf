/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ishexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:48:23 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 18:48:26 by lroussel         ###   ########.fr       */
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

int	ft_ishexa(char *value)
{
	int	i;

	i = 0;
	while (value[i] && value[i] != ' ' && value[i] != '\n')
	{
		if (c_hex(value[i]) == -1)
			return (0);
		i++;
	}
	return (1);
}
