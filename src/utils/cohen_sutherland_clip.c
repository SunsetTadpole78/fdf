/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cohen_sutherland_clip.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:14:58 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 19:15:01 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define INSIDE  0
#define LEFT    1
#define RIGHT   2
#define BOTTOM  4
#define TOP     8

static int	compute_outcode(float x, float y)
{
	int	code;

	code = INSIDE;
	if (x < 0)
		code |= LEFT;
	else if (x > width())
		code |= RIGHT;
	if (y < 0)
		code |= TOP;
	else if (y > height())
		code |= BOTTOM;
	return (code);
}

static t_vector2	find_intersection(t_vector2 v1,
		t_vector2 v2, int outcode_out)
{
	t_vector2	v;

	if (outcode_out & TOP)
	{
		v.x = v1.x + (v2.x - v1.x) * (0 - v1.y) / (v2.y - v1.y);
		v.y = 0;
	}
	else if (outcode_out & BOTTOM)
	{
		v.x = v1.x + (v2.x - v1.x) * (height() - v1.y) / (v2.y - v1.y);
		v.y = height();
	}
	else if (outcode_out & RIGHT)
	{
		v.y = v1.y + (v2.y - v1.y) * (width() - v1.x) / (v2.x - v1.x);
		v.x = width();
	}
	else
	{
		v.y = v1.y + (v2.y - v1.y) * (0 - v1.x) / (v2.x - v1.x);
		v.x = 0;
	}
	return (v);
}

static void	crop_line(int is_one, t_vector2 *v1, t_vector2 *v2, t_vector2 v)
{
	if (is_one)
	{
		v1->x = v.x;
		v1->y = v.y;
	}
	else
	{
		v2->x = v.x;
		v2->y = v.y;
	}
}

int	cohen_sutherland_clip(t_vector2 *v1, t_vector2 *v2)
{
	int			outcode1;
	int			outcode2;
	int			outcode_out;
	t_vector2	v;

	outcode1 = compute_outcode(v1->x, v1->y);
	outcode2 = compute_outcode(v2->x, v2->y);
	while (1)
	{
		if ((outcode1 == 0) && (outcode2 == 0))
			return (1);
		else if (outcode1 & outcode2)
			return (0);
		outcode_out = outcode2;
		if (outcode1)
			outcode_out = outcode1;
		v = find_intersection(*v1, *v2, outcode_out);
		crop_line(outcode_out == outcode1, v1, v2, v);
		if (outcode_out == outcode1)
			outcode1 = compute_outcode(v1->x, v1->y);
		else
			outcode2 = compute_outcode(v2->x, v2->y);
	}
	return (0);
}
