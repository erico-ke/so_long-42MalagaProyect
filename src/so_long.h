/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:24:53 by erico-ke          #+#    #+#             */
/*   Updated: 2025/02/27 12:21:00 by erico-ke         ###   ########.fr       */
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

# define PXL 50

typedef struct s_p
{
	int	y;
	int	x;
}	t_p;

typedef struct s_img
{
	mlx_texture_t	*collectible;
	mlx_texture_t	*wall;
	mlx_texture_t	*exit_c;
	mlx_texture_t	*exit_o;
	mlx_texture_t	*p;
	mlx_texture_t	*tile;
	mlx_image_t		*collect_i;
	mlx_image_t		*wall_i;
	mlx_image_t		*exit_c_i;
	mlx_image_t		*exit_o_i;
	mlx_image_t		*p_i;
	mlx_image_t		*ti_i;
}	t_img;

typedef struct s_map
{
	char		**map;
	char		**map_save;
	int			moves;
	t_img		img;
	t_p			p;
	int			exit;
	int			exit_c;
	int			coin;
	int			coin_c;
	int			p_num;
	int			p_c;
	int			height;
	int			width;
	int			null_check;
	mlx_t		*wind;
}	t_map;

int		main(int argc, char **argv);

int		print_error(char *ret);
void	the_freer(char	**free_me);
void	free_all(t_map *map);
int		does_textures_exist(t_map *m);

int		map_control(t_map *map, char *map_input);
void	flood_fill(t_map *map, int y, int x);
int		self_map_read(t_map *map);
void	map_list_init(t_map *map);

void	on_key_press(mlx_key_data_t keydata, void *param);
void	map_img_ter(t_map *map);
int		init_window(t_map *map);
void	a_move_map_charge(t_map *m, int ye, int xe);

#endif