/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmerkulo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 17:01:18 by kmerkulo          #+#    #+#             */
/*   Updated: 2019/03/17 17:01:19 by kmerkulo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		make_aff(t_cursor *cursor, int arg, int *shift)
{
	char	val;
	int		reg;

	val = 0;
	*shift = 2;
	if (!g_aflag || ((arg & 0xc0) != 0x40) ||
		!valid_reg(cursor, arg, 4, shift))
		return (*shift += skip_args(arg, 4, 1));
	reg = g_arena[(cursor->place + (*shift)++) % MEM_SIZE];
	val = cursor->reg[reg - 1];
	ft_printf("Aff: %c\n", val);
	return (*shift);
}
