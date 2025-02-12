/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:28:54 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 19:28:55 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	switch_view(t_fdf *fdf)
{
	if (fdf->type == ISOMETRIC)
	{
		fdf->type = CONIC;
		fdf->position_adr = conic_data;
	}
	else if (fdf->type == CONIC)
	{
		fdf->type = PARALLEL;
		fdf->position_adr = parallel_data;
	}
	else
	{
		fdf->type = ISOMETRIC;
		fdf->position_adr = isometric_data;
	}
	fdf->must_update = 1;
}
