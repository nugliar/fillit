/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sq_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsharipo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 16:30:56 by rsharipo          #+#    #+#             */
/*   Updated: 2018/07/18 16:35:00 by rsharipo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int		sq_rt(int nb)
{
	int	i;

	i = 0;
	while (++i <= nb)
	{
		if (i * i == nb)
			return (i);
		else if (i * i > nb)
			return (i - 1);
	}
	return (0);
}
