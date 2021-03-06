/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsharipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 14:20:38 by rsharipo          #+#    #+#             */
/*   Updated: 2018/07/21 15:29:18 by rsharipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	calc_shift(char *tet, t_stack *elem)
{
	int	i;
	int	j;
	int	min;

	i = 0;
	j = 0;
	min = 22;
	while (i < 20)
	{
		if (tet[i] == '#')
		{
			*(elem->coor + j) = i;
			*(elem->shift + j) = i % 5;
			j++;
		}
		i++;
	}
	i = -1;
	while (++i < 4)
		min = (*(elem->shift + i) < min) ? *(elem->shift + i) : min;
	while (--i >= 0)
		*(elem->shift + i) = *(elem->shift + i) - min;
}

int		scan_map(t_list *data, t_stack *elem, int index, int pos)
{
	while (pos < data->size * data->size)
	{
		if ((data->board)[pos] == '.' && solver(data, elem, index, pos))
			return (1);
		pos++;
	}
	return (0);
}

int		solver(t_list *data, t_stack *elem, int index, int pos)
{
	int	z;

	z = 0;
	if (stack_len(elem) == data->num)
		return (1);
	//printf("[pos: %d] [%c]", pos, index + 'A');
	if (!check_elem(data, elem, index))
	{
//		printf("...skipping %c\n", index + 'A');
		return (0);
	}
	if (index >= data->num)
		return (0);
	elem = add_elem(elem, index);
	if (push_to_board(data, elem, index, pos))
	{
		while (z++ + 1 < data->num)
		{
			if (scan_map(data, elem, (index++ + 1) % data->num, 0))
				return (1);
//			printf("\n");
//			usleep(500000);
		}
		erase_from_board(data, elem);
	}
	pop_elem(&elem);
	return (0);
}

int		init_comb(t_list *data, t_stack *elem, int index)
{
	while (index < data->num)
	{
		printf("...init %c\n", index + 'A');
		if (scan_map(data, elem, index++, 0))
			return (1);
//		printf("\n");
	}
	return (0);
}

char	*ft_filler(t_list *data, char **input, int num)
{
	t_stack	*elem;

	elem = NULL;
	if (num == 0)
		return ("error");
	data->input = input;
	data->size = sq_rt(num) * 2;
	data->num = num;
	create_board(data);
	if (!data->board)
		return ("error");
	while (!init_comb(data, elem, 0))
	{
		data->size = data->size + 1;
		printf("\n...increasing size of map to %d\n\n", data->size);
		create_board(data);
		if (!(data->board))
			return ("error");
	}
	printf("\n...[SOLVED]\n\n");
	return (data->board);
}
