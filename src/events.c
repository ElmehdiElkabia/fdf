/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 03:47:08 by eelkabia          #+#    #+#             */
/*   Updated: 2025/02/06 16:05:14 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	ft_key_hook1(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
		ft_destroy(fdf, "Program terminated successfully.\n");
	else if (keycode == 65361)
		fdf->camera.offset_x -= 10;
	else if (keycode == 65363)
		fdf->camera.offset_x += 10;
	else if (keycode == 65362)
		fdf->camera.offset_y -= 10;
	else if (keycode == 65364)
		fdf->camera.offset_y += 10;
	else if (keycode == 61 && fdf->camera.zoom < 100)
		fdf->camera.zoom += 1;
	ft_menu(fdf);
	render_map(fdf);
	return (0);
}

int	ft_key_hook2(int keycode, t_fdf *fdf)
{
	if (keycode == 61 && fdf->camera.zoom < 50)
		fdf->camera.zoom += 1;
	else if (keycode == 45 && fdf->camera.zoom > 1)
		fdf->camera.zoom -= 1;
	else if (keycode == 49)
		fdf->camera.projection = 1;
	else if (keycode == 50)
		fdf->camera.projection = 0;
	else if (keycode == 91)
		fdf->camera.angle_y += 0.1;
	else if (keycode == 93)
		fdf->camera.angle_y -= 0.1;
	else if (keycode == 101)
		init_camera(fdf);
	ft_menu(fdf);
	render_map(fdf);
	return (0);
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 65307 || keycode == 65363 || keycode == 65362
		|| keycode == 65361 || keycode == 65364)
		ft_key_hook1(keycode, fdf);
	else if (keycode == 61 || keycode == 45 || keycode == 49 || keycode == 50
		|| keycode == 91 || keycode == 93 || keycode == 101)
		ft_key_hook2(keycode, fdf);
	return (0);
}

int	ft_destroy(t_fdf *fdf, char *message)
{
	int	i;

	if (fdf->map.points)
	{
		i = 0;
		while (i < fdf->map.height)
			free(fdf->map.points[i++]);
		free(fdf->map.points);
	}
	if (fdf->image.img)
		mlx_destroy_image(fdf->window.mlx, fdf->image.img);
	if (fdf->window.win)
		mlx_destroy_window(fdf->window.mlx, fdf->window.win);
	if (fdf->window.mlx)
	{
		mlx_destroy_display(fdf->window.mlx);
		free(fdf->window.mlx);
	}
	i = ft_strlen(message);
	write(1, message, i);
	exit(EXIT_SUCCESS);
}

void	ft_menu(t_fdf *fdf)
{
	mlx_string_put(fdf->window.mlx, fdf->window.win, 30, 30, 0xFFFFFF,
		"Move: Arrows");
	mlx_string_put(fdf->window.mlx, fdf->window.win, 30, 50, 0xFFFFFF,
		"Zoom: +/-");
	mlx_string_put(fdf->window.mlx, fdf->window.win, 30, 70, 0xFFFFFF,
		"Projection: 1 / 2");
	mlx_string_put(fdf->window.mlx, fdf->window.win, 30, 90, 0xFFFFFF,
		"Rotate: [");
	mlx_string_put(fdf->window.mlx, fdf->window.win, 30, 110, 0xFFFFFF,
		"Reverse Rotate: ]");
	mlx_string_put(fdf->window.mlx, fdf->window.win, 30, 130, 0xFFFFFF,
		"Reset: E");
	mlx_string_put(fdf->window.mlx, fdf->window.win, 30, 150, 0xFFFFFF,
		"Exit: ESC");
}
