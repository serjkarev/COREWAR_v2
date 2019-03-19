/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarev <skarev@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 14:39:51 by skarev            #+#    #+#             */
/*   Updated: 2019/03/12 14:39:52 by skarev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include <ncurses.h>
# include <locale.h>
# include <string.h>
# include <stdlib.h>

# define COLOR_GRAY 125
# define PAUSE_BUTTON 32
# define SPEED_UP 259
# define SPEED_DOWN 258
# define MAX_SPEED 1000000
# define MIN_SPEED 10000
# define RUN 114

typedef struct		s_cur
{
	WINDOW			*field;
	WINDOW			*score;
	int				sec_lim;
	int				n_p;
	int				n_c;
	bool			pause;

}					t_cur;

t_cur				*ncur;
int					**g_arena_coord;
int					button;

void				init_ncurses(void);
void				print_battle_field(void);
void				init_colors(void);
void				print_score_board(void);
void				print_players(void);
void				print_cursor(void);
int					key_hook(void);
void				end_vizo(void);

#endif