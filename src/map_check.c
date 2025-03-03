/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:51:51 by erico-ke          #+#    #+#             */
/*   Updated: 2025/03/03 12:16:47 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*Map validation functions*/

static int	is_map_ber(char *input)
{
	int		i;
	int		j;
	char	*str;

	i = ft_strlen(input) - 4;
	j = 0;
	str = ".ber";
	while (input[i] == str[j] && input[i])
	{
		i++;
		j++;
		if (input[i] != str[j] || input[i - j] != str[0])
			return (print_error("Error:\n	Incorrect map format: <map>.ber"));
	}
	return (EXIT_SUCCESS);
}

static int	is_map_valid(t_map *map, char *input)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(input, O_RDONLY);
	line = NULL;
	if (fd < 0)
		return (print_error("Error:\n	Map open error"));
	tmp = get_next_line(fd);
	if (!tmp)
		return (print_error("Error:\n	Map read error"));
	while (tmp != NULL)
	{
		line = ft_strjoin_g(line, tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
	map->map = ft_split(line, '\n');
	map->map_save = ft_split(line, '\n');
	free (line);
	return (EXIT_SUCCESS);
}

static void	flood_fill(t_map *map, int y, int x)
{
	if (y < 0 || x < 0 || y >= map->height || x >= map->width)
	{
		map->null_check += 1;
		return ;
	}
	if (map->map_save[y][x] == '1')
		return ;
	else if (map->map_save[y][x] == '*')
		return ;
	else if (map->map_save[y][x] == 'P')
		map->p_num += 1;
	else if (map->map_save[y][x] == 'C')
		map->coin_c += 1;
	else if (map->map_save[y][x] == 'E')
		map->exit += 1;
	else if (map->map_save[y][x] != '0')
	{
		map->null_check += 1;
		return ;
	}
	map->map_save[y][x] = '*';
	flood_fill(map, y + 1, x);
	flood_fill(map, y, x + 1);
	flood_fill(map, y - 1, x);
	flood_fill(map, y, x - 1);
}

static void	map_border_check(t_map *map)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = ft_strlen(map->map[i]);
	len = 0;
	while (map->map[len])
		len++;
	while (map->map[0][i] == '1' && map->map[0][i])
		i++;
	if (i != j)
		map->null_check += 1;
	i = 0;
	while (map->map[i][0] == '1' && map->map[i][j - 1] == '1' && i != len - 1)
		i++;
	if (i != len - 1)
		map->null_check += 1;
	len = 0;
	while (map->map[i][len] == '1' && map->map[i][len])
		len++;
	if (len != j)
		map->null_check += 1;
}

int	map_control(t_map *map, char *map_input)
{
	if (is_map_ber(map_input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (is_map_valid(map, map_input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	map_list_init(map);
	self_map_read(map);
	if (!map->p.y || !map->p.x)
		return (EXIT_FAILURE);
	flood_fill(map, map->p.y, map->p.x);
	map_border_check(map);
	if (map->p_num != 1 || map->coin != map->coin_c || map->exit_c != 1
		|| map->exit != 1 || map->null_check > 0 || map->p_c != 1)
		return (print_error("Error:\n	Invalid map."));
	if (map->coin < 1)
		return (print_error("Error:\n	Invalid map."));
	return (EXIT_SUCCESS);
}
