/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yessemna <yessemna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:39:44 by yessemna          #+#    #+#             */
/*   Updated: 2024/12/25 00:11:17 by yessemna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	delete_image(mlx_t *mlx, mlx_image_t *img)
{
	if (img)
		mlx_delete_image(mlx, img);
}

void	delete_texture(mlx_texture_t *texture)
{
	if (texture)
		mlx_delete_texture(texture);
}

void	terminate_mlx(t_data *data)
{
	delete_texture(data->textures.ea);
	delete_texture(data->textures.no);
	delete_texture(data->textures.so);
	delete_texture(data->textures.we);
	delete_image(data->mlx.mlx_p, data->mlx.img);
	delete_image(data->mlx.mlx_p, data->mlx.img_r);
	delete_image(data->mlx.mlx_p, data->mlx.img_m);
	delete_image(data->mlx.mlx_p, data->mlx.img_p);
	mlx_terminate(data->mlx.mlx_p);
	exit(EXIT_FAILURE);
}
