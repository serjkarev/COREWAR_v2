/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 20:37:32 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/07 20:37:35 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	run_one_cursor(t_list *l_cursor)
{
	int			arg;
	t_cursor	*cursor;
	int			shift;

	shift = 0;
	cursor = (t_cursor *)l_cursor->content;
    if (cursor->delay == 0)
    {
        cursor->op = g_arena[cursor->place];
        if (cursor->op > 0 && cursor->op <= 16)
            cursor->delay = g_op_tab_time[cursor->op - 1];
    }
	if (cursor->delay > 0 && --cursor->delay > 0)
		return ;
	if (cursor->op > 0 && cursor->op <= 16)
	{
		arg = 0;
		if (g_op_tab[cursor->op - 1].flag)
			arg = g_arena[(cursor->place + 1) % MEM_SIZE];
		g_op_tab[cursor->op - 1].func(cursor, arg, &shift);
		if ((g_vflag & 0x10) && shift)
			cursor_move(cursor, shift);
        cursor->place = (cursor->place + shift) % MEM_SIZE;
	}
	else
		cursor->place = (cursor->place + 1) % MEM_SIZE;
}

static t_list	*kill_when(t_list *l_cursor)
{
	t_cursor	*cursor;
	t_list		*new;

	cursor = (t_cursor *)l_cursor->content;
	new = NULL;
	if ((g_current_cyrcle - cursor->last_live) < g_cycles_to_die)
        new = ft_lstnew_link(cursor, 8);
	else
    {
        if (g_vflag & 0x08)
            ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
	            cursor->id, g_current_cyrcle - cursor->last_live, g_cycles_to_die);
	    free(cursor);
    }
	l_cursor->content = NULL;
	return (new);
}


static t_list	*kill_cursors(void)
{
	t_list	*new_list;

	new_list = ft_lstmap_link(g_all_cursor, kill_when);
	new_list = ft_lst_reverse(new_list);
	ft_lstdel(&g_all_cursor, NULL);
	return (new_list);
}

void		one_check(void)
{
	int		rounds;

	// int ch;
	getch();
	rounds = -1;
	g_live_per_cyrcle = 0;
	while (++rounds < ((g_cycles_to_die > 0) ? g_cycles_to_die : 1)
			&& (g_dump == DUMP || g_current_cyrcle < g_dump))
	{
        g_current_cyrcle++;
        if (g_vflag & 0x02)
            ft_printf("It is now cycle %d\n", g_current_cyrcle);
		ft_lstiter(g_all_cursor, run_one_cursor);

		print_battle_field();
		print_cursor();
		print_score_board();
		// getch();
		//viso
	}
	if (g_current_cyrcle == g_dump)
		return ;
	g_all_cursor = kill_cursors();
	if (g_live_per_cyrcle >= NBR_LIVE || ++g_check_amount == MAX_CHECKS)
	{
        g_cycles_to_die -= CYCLE_DELTA ; //* (g_cycles_to_die >= 0);
        if (g_vflag & 0x02)
            ft_printf("Cycle to die is now %d\n", g_cycles_to_die);
		g_check_amount = 0;

	}

	//viso ?
}

void		buttle(void)
{
	int		ch = 0;
	while (ft_lstlen(g_all_cursor) > 0 && (g_dump == DUMP || g_current_cyrcle < g_dump))
	{
		// ch = getch();
		// if (ch == 49)
		// 	(ncur->pause == TRUE) ? (ncur->pause = FALSE) : (ncur->pause = TRUE);
		// if (ncur->pause == FALSE)
		// 	continue ; 
	    one_check();
	}
	if (g_current_cyrcle == g_dump)
	{
		print_map();
		return ;
	}
	if (g_last_player != NULL)
        ft_printf("Contestant %d, \"%s\", has won !\n",
                  g_last_player->header->magic, g_last_player->header->prog_name);
}
