/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 02:14:15 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/06 03:00:51 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

# define FRM 4  // this macro to haw match  moves the player do in single clik !
# define SOP 4  // this is size of player (x and y)!
# define SOF 64 // this is square size
# define SPEED 1.5
# define MI_SIZE 30

# define XPM_IMG mlx_xpm_file_to_image
# define ADDR mlx_get_data_addr

# define N_TEX data->north_tex
# define S_TEX data->south_tex
# define W_TEX data->west_tex
# define E_TEX data->east_tex
# define D_TEX data->anim->door_tex
# define H_TEX data->anim->hand_tex
# define F_TEX data->anim->fire_tex

# define IS_BLOCKING_TILE(c) ((c) == '1' || (c) == 'D' || (c) == 'F')
# define PI 3.141592653589793
# define TOW_PI data->two_pi
# define ROT_SPEED 0.06
# define FOV_ANGLE data->field_of_view
# define PROJECTION_DIST data->projection_dist

# define EPSILON 1e-6
# define SCREEN_W 1920
# define SCREEN_H 1080

# define FRAMES data->anim->door_curr_frame
# define DOOR_FRAMES 22
# define DOOR_FRAME_STEP 1
# define DOOR_TEX data->anim->door_tex

# define HAND_FRAMES 54
# define HAND_CURR_FRAME data->anim->hand_curr_frame
# define ANIM_STEP 3

# define FIRE_FRAMES 10
# define FIRE_CURR_FRAME data->anim->fire_curr_frame
# define FIRE_FRAME_STEP 4
# define FIRE_TEX data->anim->fire_tex
# define FIRE_SWITCH data->anim->fire_switch

# define RESET "\e[0m"

# define BOLD "\e[1m"

# define BLACK "\e[30m"
# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define PURPLE "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[37m"

#endif