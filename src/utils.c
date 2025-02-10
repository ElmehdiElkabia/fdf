/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:28:50 by eelkabia          #+#    #+#             */
/*   Updated: 2025/02/10 23:00:13 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	rotate_point(t_point *point, t_fdf *fdf)
{
	point->y = point->y * cos(fdf->camera.angle_y) - point->z
		* sin(fdf->camera.angle_y);
	point->z = point->y * sin(fdf->camera.angle_y) + point->z
		* cos(fdf->camera.angle_y);
}

void	project_point(t_point *point, t_fdf *fdf)
{
	point->x *= fdf->camera.zoom;
	point->y *= fdf->camera.zoom;
	point->z *= fdf->camera.zoom;
	if (fdf->camera.projection == 1)
	{
		point->x = (point->x - point->y) * cos(0.8);
		point->y = (point->x + point->y) * sin(0.8) - point->z;
	}
	else if (fdf->camera.projection == 0)
	{
		point->x = point->x;
		point->y = point->y;
	}
	rotate_point(point, fdf);
	point->x += WIDTH / 2 + fdf->camera.offset_x;
	point->y += HEIGHT / 4 + fdf->camera.offset_y;
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	ft_atoi_base(const char *str, int base)
{
	int	result;
	int	value;

	result = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			value = *str - '0';
		else if (*str >= 'A' && *str <= 'F')
			value = *str - 'A' + 10;
		else if (*str >= 'a' && *str <= 'f')
			value = *str - 'a' + 10;
		else
			break ;
		result = result * base + value;
		str++;
	}
	return (result);
}
