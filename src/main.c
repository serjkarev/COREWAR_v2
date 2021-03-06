/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:09:41 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/04 16:09:42 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		main(int argc, char **argv)
{
	main_read(argc, argv);
	if (g_dump == 0)
		print_map();
	else
	{
		if (g_vizo == 1)
		{
			init_ncurses();
			print_battle_field();
			print_cursor();
			print_score_board();
		}
		buttle();
	}
	main_free();
	return (0);
}
