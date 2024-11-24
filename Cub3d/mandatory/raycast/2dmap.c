/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:02:22 by lamhal            #+#    #+#             */
/*   Updated: 2024/11/24 15:10:13 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		calculate_scale(t_data *data)
{
	int scale;
	int width;
	int	height;

	width = round((float)(data->mlx.img_m)->width / data->map.map_w);
	height = round((float)(data->mlx.img_m)->height / data->map.map_h);
	if (width < height)
		scale = width;
	else
		scale = height;
	return (scale);
}

void	draw_rect(t_data *data, int x, int y, int scale)
{
	int		i;
    int     j;
    int     tmp_x;
    int     tmp_y;
	
    tmp_x = x * scale;
    tmp_y = y * scale;
	if (data->map.map[y][x] == '1')
		data->clr = 0x000000FF;
	else if (data->map.map[y][x] == '0')
		data->clr = 0xFFFFFFFF;
	i = 0;
	while (i <= scale)
	{
        j = 0;
        while (j <= scale)
        {
            mlx_put_pixel(data->mlx.img_m, tmp_x + i, tmp_y + j, data->clr);
            j++;
        }
		// a.x = x * scale ;
		// a.y = y * scale + i;
		// b.x = x * scale + scale;
		// b.y = y * scale + i;
		// draw_line(a, b, data, 0);
		i++;
	}
}

void    draw_map(t_data *data)
{
	int	i;
	int	j;
	int	scale;

	j = -1;
	scale = data->scale;
	while (++j < data->map.map_h)
	{
		i = -1;
		while (++i < data->map.map_w)
			draw_rect(data, i, j, scale);
	}
	j = 0;
    while (++j < data->map.map_h)
    {
        i = -1;
		while(++i < data->map.map_w * data->scale)
			mlx_put_pixel(data->mlx.img_m, i, j * scale, 0x000000FF);
    }
	i = 0;
    while (++i < data->map.map_w)
    {
        j = 0;
		while(++j < data->map.map_h * data->scale)
			mlx_put_pixel(data->mlx.img_m, i * scale, j, 0x000000FF);
    }

}

void	draw_player(mlx_image_t *img, int x_pl, int y_pl)
{
	int	raduis;
	int	x;
	int	y;

	raduis = 4;
	y = -4;
	while(y < raduis)
	{
		x = -4;
		while (x < raduis)
		{
			if (x * x + y * y <= raduis * raduis)
				if ((x_pl + x >= 0 && y_pl + y >= 0)
					&& (x_pl + x <= S_W && y_pl + y <= S_H))
					mlx_put_pixel(img, x_pl + x, y_pl + y, 0xFF0000FF);
			x++;	
		}
		y++;
	}
}

void	render_2d(t_data *data)
{
    draw_map(data);
	draw_player(data->mlx.img_m, data->tmp_pl.x, data->tmp_pl.y);
    mlx_image_to_window(data->mlx.mlx_p, data->mlx.img_m, 0, 0);
}

uint32_t	get_coller(int	r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	clear_image(t_data *data)
{
	int i;
	int j;

	j = -1;
	while (++j <= S_H)
	{
		i = -1;
		while (++i <= S_W)
			mlx_put_pixel(data->mlx.img_m, i, j, get_coller(0, 0, 0, 0));		
	}
}

int	check_hitt_wall(t_data *data, double x, double y)
{
	int i = x / data->scale;
	int j = y / data->scale;
	if (data->map.map[j][i] == '0')
		return (5);
	return (0);
}

void	handell_keys(void *pram)
{
	t_data	*data;

	data = (t_data *)pram;
	if (mlx_is_key_down(data->mlx.mlx_p, MLX_KEY_W))
		data->tmp_pl.y -= check_hitt_wall(data, data->tmp_pl.x, data->tmp_pl.y - 5);
	if (mlx_is_key_down(data->mlx.mlx_p, MLX_KEY_S))
		data->tmp_pl.y += check_hitt_wall(data, data->tmp_pl.x, data->tmp_pl.y + 5);;
	if (mlx_is_key_down(data->mlx.mlx_p, MLX_KEY_A))
		data->tmp_pl.x -= check_hitt_wall(data, data->tmp_pl.x - 5, data->tmp_pl.y);;
	if (mlx_is_key_down(data->mlx.mlx_p, MLX_KEY_D))
		data->tmp_pl.x += check_hitt_wall(data, data->tmp_pl.x + 5, data->tmp_pl.y);;
	if (mlx_is_key_down(data->mlx.mlx_p, MLX_KEY_LEFT))
		data->ang -= M_PI / 180;
	if (mlx_is_key_down(data->mlx.mlx_p, MLX_KEY_RIGHT))
		data->ang += M_PI / 180;
	clear_image(data);
	render_2d(data);
}

// void	handell_keys(void *pram)
// {
// 	t_data	*data;

// 	data = (t_data *)pram;
// 	if (mlx_is_key_down(data->mlx.mlx_p, MLX_KEY_W))
// 		data->tmp_pl.y -= 5;
// 	if (mlx_is_key_down(data->mlx.mlx_p, MLX_KEY_S))
// 		data->tmp_pl.y += 5;
// 	if (mlx_is_key_down(data->mlx.mlx_p, MLX_KEY_A))
// 		data->tmp_pl.x -= 5;
// 	if (mlx_is_key_down(data->mlx.mlx_p, MLX_KEY_D))
// 		data->tmp_pl.x += 5;
// 	if (mlx_is_key_down(data->mlx.mlx_p, MLX_KEY_LEFT))
// 		data->ang -= M_PI / 180;
// 	if (mlx_is_key_down(data->mlx.mlx_p, MLX_KEY_RIGHT))
// 		data->ang += M_PI / 180;
// 	clear_image(data);
// 	render_2d(data);
// }

void	start_game(t_data *data)
{
    data->mlx.mlx_p = mlx_init(S_W, S_H, "cub3d", 0);
    data->mlx.img_m = mlx_new_image(data->mlx.mlx_p, S_W, S_H);
	data->scale = calculate_scale(data);
	data->tmp_pl.x = data->player.x * data->scale + (data->scale / 2);
	data->tmp_pl.y = data->player.y * data->scale + (data->scale / 2);
	render_2d(data);
    mlx_loop_hook(data->mlx.mlx_p, handell_keys, data);
    mlx_loop(data->mlx.mlx_p);
}