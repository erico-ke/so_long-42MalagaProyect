/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:19:44 by erico-ke          #+#    #+#             */
/*   Updated: 2025/03/03 12:12:20 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
		return (print_error("Error:\n	Please insert only one argument."));
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (print_error("Error:\n	Malloc failed."));
	if (map_control(map, argv[1]) == EXIT_FAILURE)
	{
		free_all(map);
		return (EXIT_FAILURE);
	}
	init_window(map);
	map_img_ter(map);
	free_all(map);
	return (EXIT_SUCCESS);
}

/* 
COSAS A AGREGAR:
que el player no se coma la salida...
acortar lineas muy largas
*/