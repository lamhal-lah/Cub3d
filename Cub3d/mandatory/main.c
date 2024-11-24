/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:55:55 by yessemna          #+#    #+#             */
/*   Updated: 2024/11/23 16:04:29 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char const *av[])
{
	t_data  data;

	if (ac != 2)
		print_err("Error\n");
	check_extention(av[1]);
	data.map_path = ft_strdup(av[1]);
	if (fill_map_data(&data))
		return (ft_printf("Error\n"), 1);
	if (check_if_valid(&data))
		return (ft_printf("Error\n"), 1);
	if (prepare_data(&data))
		return (ft_printf("Error\n"), 1);
	esolate_check(&data);
	start_game(&data);

	
	// int	i = 0;
	
	//print map
	// while (i < data.map.map_h)
	// {
	// 	printf("%s\n", data.map.map[i]);
	// 	i++;
	// }
	// printf("data.map_path = %s\n", data.map_path);
	// printf("data.no = %s\n", data.no);
	// printf("data.so = %s\n", data.so);
	// printf("data.ea = %s\n", data.ea);
	// printf("data.we = %s\n", data.we);
	// printf("data.player.x = %d\n", data.player.x);
	// printf("data.player.y = %d\n", data.player.y);
	// printf("data.map.map_w = %d\n", data.map.map_w);
	// printf("data.map.map_h = %d\n", data.map.map_h);

	return 0;
}
