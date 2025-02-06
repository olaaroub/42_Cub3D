/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 17:43:03 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/06 18:10:13 by olaaroub         ###   ########.fr       */
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

	if (data->anim->d_tex)
	{
		i = 0;
		while (i < DOOR_FRAMES && data->anim->d_tex[i])
			mlx_destroy_image(data->mlx, data->anim->d_tex[i++]->texture);
	}
	if (data->anim->h_tex)
	{
		i = 0;
		while (i < HAND_FRAMES && data->anim->h_tex[i])
			mlx_destroy_image(data->mlx, data->anim->h_tex[i++]->texture);
	}
	if (data->anim->f_tex)
	{
		i = 0;
		while (i < FIRE_FRAMES && data->anim->f_tex[i])
			mlx_destroy_image(data->mlx, data->anim->f_tex[i++]->texture);
	}
}

void	ft_error(t_data *data, char *str, int exit_code)
{
	free_trash(&data->trash);
	if (data->mlx != NULL)
	{
		if (data->n_tex)
			mlx_destroy_image(data->mlx, data->n_tex->texture);
		if (data->s_tex)
			mlx_destroy_image(data->mlx, data->s_tex->texture);
		if (data->w_tex)
			mlx_destroy_image(data->mlx, data->w_tex->texture);
		if (data->e_tex)
			mlx_destroy_image(data->mlx, data->e_tex->texture);
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
