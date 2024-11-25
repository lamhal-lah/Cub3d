/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamhal <lamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:33:41 by lamhal            #+#    #+#             */
/*   Updated: 2024/11/25 16:06:06 by lamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_player   pos_in_map(t_player pl)
{
	t_player	tmp;
	tmp.x = pl.x * TILE_SIZE + (TILE_SIZE / 2);
	tmp.y = pl.y * TILE_SIZE + (TILE_SIZE / 2);
	return (tmp);
}

double	ft_normalize(double ang)
{
	if (ang < 0)
		ang += 2 * M_PI;
	if (ang >= 2 * M_PI)
		ang -= 2 * M_PI;
	return (ang);
}

double	set_angle(t_player pl)
{
	double	ang;

	ang = 0;
	if (pl.dir == 'N')
		ang = 3 * M_PI / 2;
	else if (pl.dir == 'E')
		ang = 0;
	else if (pl.dir == 's')
		ang = M_PI / 2;
	else if (pl.dir == 'w')
		ang = M_PI;
	ang = ft_normalize(ang);
	return (ang);
}


int	hitt_wall(double i, double j, t_data *data)
{
	int	x;
	int	y;
	
	x = i / TILE_SIZE;
	y = j / TILE_SIZE;
	if (x < 0 || y < 0)
		return (0);
	if (x >= data->map.map_w || y >= data->map.map_h)
		return (0);
	if (data->map.map[y][x] =='1')
		return (0);
	return (1);
}

int	ray_datiction_dwn(double ang)
{
	if (ang > 0 && ang < M_PI)
		return (1);
	return (0);
}

int	ray_dariction_right(double ang)
{
	if (ang >= 0 && ang < M_PI / 2)
		return (1);
	if (ang > 3 * M_PI / 2 && ang < 2 * M_PI)
		return (1);
	return (0);
}

void	siting_up_steps(double	*x, double *y, double ang)
{
	if (ray_datiction_dwn(ang))
		*y = fabs(*y);
	else
		*y = -fabs(*y);
	if (ray_dariction_right(ang))
		*x = fabs(*x);
	else
		*x = -fabs(*x);
}

t_pos	get_first_intesaction(t_player pl, double ang)
{
	t_pos	inter;

	inter.y = floor(pl.y / TILE_SIZE) * TILE_SIZE;
	if (ang > 0 && ang < M_PI)
		inter.y += TILE_SIZE;
	inter.x = pl.x + (inter.y - pl.y) / tan(ang);
	return (inter);
}

double	find_horiznatal_inter(t_player pl, double ang, t_data *data)
{
	t_pos	inter;
	double	x_step;
	double	y_step;
	int		pixl;

	pixl = 1;
	if (ray_datiction_dwn(ang))
		pixl = -1;
	inter = get_first_intesaction(pl, ang);
	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(ang);
	siting_up_steps(&x_step, &y_step, ang);
	while (hitt_wall(inter.x, inter.y - pixl, data))
	{
		inter.x += x_step;
		inter.y += y_step;
	}
	return (sqrt(pow(inter.x - pl.x, 2) + pow(inter.y - pl.y, 2)));
}

t_pos	get_first_intesaction1(t_player pl, double ang)
{
	t_pos	inter;

	inter.x = floor(pl.x / TILE_SIZE) * TILE_SIZE ;
	if ((ang >= 0 && ang < M_PI / 2)
			|| (ang > 3 * M_PI / 2 && ang < 2 * M_PI))
		inter.x += TILE_SIZE;
	inter.y = pl.y + (inter.x - pl.x) * tan(ang);
	return (inter);
}

float	find_vertical_inter(t_player pl, double ang, t_data *data)
{
	t_pos	inter;
	double		x_step;
	double		y_step;
	int			pixl;

	pixl = 1;
	if (ray_dariction_right(ang))
		pixl = -1;
	inter = get_first_intesaction1(pl, ang);
	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(ang);
	siting_up_steps(&x_step, &y_step, ang);
	while (hitt_wall(inter.x - pixl, inter.y, data))
	{
		inter.x += x_step;
		inter.y += y_step;
	}
	return (sqrt(pow(inter.x - pl.x, 2) + pow(inter.y - pl.y, 2)));
}

void    render_rays(t_data *data, double ang)
{
    t_pos ray;
    t_pos step;
    int pixl;

    ray.x = data->player.x * data->unite;
	ray.y = data->player.y * data->unite;
	step.x = cos(ang) * data->ray_dst * data->unite;
	step.y = sin(ang) * data->ray_dst * data->unite;
	pixl = data->ray_dst * data->unite;
	step.x /= data->ray_dst * data->unite;
	step.y /= data->ray_dst * data->unite;
	while (pixl >= 0)
	{
		mlx_put_pixel(data->mlx.img_m, ray.x, ray.y, 0xFFFF00FF);
		ray.x += step.x;
		ray.y += step.y;
		--pixl;
	}
}

void	ray_cast(t_data	*data)
{
	int		i;
	double	first_ray;
	double	fov;
	double	v_inter;
	double	h_inter;
	
	fov = M_PI / 3;
	i = -1;
	first_ray = data->ang - fov / 2;
	while (++i < 300)
	{
		data->ver = 0;
		first_ray = ft_normalize(first_ray);
		v_inter = find_vertical_inter(data->player, first_ray, data);
		h_inter = find_horiznatal_inter(data->player, first_ray, data);
		if (v_inter <= h_inter)
			data->ray_dst = v_inter;
		else
		{
			data->ray_dst = h_inter;
			data->ver = 1;
		}
		render_rays(data, first_ray);
		// printf("ray dst %f\n", data->ray_dst);
		// render(data, first_ray, i);
		first_ray += fov / 300;
	}
}


