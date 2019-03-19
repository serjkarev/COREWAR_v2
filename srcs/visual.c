/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:57:16 by skarev            #+#    #+#             */
/*   Updated: 2019/03/02 15:57:16 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "vm.h"

int		key_hook(void)
{
	int		c;

	while (1)
	{
		c = getch();
		mvwprintw(ncur->score, 38, 2, "key %d ", c);
		wrefresh(ncur->score);
		wattron(ncur->score, A_BOLD);
		mvwprintw(ncur->score, 4, 3, "Cycles/second limit : %d ", ncur->sec_lim/1000);
		wrefresh(ncur->score);
		wattroff(ncur->score, A_BOLD);
		if (c == PAUSE_BUTTON && ncur->pause)
			ncur->pause = false;
		else if (c == PAUSE_BUTTON && !ncur->pause)
			ncur->pause = true;
		else if (c == SPEED_UP && ncur->sec_lim < MAX_SPEED)
			ncur->sec_lim += 10000;
		else if (c == SPEED_DOWN && ncur->sec_lim > MIN_SPEED)
			ncur->sec_lim -= 10000;
		if (ncur->pause)
			continue ;
		else
			break ;
	}
	return (c);
}

void		end_vizo(void)
{
	wclear(ncur->field);
	wclear(ncur->score);
	clear();
	echo();
	curs_set(1);
	endwin();
}

void		print_cursor(void)
{
	int		i;
	t_list	*head;

	i = 0;
	head = g_all_cursor;
	ncur->n_c = 0;
	while (head)
	{
		i = ((t_cursor*)head->content)->place;
		if (g_arena[i] == 1)
		{
			wattron(ncur->field, A_BOLD);
			wattron(ncur->field, COLOR_PAIR(g_arena_color[i] + 100));
			mvwprintw(ncur->field, g_arena_coord[0][i], g_arena_coord[1][i], "%.2x", g_arena[i]);
			wattroff(ncur->field, COLOR_PAIR(g_arena_color[i] + 100));
			wattroff(ncur->field, A_BOLD);
		}
		else
		{
			wattron(ncur->field, COLOR_PAIR(g_arena_color[i] + 10));
			mvwprintw(ncur->field, g_arena_coord[0][i], g_arena_coord[1][i], "%.2x", g_arena[i]);
			wattroff(ncur->field, COLOR_PAIR(g_arena_color[i] + 10));
		}
		ncur->n_c += 1;
		head = head->next;
	}
	wrefresh(ncur->field);
}

int			count_players(void)
{
	int		n;

	n = 0;
	while (g_array_players[n])
		n++;
	return (n);
}

void		print_players(void)
{
	int 	i;

	i = 1;
	while (i - 1 < ncur->n_p)
	{
		mvwprintw(ncur->score, getcury(ncur->score) + 2, 3, "Player -%d : ", i);
		wattron(ncur->score, COLOR_PAIR(i));
		mvwprintw(ncur->score, getcury(ncur->score), 16, "%s", g_array_players[i-1]->header->prog_name);
		wattroff(ncur->score, COLOR_PAIR(i));
		mvwprintw(ncur->score, getcury(ncur->score) + 1, 5, "Last live :                 %d", 123);//где его взять?
		mvwprintw(ncur->score, getcury(ncur->score) + 1, 5, "Lives in last period :      %d", 123);//где его взять?
		i++;
	}
}

void		print_score_board(void)
{
	wattron(ncur->score, A_BOLD);
	// mvwprintw(ncur->score, 2, 14, "** PAUSED **");
	mvwprintw(ncur->score, 4, 3, "Cycles/second limit : %d ", ncur->sec_lim/1000);
	//рег скорости добавить потом где то я ебу где)
	mvwprintw(ncur->score, 7, 3, "Cycle : %d", g_current_cyrcle);
	mvwprintw(ncur->score, 9, 3, "Processes : %d", ncur->n_c);//колво кареток а не игроков
	print_players();
	mvwprintw(ncur->score, getcury(ncur->score) + 3, 3, "CYCLE_TO_DIE : %d", g_cycles_to_die);
	mvwprintw(ncur->score, getcury(ncur->score) + 2, 3, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(ncur->score, getcury(ncur->score) + 2, 3, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(ncur->score, getcury(ncur->score) + 2, 3, "MAX_CHECKS : %d", MAX_CHECKS);
	wattroff(ncur->score, A_BOLD);
	wrefresh(ncur->score);
}

void		init_colors(void)
{
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_color(COLOR_GRAY, 400, 400, 400);
	init_pair(5, COLOR_GRAY, COLOR_BLACK);
	init_pair(11, COLOR_BLACK, COLOR_GREEN);
	init_pair(12, COLOR_BLACK, COLOR_BLUE);
	init_pair(13, COLOR_BLACK, COLOR_RED);
	init_pair(14, COLOR_BLACK, COLOR_CYAN);
	init_pair(10, COLOR_GRAY, COLOR_GRAY);

	init_pair(101, COLOR_WHITE, COLOR_GREEN);
	init_pair(102, COLOR_WHITE, COLOR_BLUE);
	init_pair(103, COLOR_WHITE, COLOR_RED);
	init_pair(104, COLOR_WHITE, COLOR_CYAN);
	// init_pair(10, COLOR_GRAY, COLOR_GRAY);
}

void		print_battle_field(void)
{
	int		i;
	int		y;

	i = 0;
	y = 1;
	wmove(ncur->field, 2, 2);
	while (i < MEM_SIZE && y < 65)
	{
		if (getcurx(ncur->field) < 194)
		{
			if (g_arena_color[i] == 0)
			{
				wattron(ncur->field, COLOR_PAIR(5));
				wattron(ncur->field, A_BOLD);
			}
			else
				wattron(ncur->field, COLOR_PAIR(g_arena_color[i]));
			mvwprintw(ncur->field, y, getcurx(ncur->field), "%.2x ", g_arena[i]);
			if(g_arena_color[i] == 0)
			{
				wattroff(ncur->field, COLOR_PAIR(5));
				wattroff(ncur->field, A_BOLD);
			}
			else
				wattroff(ncur->field, COLOR_PAIR(g_arena_color[i]));
			i++;
		}
		else
		{
			wmove(ncur->field, getcury(ncur->field) + 1, 2);
			y++;
		}
	}
	wrefresh(ncur->field);
}

void		init_coord(void)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	g_arena_coord = (int**)malloc(sizeof(int*) * 2);
	while (i < 2)
	{
		g_arena_coord[i++] = (int*)malloc(sizeof(int) * MEM_SIZE);
	}
	i = 0;
	x = 2;
	y = 1;
	while (i < MEM_SIZE)
	{
		if(y > 64)
			y = 1;
		if (x > 191)
		{
			x = 2;
			y += 1;
		}
		g_arena_coord[0][i] = y;
		g_arena_coord[1][i] = x;
		x += 3;
		i++;
	}
}

void		init_ncurses(void)
{
	initscr();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	cbreak();
	init_colors();
	ncur = (t_cur*)malloc(sizeof(t_cur));
	init_coord();
	ncur->field = newwin(66, 195, 0, 0);
	ncur->score = newwin(66, 59, 0, 195);
	ncur->sec_lim = 50000;
	ncur->n_p = count_players();
	ncur->pause = true;
	box(ncur->field, 0, 0);
	box(ncur->score, 0, 0);
	refresh();
	wrefresh(ncur->field);
	wrefresh(ncur->score);
}
