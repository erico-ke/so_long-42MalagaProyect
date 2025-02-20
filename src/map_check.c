/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:51:51 by erico-ke          #+#    #+#             */
/*   Updated: 2025/02/20 13:57:48 by erico-ke         ###   ########.fr       */
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
			return (print_error("Incorrect map format: <map>.ber"));
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
		return (print_error("Map open error"));
	tmp = get_next_line(fd);
	if (!tmp)
		return (print_error("Map read error"));
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

void	flood_fill(t_map *map, int y, int x)
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
		map->player_num += 1;
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

int	map_control(t_map *map, char *map_input)
{
	if (is_map_ber(map_input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (is_map_valid(map, map_input) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	map_list_init(map);
	self_map_read(map);
	if (!map->player.y || !map->player.x)
		return (EXIT_FAILURE);
	flood_fill(map, map->player.y, map->player.x);
	if (map->player_num != 1 || map->coin != map->coin_c || map->exit_c != 1
		|| map->exit != 1 || map->null_check > 0 || map->player_c != 1)
		return (print_error("Invalid map."));
	if (map->coin < 1)
		return (print_error("Invalid map."));
	return (EXIT_SUCCESS);
}

//NO OLVIDAR QUE COLECCIONABLES TIENEN QUE SER >= 1