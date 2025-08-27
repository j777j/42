/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:30:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/12 07:01:32 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map)
	{
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
}

static void	destroy_images(t_game *game)
{
	if (game->wall.ptr)
		mlx_destroy_image(game->mlx, game->wall.ptr);
	if (game->floor.ptr)
		mlx_destroy_image(game->mlx, game->floor.ptr);
	if (game->collectible.ptr)
		mlx_destroy_image(game->mlx, game->collectible.ptr);
	if (game->exit.ptr)
		mlx_destroy_image(game->mlx, game->exit.ptr);
	if (game->player.ptr)
		mlx_destroy_image(game->mlx, game->player.ptr);
}

void	exit_game(t_game *game, int exit_code)
{
	if (game)
	{
		free_map(game);
		destroy_images(game);
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
	}
	exit(exit_code);
}
