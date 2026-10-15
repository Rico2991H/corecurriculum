#include <stdlib.h>
#include <stdio.h>

typedef struct s_map
{
	int		rows;
	int		cols;
	char	empty;
	char	obstcl;
	char	full;
	char	**grid;
}	t_map;

typedef struct s_valsqr
{
	int	x_start;
	int	x_end;
	int	y_start;
	int	y_end;
}	t_valsqr;

void	free_map(t_map *map)
{
	int	i = 0;

	if (!map)
		return ;
	if (map->grid)
	{
		while (i < map->rows)
		{
			free(map->grid[i]);	/* free(NULL) is fine */
			i++;
		}
		free(map->grid);
	}
	free(map);
}

int	read_header(FILE *f, t_map *map)
{
	char	digit[10];
	char	sp1;
	char	sp2;
	char	sp3;
	char	end;
	int		i = 0;

	if (fscanf(f, "%9[0-9]%c%c%c%c%c%c%c", digit, &sp1, &map->empty,
			&sp2, &map->obstcl, &sp3, &map->full, &end) != 8)
		return 0;
	if (sp1 != ' ' || sp2 != ' ' || sp3 != ' ' || end != '\n')
		return 0;
	if (map->empty == map->obstcl || map->empty == map->full
		|| map->obstcl == map->full)
		return 0;
	map->rows = 0;
	while (digit[i])
	{
		map->rows = map->rows * 10 + (digit[i] - '0');
		i++;
	}
	return (map->rows > 0);
}

int	read_grid(FILE *f, t_map *map)
{
	size_t	n;
	ssize_t	r;
	int		i = 0;
	int		j;

	map->grid = calloc(map->rows, sizeof(char *));
	if (!map->grid)
		return 0;
	while (i < map->rows)
	{
		n = 0;
		r = getline(&map->grid[i], &n, f);
		if (r < 2 || map->grid[i][r - 1] != '\n')
			return 0;
		if (i == 0)
			map->cols = r - 1;
		if (r - 1 != map->cols)
			return 0;
		j = 0;
		while (j < map->cols)
		{
			if (map->grid[i][j] != map->empty && map->grid[i][j] != map->obstcl)
				return 0;
			j++;
		}
		i++;
	}
	return 1;
}

t_map	*read_map(char *path)
{
	FILE	*f;
	t_map	*map;
	char	*extra = NULL;
	size_t	n = 0;

	f = fopen(path, "r");
	if (!f)
		return NULL;
	map = calloc(1, sizeof(t_map));
	if (!map || !read_header(f, map) || !read_grid(f, map)
		|| getline(&extra, &n, f) != -1)	/* more lines than announced */
	{
		free(extra);
		free_map(map);
		fclose(f);
		return NULL;
	}
	free(extra);
	fclose(f);
	return map;
}

t_valsqr	find_big_sq(t_map *map)
{
	t_valsqr	square = {0};
	int			x_start;
	int			y_start = 0;
	int			bsq = 0;
	int			sq;
	int			vsq;
	int			i;

	while (y_start < map->rows)
	{
		x_start = 0;
		while (x_start < map->cols)
		{
			sq = 0;
			vsq = 1;
			while (vsq && y_start + sq < map->rows && x_start + sq < map->cols)
			{
				i = 0;
				while (i <= sq && vsq)
				{
					if (map->grid[y_start + i][x_start + sq] == map->obstcl)
						vsq = 0;
					if (map->grid[y_start + sq][x_start + i] == map->obstcl)
						vsq = 0;
					i++;
				}
				if (vsq)
					sq++;
			}
			if (bsq < sq)
			{
				bsq = sq;
				square.x_start = x_start;
				square.x_end = x_start + sq;
				square.y_start = y_start;
				square.y_end = y_start + sq;
			}
			x_start++;
		}
		y_start++;
	}
	return square;
}

void	fill_and_print(t_map *map, t_valsqr sq)
{
	int	y = sq.y_start;
	int	x;

	while (y < sq.y_end)
	{
		x = sq.x_start;
		while (x < sq.x_end)
		{
			map->grid[y][x] = map->full;
			x++;
		}
		y++;
	}
	y = 0;
	while (y < map->rows)
	{
		printf("%s", map->grid[y]);
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
	{
		fprintf(stderr, "map error\n");
		return 1;
	}
	map = read_map(argv[1]);
	if (!map)
	{
		fprintf(stderr, "map error\n");
		return 1;
	}
	t_valsqr sq = find_big_sq(map);
	fill_and_print(map, sq);
	free_map(map);
	return 0;
}
