/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:24:53 by erico-ke          #+#    #+#             */
/*   Updated: 2025/01/16 18:58:46 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../libs/libft/src/libft.h"
# include <MLX42.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# define UP      13
# define DOWN    1
# define LEFT    0
# define RIGHT   2
# define ESC     53
# define IMG_PXL 50

typedef	struct s_player
{
	int	y;
	int	x;
}	t_player;

typedef struct s_img
{
	void	*collectible;
	void	*wall;
	void	*exit;
	void	*player_left;
	void	*player_right;
	void	*player_up;
	void	*player_down;
	void	*tile;
}	t_img;

typedef struct s_map
{
	char		**map;
	int			moves;
	t_img		img;
	t_player	player;
	
}	t_map;


#endif