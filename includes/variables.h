/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 02:14:15 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/03 18:32:15 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

# define FRM 4  // this macro to haw match  moves the player do in single clik !
# define SOP 4  // this is size of player (x and y)!
# define SOF 64 // this is square size
# define SPEED 1.5
# define MI_SIZE 30

# define IS_BLOCKING_TILE(c) ((c) == '1' || (c) == 'D' || (c) == 'F')
# define PI 3.141592653589793
# define TOW_PI data->two_pi
# define ROT_SPEED 0.06
# define FOV_ANGLE data->field_of_view

# define EPSILON 1e-6
# define SCREEN_W 1920
# define SCREEN_H 1080

# define FRAMES data->animations->door_curr_frame
# define DOOR_FRAMES 22
# define DOOR_FRAME_STEP 1
# define DOOR_TEX data->animations->door_tex

# define HAND_FRAMES 54
# define HAND_CURR_FRAME data->animations->hand_curr_frame
# define ANIM_STEP 3

# define FIRE_FRAMES 10
# define FIRE_CURR_FRAME data->animations->fire_curr_frame
# define FIRE_FRAME_STEP 4
# define FIRE_TEX data->animations->fire_tex
# define FIRE_SWITCH data->animations->fire_switch

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