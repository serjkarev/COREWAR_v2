/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 20:33:43 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/03 20:34:26 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "libft.h"
# include "vm_error.h"
# include "op.h"
# include "visual.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <limits.h>

# include <stdbool.h>
/*
#include <sys/types.h>
#include <sys/stat.h>
*/

# define uchar			unsigned char
// # define bool			char
# define uint_t			unsigned int

# define PLAY_HEAD(i)		(g_array_players[(i)]->header)
# define PLAY_NAME(i)		(g_array_players[(i)]->header->prog_name)
# define PLAY_ID(i)			(g_array_players[(i)]->header->magic)
# define PLAY_SIZE(i)		(g_array_players[(i)]->header->prog_size)
# define PLAY_COMMENT(i)	(g_array_players[(i)]->header->comment)
# define PLAY_CODE(i)		(g_array_players[(i)]->code)
# define PLAYER(i)			(g_array_players[(i) - 1])
# define IF_FREE(x)			if (x) free(x)

#define W_ARENA(p, v) g_arena[(p + MEM_SIZE + ((v) % IDX_MOD)) % MEM_SIZE]
#define W_COLOR(p, v) g_arena_color[(p + MEM_SIZE + ((v) % IDX_MOD)) % MEM_SIZE]

# define DUMP				(-1)

typedef struct			s_header
{
	uint_t				magic;
	char				*prog_name;
	uint_t				prog_size;
	char				*comment;
}						t_header;

typedef struct			s_player
{
	t_header			*header;
	char				*code;
}						t_player;

typedef struct			s_cursor
{
	uint_t				id;
	uchar				op;
	bool				carry;
	uint_t				place;
	uint_t				last_live;
	uint_t				delay;
	uchar				owner;
	int32_t				reg[REG_NUMBER];
}						t_cursor;

typedef struct	s_op
{
	char		*name;
	uchar		args_num;
	uchar		args_types[3];
	bool		flag;
	uchar		t_dir_size;
	int			(*func)(t_cursor *, int, int *);
}				t_op;

int				make_live(t_cursor *cursor, int arg, int *shift);
int				make_ld(t_cursor *cursor, int arg, int *shift);
int				make_st(t_cursor *cursor, int arg, int *shift);
int				make_add(t_cursor *cursor, int arg, int *shift);
int				make_sub(t_cursor *cursor, int arg, int *shift);
int				make_and(t_cursor *cursor, int arg, int *shift);
int				make_or(t_cursor *cursor, int arg, int *shift);
int				make_xor(t_cursor *cursor, int arg, int *shift);
int				make_zjmp(t_cursor *cursor, int arg, int *shift);
int				make_ldi(t_cursor *cursor, int arg, int *shift);
int				make_sti(t_cursor *cursor, int arg, int *shift);
int				make_fork(t_cursor *cursor, int arg, int *shift);
int				make_lld(t_cursor *cursor, int arg, int *shift);
int				make_lldi(t_cursor *cursor, int arg, int *shift);
int				make_lfork(t_cursor *cursor, int arg, int *shift);
int				make_aff(t_cursor *cursor, int arg, int *shift);

static t_op    g_op_tab[16] =
{
	{"live", 1, {T_DIR}, 0, 4, make_live},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 1, 4, make_ld},
	{"st", 2, {T_REG, T_IND | T_REG}, 1, 4, make_st},
	{"add", 3, {T_REG, T_REG, T_REG}, 1, 4, make_add},
	{"sub", 3, {T_REG, T_REG, T_REG}, 1, 4, make_sub},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 1, 4, make_and},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4, make_or},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4, make_xor},
	{"zjmp", 1, {T_DIR}, 0, 2, make_zjmp},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2, make_ldi},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 1, 2, make_sti},
	{"fork", 1, {T_DIR}, 0, 2, make_fork},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 1, 4, make_lld},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2, make_lldi},
	{"lfork", 1, {T_DIR}, 0, 2, make_lfork},
	{"aff", 1, {T_REG}, 1, 4, make_aff}
};

static int		g_op_tab_time[16]= {10, 5, 5, 10, 10, 6, 6, 6, 20, 25, 25, 800, 10, 50, 1000, 2};

 uchar			g_arena[MEM_SIZE];
 char			g_arena_color[MEM_SIZE];
 t_player		*g_array_players[MAX_PLAYERS];
 t_list			*g_all_cursor;

//for cyrcles
 t_player		*g_last_player;
 long			g_current_cyrcle;
 int			g_cycles_to_die;
 int			g_live_per_cyrcle;
 int			g_check_amount;//количество проведенных проверок

 int			g_dump;
 bool			g_vizo;
 char			g_vflag;
 bool			g_aflag;

t_header		*init_header(uint_t magic, char *prog_name, uint_t prog_size, char *comment);
t_player		*init_player(t_header *header, char *code);
t_cursor		*init_cursor(uint_t place, int whom);
void			init_map(uint_t place, int whom);
void			init_global(void);

t_player		*parce_bytecode(int file, uint_t number);
void			main_read(int argc, char **argv);
void			main_free(void);

uint_t			xtoi_bytecode(size_t start, size_t size);
int				skip_args(int arg, int dir_size, int max_arg);
int				valid_reg(t_cursor *cursor, int arg, int dir_size, int *shift);
int				get_val(t_cursor *cursor, int *shift, int dir_size, uchar mask);
void			write_val(t_cursor *cursor, int *shift, int val, int mask);

void			buttle(void);
void			print_map(void);
void			print_v(t_cursor *cursor, int val, int reg, uchar mask);
void            cursor_move(t_cursor *cursor, int shift);
void			help(char *name);
void			intro(int amount_players, t_list **poor_players);

#endif
