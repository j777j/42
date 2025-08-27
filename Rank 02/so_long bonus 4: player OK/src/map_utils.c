/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 07:01:02 by juwang            #+#    #+#             */
/*   Updated: 2025/07/12 07:01:05 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		if (i == 0 || i == game->height - 1)
		{
			while (game->map[i][j])
			{
				if (game->map[i][j] != '1')
					exit_game(game, 1);
				j++;
			}
		}
		else
		{
			if (game->map[i][0] != '1' || game->map[i][game->width - 1] != '1')
				exit_game(game, 1);
		}
		i++;
	}
}
