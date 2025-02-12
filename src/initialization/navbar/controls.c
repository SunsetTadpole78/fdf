/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lroussel <lroussel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:13:57 by lroussel          #+#    #+#             */
/*   Updated: 2025/02/12 18:13:57 by lroussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_button	*ctrl_btn(enum e_ButtonId id, t_controls c, enum e_KeyId key,
	t_vector2 offset)
{
	static t_button	*btn = NULL;
	t_vector2		size;

	size.x = 40;
	size.y = 40;
	if (!btn)
	{
		btn = create_button(id, KEYBOX, size, offset);
		set_button_name(btn, get_name_for(get_key(c, key)->v), 1);
		set_color(btn, keybox_color, keybox_color_hover, keybox_color_pressed);
	}
	else
		btn = next_bm(btn, get_name_for(get_key(c, key)->v), offset);
	btn->id = id;
	return (btn);
}

t_subcategory	*register_sub_controls(enum e_SubCategoryId id, void *fn)
{
	t_category	*cat;

	cat = get_category(CONTROLS);
	add_subcategory(cat, id, fn);
	return (get_sub(cat, id));
}

void	register_iso_controls_buttons(t_subcategory *c, t_controls ic)
{
	add_title(c, "Translation:", 100, 100);
	add_sbtn(c, ctrl_btn(CTRLI_UP, ic, I_UP, (t_vector2){200, 60}));
	add_sbtn(c, ctrl_btn(CTRLI_DOWN, ic, I_DOWN, (t_vector2){200, 100}));
	add_sbtn(c, ctrl_btn(CTRLI_LEFT, ic, I_LEFT, (t_vector2){160, 100}));
	add_sbtn(c, ctrl_btn(CTRLI_RIGHT, ic, I_RIGHT, (t_vector2){240, 100}));
	add_title(c, "X Rotation:", 440, 100);
	add_sbtn(c, ctrl_btn(CTRLI_RX1, ic, I_RX1, (t_vector2){497, 60}));
	add_sbtn(c, ctrl_btn(CTRLI_RX2, ic, I_RX2, (t_vector2){497, 100}));
	add_title(c, "Y Rotation:", 697, 100);
	add_sbtn(c, ctrl_btn(CTRLI_RY1, ic, I_RY1, (t_vector2){754, 60}));
	add_sbtn(c, ctrl_btn(CTRLI_RY2, ic, I_RY2, (t_vector2){754, 100}));
	add_title(c, "Z Rotation:", 954, 100);
	add_sbtn(c, ctrl_btn(CTRLI_RZ1, ic, I_RZ1, (t_vector2){1011, 60}));
	add_sbtn(c, ctrl_btn(CTRLI_RZ2, ic, I_RZ2, (t_vector2){1011, 100}));
	add_title(c, "Zoom :", 1196, 100);
	add_sbtn(c, ctrl_btn(CTRLI_ZOOM, ic, I_ZOOM, (t_vector2){1238, 60}));
	add_sbtn(c, ctrl_btn(CTRLI_UNZOOM, ic, I_UNZOOM, (t_vector2){1238, 100}));
	add_title(c, "Y Amplifier :", 1444, 100);
	add_sbtn(c, ctrl_btn(CTRLI_YA1, ic, I_YA1, (t_vector2){1507, 60}));
	add_sbtn(c, ctrl_btn(CTRLI_YA2, ic, I_YA2, (t_vector2){1507, 100}));
}

void	register_conic_controls_buttons(t_subcategory *c, t_controls cc)
{
	add_title(c, "Movements:", 94, 100);
	add_sbtn(c, ctrl_btn(CTRLC_FRONT, cc, C_FRONT, (t_vector2){188, 60}));
	add_sbtn(c, ctrl_btn(CTRLC_BEHIND, cc, C_BEHIND, (t_vector2){188, 100}));
	add_sbtn(c, ctrl_btn(CTRLC_LEFT, cc, C_LEFT, (t_vector2){148, 100}));
	add_sbtn(c, ctrl_btn(CTRLC_RIGHT, cc, C_RIGHT, (t_vector2){228, 100}));
	add_title(c, "Up / Down:", 425, 100);
	add_sbtn(c, ctrl_btn(CTRLC_UP, cc, C_UP, (t_vector2){479, 60}));
	add_sbtn(c, ctrl_btn(CTRLC_DOWN, cc, C_DOWN, (t_vector2){479, 100}));
	add_title(c, "X Rotation:", 679, 100);
	add_sbtn(c, ctrl_btn(CTRLC_RX1, cc, C_RX1, (t_vector2){736, 60}));
	add_sbtn(c, ctrl_btn(CTRLC_RX2, cc, C_RX2, (t_vector2){736, 100}));
	add_title(c, "Y Rotation:", 936, 100);
	add_sbtn(c, ctrl_btn(CTRLC_RY1, cc, C_RY1, (t_vector2){993, 60}));
	add_sbtn(c, ctrl_btn(CTRLC_RY2, cc, C_RY2, (t_vector2){993, 100}));
	add_title(c, "Z Rotation:", 1193, 100);
	add_sbtn(c, ctrl_btn(CTRLC_RZ1, cc, C_RZ1, (t_vector2){1250, 60}));
	add_sbtn(c, ctrl_btn(CTRLC_RZ2, cc, C_RZ2, (t_vector2){1250, 100}));
	add_title(c, "FOV :", 1432, 100);
	add_sbtn(c, ctrl_btn(CTRLC_FOV1, cc, C_FOV1, (t_vector2){1471, 60}));
	add_sbtn(c, ctrl_btn(CTRLC_FOV2, cc, C_FOV2, (t_vector2){1471, 100}));
	add_title(c, "Y Amplifier :", 1677, 100);
	add_sbtn(c, ctrl_btn(CTRLC_YA1, cc, C_YA1, (t_vector2){1740, 60}));
	add_sbtn(c, ctrl_btn(CTRLC_YA2, cc, C_YA2, (t_vector2){1740, 100}));
}

void	register_parallel_controls_buttons(t_subcategory *c, t_controls pc)
{
	add_title(c, "Translation:", 100, 100);
	add_sbtn(c, ctrl_btn(CTRLP_UP, pc, P_UP, (t_vector2){200, 60}));
	add_sbtn(c, ctrl_btn(CTRLP_DOWN, pc, P_DOWN, (t_vector2){200, 100}));
	add_sbtn(c, ctrl_btn(CTRLP_LEFT, pc, P_LEFT, (t_vector2){160, 100}));
	add_sbtn(c, ctrl_btn(CTRLP_RIGHT, pc, P_RIGHT, (t_vector2){240, 100}));
	add_title(c, "X Rotation:", 440, 100);
	add_sbtn(c, ctrl_btn(CTRLP_RX1, pc, P_RX1, (t_vector2){497, 60}));
	add_sbtn(c, ctrl_btn(CTRLP_RX2, pc, P_RX2, (t_vector2){497, 100}));
	add_title(c, "Y Rotation:", 697, 100);
	add_sbtn(c, ctrl_btn(CTRLP_RY1, pc, P_RY1, (t_vector2){754, 60}));
	add_sbtn(c, ctrl_btn(CTRLP_RY2, pc, P_RY2, (t_vector2){754, 100}));
	add_title(c, "Zoom :", 939, 100);
	add_sbtn(c, ctrl_btn(CTRLP_ZOOM, pc, P_ZOOM, (t_vector2){981, 60}));
	add_sbtn(c, ctrl_btn(CTRLP_UNZOOM, pc, P_UNZOOM, (t_vector2){981, 100}));
	add_title(c, "Y Amplifier :", 1187, 100);
	add_sbtn(c, ctrl_btn(CTRLP_YA1, pc, P_YA1, (t_vector2){1250, 60}));
	add_sbtn(c, ctrl_btn(CTRLP_YA2, pc, P_YA2, (t_vector2){1250, 100}));
}
