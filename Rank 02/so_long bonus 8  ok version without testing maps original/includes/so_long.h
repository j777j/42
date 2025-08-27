/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/20 04:56:52 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 64

// Key codes
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

// Game elements
# define WALL '1'
# define FLOOR '0'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'
# define ENEMY 'X'

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_enemy
{
	int		x;
	int		y;
	int		dir;
}			t_enemy;

typedef struct s_tile_data
{
	int		*exits;
	int		*players;
	char	c;
	int		x;
	int		y;
}			t_tile_data;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	char	**map;
	int		width;
	int		height;
	int		collectibles;
	int		player_x;
	int		player_y;
	int		moves;
	t_img	wall;
	t_img	floor;
	t_img	collectible;
	t_img	exit;
	t_img	exit_open;
	t_img	player[3];
	int		player_anim_frame;
	int		player_anim_delay;
	t_img	buffer;
	t_img	enemy[2];
	t_enemy	*enemies;
	int		enemy_count;
	int		enemy_anim_frame;
	int		enemy_anim_delay;
	int		enemy_move_delay;
}			t_game;

// Function prototypes
void		init_game(t_game *game, char *map_file);
void		load_map(t_game *game, char *map_file);
void		check_map(t_game *game);
void		init_mlx(t_game *game);
void		load_sprites(t_game *game);
int			game_loop(t_game *game);
int			handle_keypress(int keycode, t_game *game);
void		render_map(t_game *game);
void		move_player(t_game *game, int new_x, int new_y);
void		count_elements(t_game *game, int *exits, int *players);
void		put_pixel_to_buffer(t_img *buffer, int x, int y, int color);
void		display_move_count(t_game *game);
void		locate_enemies(t_game *game);
void		exit_game(t_game *game, int exit_code);
void		check_enemy_collision(t_game *game, int new_x, int new_y);
void		validate_path(t_game *game);
void		check_walls(t_game *game);
int			close_window(t_game *game);

#endif
