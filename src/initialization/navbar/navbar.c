/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   navbar.c                                           :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lroussel <lroussel@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/27 08:48:43 by lroussel		  #+#	#+#			 */
/*   Updated: 2025/02/12 22:49:13 by lroussel         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "fdf.h"

static void	register_categories(void)
{
	add_category(BG, "Background");
	add_category(LINES, "Lines");
	add_category(CONTROLS, "Controls");
	add_category(OTHER, "Other");
}

void	init_navbar(t_fdf *fdf)
{
	active_navbar(1);
	register_categories();
	register_background_buttons();
	register_lines_buttons();
	register_iso_controls_buttons(
		register_sub_controls(CONTROLS_ISO, is_isometric),
		fdf->isometric.controls);
	register_conic_controls_buttons(
		register_sub_controls(CONTROLS_CONIC, is_conic),
		fdf->conic.controls);
	register_parallel_controls_buttons(
		register_sub_controls(CONTROLS_PARALLEL, is_parallel),
		fdf->parallel.controls);
	register_iso_other_buttons();
	register_conic_other_buttons();
	register_parallel_other_buttons();
}
