/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   navbar.c                                           :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lroussel <lroussel@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/27 08:48:43 by lroussel		  #+#	#+#			 */
/*   Updated: 2025/01/27 10:11:20 by lroussel         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "fdf.h"

void	register_categories(void)
{
	add_category(BG, "Background");
	add_category(LINES, "Lines");
	add_category(CONTROLS, "Controls");
	add_category(OTHER, "Other");
}

t_button	*next_b(t_button *button, int x, int y)
{
	t_vector2	offset;

	offset.x = x;
	offset.y = y;
	return (create_button(button->id, button->type, button->size, offset));
}

void	register_background_buttons(void)
{
	t_category	*bg;
	t_vector2	size;
	t_vector2	o;
	t_button	*btn;

	bg = get_navbar_category(BG);
	size.x = 40;
	size.y = 40;
	o.x = 100;
	o.y = 100;
	btn = create_button(BGG, CIRCLE, size, o);
	btn->selected = 1;
	add_button(bg, btn);
	add_button(bg, set_color(next_b(btn, 200, 100), rnb, rnb, rnb));
	add_button(bg, set_color(next_b(btn, 300, 100), rnb2, rnb2, rnb2));
	add_button(bg, set_color(next_b(btn, 400, 100), ver, ver, ver));
	add_button(bg, set_color(next_b(btn, 500, 100), hor, hor, hor));
	add_button(bg, set_color(next_b(btn, 600, 100), diag, diag, diag));
	add_button(bg, set_color(next_b(btn, 700, 100), circ, circ, circ));
	add_button(bg, set_color(next_b(btn, 800, 100), spir, spir, spir));
	add_button(bg, set_color(next_b(btn, 900, 100), rnb2_m, rnb2_m, rnb2_m));
	add_button(bg, set_color(next_b(btn, 1000, 100), diag_m, diag_m, diag_m));
	add_button(bg, set_color(next_b(btn, 1100, 100), circ_m, circ_m, circ_m));
	add_button(bg, set_color(next_b(btn, 1200, 100), spir_m, spir_m, spir_m));
}

void	init_navbar(t_fdf *fdf)
{
	active_navbar(1);
	mlx_hook(fdf->window, 6, 1L << 6, on_move, get_navbar());
	mlx_hook(fdf->window, 4, 1L << 2, on_click, fdf);
	register_categories();
	register_background_buttons();
}
