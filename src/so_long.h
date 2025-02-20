/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:24:53 by erico-ke          #+#    #+#             */
/*   Updated: 2025/02/20 15:17:28 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../libs/libft/src/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define IPXL 50

typedef struct s_player
{
	int	y;
	int	x;
}	t_player;

typedef struct s_img
{
	mlx_texture_t	*collectible;
	mlx_texture_t	*wall;
	mlx_texture_t	*exit_c;
	mlx_texture_t	*exit_o;
	mlx_texture_t	*player;
	mlx_texture_t	*tile;
	mlx_image_t		*collect_i;
	mlx_image_t		*wall_i;
	mlx_image_t		*exit_c_i;
	mlx_image_t		*exit_o_i;
	mlx_image_t		*player_i;
	mlx_image_t		*tile_i;
}	t_img;

typedef struct s_map
{
	char		**map;
	char		**map_save;
	int			moves;
	t_img		img;
	t_player	player;
	int			exit;
	int			exit_c;
	int			coin;
	int			coin_c;
	int			player_num;
	int			player_c;
	int			height;
	int			width;
	int			null_check;
	mlx_t		*wind;
}	t_map;

int		print_error(char *ret);
int		map_control(t_map *map, char *map_input);
void	flood_fill(t_map *map, int y, int x);
void	the_freer(char	**free_me);
int		self_map_read(t_map *map);
void	map_list_init(t_map *map);
void	free_all(t_map *map);
int		main(int argc, char **argv);

#endif