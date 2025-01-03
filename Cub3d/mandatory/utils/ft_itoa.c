/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:37:19 by yessemna          #+#    #+#             */
/*   Updated: 2024/12/26 04:18:26 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_digit(int nbr)
{
	int	digits;

	digits = 0;
	while (nbr)
	{
		nbr /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		dcount;
	char	*res;

	sign = n < 0;
	dcount = count_digit(n) + sign;
	if (n == 0)
		dcount = 1;
	res = g_malloc(sizeof(char) * (dcount + 1), MALLOC);
	if (!res)
		return (0);
	res[dcount] = '\0';
	if (sign)
	{
		*res = '-' ;
		res[--dcount] = -(n % 10) + '0';
		n = -(n / 10);
	}
	while (dcount-- - sign)
	{
		res[dcount] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}
