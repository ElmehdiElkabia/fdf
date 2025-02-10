/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelkabia <eelkabia@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 04:06:00 by eelkabia          #+#    #+#             */
/*   Updated: 2025/02/06 10:08:31 by eelkabia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	get_points(t_fdf *fdf, int i, int j, char **array)
{
	char	**z_color;

	if (!array[j])
		return ;
	z_color = ft_split(array[j], ',');
	if (!z_color)
		return ;
	if (z_color[1])
		fdf->map.points[i][j].color = ft_atoi_base(z_color[1] + 2, 16);
	else
	{
		if (ft_atoi(z_color[0]) > 0 || ft_atoi(z_color[0]) < 0)
			fdf->map.points[i][j].color = 0x7cfc00;
		else
			fdf->map.points[i][j].color = 0x008080;
	}
	fdf->map.points[i][j].x = j;
	fdf->map.points[i][j].y = i;
	fdf->map.points[i][j].z = ft_atoi(z_color[0]);
	free_array(z_color);
}

void	get_dimensions(int fd, t_fdf *fdf)
{
	char	*line;
	char	**array;

	if (fd < 0)
		ft_destroy(fdf, "Error: Failed to open file.");
	fdf->map.width = 0;
	fdf->map.height = 0;
	line = get_next_line(fd);
	if (line == NULL)
		ft_destroy(fdf, "Error: Empty file.");
	while (line)
	{
		if (fdf->map.height == 0)
		{
			array = ft_split(line, ' ');
			while (array[fdf->map.width])
				fdf->map.width++;
			free_array(array);
		}
		fdf->map.height++;
		free(line);
		line = get_next_line(fd);
	}
}

void	init_map(char *filename, t_fdf *fdf)
{
	int	fd;
	int	i;

	i = 0;
	fd = open(filename, O_RDONLY);
	get_dimensions(fd, fdf);
	fdf->map.points = (t_point **)malloc(sizeof(t_point *) * fdf->map.height);
	if (!fdf->map.points)
		ft_destroy(fdf, "Error: Failed to allocate memory for map points.");
	while (i < fdf->map.height)
	{
		fdf->map.points[i] = (t_point *)ft_calloc(fdf->map.width,
				sizeof(t_point));
		if (!fdf->map.points[i])
			ft_destroy(fdf, "Error: Memory allocation failed.");
		i++;
	}
	close(fd);
}

void	parse_map(char *filename, t_fdf *fdf)
{
	int		fd;
	char	*line;
	char	**array;
	int		y;
	int		x;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_destroy(fdf, "Error: Failed to open file.");
	y = 0;
	while (y < fdf->map.height)
	{
		line = get_next_line(fd);
		array = ft_split(line, ' ');
		x = 0;
		while (x != fdf->map.width && array[x])
		{
			get_points(fdf, y, x, array);
			x++;
		}
		free_array(array);
		free(line);
		y++;
	}
	close(fd);
}
