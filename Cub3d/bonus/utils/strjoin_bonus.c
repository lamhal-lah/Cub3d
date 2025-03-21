/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:49:36 by yessemna          #+#    #+#             */
/*   Updated: 2024/12/21 03:39:44 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2, int len)
{
	int		slen;
	int		totallen;
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	slen = ft_strlen(s1);
	if (len == 0)
		len = ft_strlen(s2);
	totallen = slen + len;
	res = g_malloc(sizeof(char) * (totallen + 1), MALLOC);
	if (!res)
		return (free((char *)s1), NULL);
	while (s1 && s1[i])
		res[j++] = s1[i++];
	i = 0;
	while (s2 && i < len)
		res[j++] = s2[i++];
	res[j] = '\0';
	return (free((char *)s1), res);
}
