/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_bytecode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavrius <ahavrius@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 20:30:11 by ahavrius          #+#    #+#             */
/*   Updated: 2019/03/03 20:30:13 by ahavrius         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static uint_t	atoui_bytecode(const uint8_t *str, size_t size)
{
	uint_t	res;
	int			i;

	res = 0;
	i = 0;
	while (size--)
		res += str[size] << (8 * i++);
	return (res);
}

static uint_t	bytecode_to_uint(int file, size_t size)
{
	uint8_t	line[size];
	size_t	real_size;

	real_size = read(file, line, size);
	if (real_size == -1)
		drop_error(ERROR_OPENFILE);
	if (real_size < size)
		drop_error(ERROR_READFILE);
	return (atoui_bytecode(line, size));
}

static char	*bytecode_to_char(int file, size_t size)
{
	char	*line;
	size_t	real_size;

	line = ft_strnew(size);
	if (line == NULL)
		drop_error(ERROR_MEMALLOC);
	real_size = read(file, line, size);
	if (real_size == -1)
		drop_error(ERROR_OPENFILE);
	if (real_size < size)
		drop_error(ERROR_READFILE);
	return (line);
}

t_player	*parce_bytecode(int file, uint_t number)
{ 
	t_header	*header;

	if (bytecode_to_uint(file, 4) != COREWAR_EXEC_MAGIC)
		drop_error(ERROR_MAGICNUMBER);
	header = init_header(number, NULL, 0, NULL);
	header->prog_name = bytecode_to_char(file, PROG_NAME_LENGTH);
	if (bytecode_to_uint(file, 4) != 0)
		drop_error(ERROR_NULLFORMAT);
	header->prog_size = bytecode_to_uint(file, 4);
	if (header->prog_size > CHAMP_MAX_SIZE)
		drop_error(ERROR_CODESIZE);
	header->comment = bytecode_to_char(file, COMMENT_LENGTH);
	if (bytecode_to_uint(file, 4) != 0)
		drop_error(ERROR_NULLFORMAT);
	return (init_player(header, bytecode_to_char(file, header->prog_size)));
}
