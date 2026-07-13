/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:24:04 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 15:49:06 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "get_next_line.h"
# include "../Libft/libft.h"

# define WIN_W 640
# define WIN_H 480
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.02
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef enum e_error
{
	MALLOC,
	COLOR,
	FD,
	MAP,
	RGB,
	ARGS,
	EXTENSION,
	TEXTURE,
	MLX
}	t_e_error;

/* Struct to store everything related to the mlx window*/
typedef struct s_win
{
	void		*mlx;
	double		win_w;
	double		win_h;
	void		*win;
}				t_win;

/*struct for x, y coordinates in raycasting math*/
typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

/*Struct to store everything related to mlx img*/
typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	int		offset;
}			t_img;

typedef struct s_ray
{
	float		fov;
	float		hfov;
	float		total_d;
	float		ray_angle;
	float		precision;
	float		p_start;
	float		step_size;
	float		dist; 
	float		cor_angle; 
	int			tot_steps;
	float		ray_width;
	float		proj_plane;
}				t_ray;

typedef struct s_text
{
	char	*n_text;
	int		n_tc;
	char	*e_text;
	int		e_tc;
	char	*s_text;
	int		s_tc;
	char	*w_text;
	int		w_tc;
	char	*ceiling;
	int		c_counter;
	char	*floor;
	int		f_counter;
}			t_texture;

typedef struct s_rgb
{
	int		r_val;
	int		g_val;
	int		b_val;
}			t_rgb;

typedef struct s_player
{
	char	spawn_dir;
	float	player_x;
	float	player_y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
	int		key_w;
	int		key_a;
	int		key_s;
	int		key_d;
	int		key_right;
	int		key_left;
}	t_player;

typedef struct s_tex
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_tex;

typedef struct s_textures
{
	t_tex	n;
	t_tex	s;
	t_tex	e;
	t_tex	w;
}	t_textures;

typedef struct s_game
{
	int			fd;
	int			rows;
	int			cols;
	int			offset_x;
	int			offset_y;
	char		**map;
	int			tile_size;
	int			hit_vertical;
	float		cur_ray_dir;
	t_tex		*cur_tex;
	int			cur_tex_x;
	float		cur_wall_height;
	t_texture	*text_ptr;
	t_rgb		*c_rgb;
	t_rgb		*f_rgb;
	t_win		*win_ptr;
	t_img		*img_ptr;
	t_img		*mm_img_ptr;
	t_player	*player;
	t_ray		*rays;
	t_textures	*textures;
	t_point		closest_hit;
}				t_game;

// e_handling.c
void	exit_error(t_game *game, char *msg);
void	e_handling(t_e_error type, t_game *game);
void	calloc_checker(t_game *game);

// mapparse.c
void	read_map(char *mfile, t_game *game);
int		check_nswecf(char *line, int i, t_game *game);

//draw_game.c
void	draw(t_game *game, float start_wall, float end_wall, t_point xy_incr);
void	draw_game(t_game *game, t_point end, t_point xy_incr, float end_x);

//draw_mm.v
void	fill_window(t_game *game);
void	draw_ray(t_game *game, t_point start, t_point end, int color);

//extract_helpers.c
void	open_file(char *mfile, t_game *game);
int		check_direction(char *tline);
void	find_dimensions(char *mfile, t_game *game);
char	**create_map(t_game *game);

// map_extract_checkers.c
int		valid_trimline(char *trimline);
int		mapstart_checker(char *trimline);

//validate_map.c
void	clean_and_free_text(t_game *game);
void	conv_int_rgb(t_game *game, t_rgb *rgb_ptr, char *rgb);
void	validate_map(t_game *game);

//init_window.c
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	init_images(t_game *game);

//render_loop.c
int		render_loop(void *param);

//init_tiles.c
void	init_tile_size(t_game *game);
//init_player
void	init_player(t_game *game);

//key_hooks 
void	play_game(t_game *game);
int		handle_destroy(void *param);
int		handle_keypress(int keycode, void *param);
int		handle_keyrelease(int keycode, void *param);

//cleanup
void	clean_up(t_game *game);
void	close_game_fd(t_game *game);
//init_rays.c
void	init_rays(t_game *game);

//vert_inter.c
t_point	first_vert_inter(t_player *player, t_point v, float ray_dir);
t_point	find_wall_vert(float ray_dir, t_game *game, t_point v);

//hor_inter.c
t_point	first_hor_inter(t_player *player, t_point h, float ray_dir);
t_point	find_wall_hor(float ray_dir, t_game *game, t_point h);

//raycasting.c
t_point	shooting_rays(t_game *game, float degrees);
int		check_inter(char **map, t_point inter, float ray_dir, int is_ver);
float	degree_to_radians(float degree);
float	normalize(float radians);

//val_rgb_helpers.c
int		ft_atoi_rgb(const char *str);

//textures
void	validate_textures(t_game *game);
void	init_textures(t_game *game);
void	destroy_textures(t_game *game);

//player_movement
void	move_player(t_game *game);
void	rotate_player(t_game *game, float angle);

#endif
