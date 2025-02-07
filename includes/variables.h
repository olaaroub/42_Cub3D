/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 02:14:15 by olaaroub          #+#    #+#             */
/*   Updated: 2025/02/07 03:35:52 by olaaroub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

# define FRM 4  // this macro to haw match  moves the player do in single clik !
# define SOP 4  // this is size of player (x and y)!
# define SOF 64 // this is square size
# define SPEED 1.5
# define ROT_SPEED 0.06
# define MI_SIZE 30

# define XPM_IMG mlx_xpm_file_to_image
# define ADDR mlx_get_data_addr

# define PI 3.141592653589793
# define TWO_PI 6.28318530718
# define FOV_ANGLE  1.0471975512

# define EPSILON 1e-6
# define SCREEN_W 1920
# define SCREEN_H 1080

# define DOOR_FRAMES 22
# define DOOR_FRAME_STEP 1

# define HAND_FRAMES 54
# define ANIM_STEP 2

# define FIRE_FRAMES 10
# define FIRE_FRAME_STEP 4

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