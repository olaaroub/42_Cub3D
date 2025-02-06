/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:43:03 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/06 03:51:06 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	del(void *addr)
{
	if (addr)
		free(addr);
}

void	free_trash(t_list **trash)
{
	ft_lstclear(trash, del);
}

void	add_to_trash(t_list **trash, void *addr)
{
	t_list	*new;

	new = ft_lstnew(addr);
	ft_lstadd_back(trash, new);
}

static void	bonus_cleanup(t_data *data)
{
	int	i;

	if (D_TEX)
	{
		i = 0;
		while (i < DOOR_FRAMES && D_TEX[i])
			mlx_destroy_image(data->mlx, D_TEX[i++]->texture);
	}
	if (H_TEX)
	{
		i = 0;
		while (i < HAND_FRAMES && H_TEX[i])
			mlx_destroy_image(data->mlx, H_TEX[i++]->texture);
	}
	if (F_TEX)
	{
		i = 0;
		while (i < FIRE_FRAMES && F_TEX[i])
			mlx_destroy_image(data->mlx, F_TEX[i++]->texture);
	}
}

void	ft_error(t_data *data, char *str, int exit_code)
{
	free_trash(&data->trash);
	if (data->mlx != NULL)
	{
		if (N_TEX)
			mlx_destroy_image(data->mlx, N_TEX->texture);
		if (S_TEX)
			mlx_destroy_image(data->mlx, S_TEX->texture);
		if (W_TEX)
			mlx_destroy_image(data->mlx, W_TEX->texture);
		if (E_TEX)
			mlx_destroy_image(data->mlx, E_TEX->texture);
		if (BONUS)
			bonus_cleanup(data);
		if (data->img)
			mlx_destroy_image(data->mlx, data->img->img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (exit_code == 1)
		write(2, str, ft_strlen(str));
	else
		printf("%s\n", str);
	exit(exit_code);
}
