/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:00:44 by lroussel          #+#    #+#             */
/*   Updated: 2025/01/16 14:41:57 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./fdf <map_path>\n", 2);
		return (1);
	}
	map = parse_map(argv[1]);
	if (!map)
	{
		ft_putstr_fd("Map not found\n", 2);
		return (1);
	}
	free_map(map);
}
