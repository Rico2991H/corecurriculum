#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

typedef struct s_map
{
	int 	rows;
	int	cols;
	char	empty;
	char	obstcl;
	char	full;
	char**	grid;
	int	bsq_y;
	int	bsq_x;
} t_map;

typedef struct s_valsqr
{
	int x_start;
	int x_end;
	int y_start;
	int y_end;
} t_valsqr;

t_map* init_map()
{
	t_map *map = malloc(sizeof(t_map));
	if (!map)
		return NULL;
	map->cols = 0;
	map->rows = 0;
	map->empty = '\0';
	map->obstcl = '\0';
	map->full = '\0';
	map->grid = NULL;
	return map;
}

/* FIX: free everything, works on a half-built map too */
void	free_map(t_map *map)
{
	int i = 0;
	if (!map)
		return;
	if (map->grid)
	{
		while (i < map->rows)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}

int	conv_digit(char* digit)
{
	int 	num = 0;
	int	i = 0;
	while(digit[i])
	{
		num = num * 10 + (digit[i] - '0');	/* FIX: was *digit */
		i++;
	}
	return num;
}
		
int	extract_firstline(FILE* file, t_map *map)
{
	int s = 0;
	char sp1;
	char sp2;
	char sp3;
	char end;
	char digit[10];
	/* FIX: [0-9] instead of [123456789], so "10" can be read */
	s = fscanf(file, "%9[0-9]%c%c%c%c%c%c%c", digit, &sp1, &map->empty, 
			&sp2, &map->obstcl, &sp3, &map->full, &end);	
	if (s != 8)
		return 0;
	if (sp1 != ' ' || sp2 != ' ' || sp3 != ' ')
		return 0;
	if (map->empty == map->obstcl || map->empty == map->full || map->obstcl == map->full)
		return 0;
	if (end != '\n')
		return 0;
	map->rows = conv_digit(digit);
	if (map->rows <= 0)	/* FIX: "0" is not a valid map */
		return 0;
	return 1;
}

int	init_grid(t_map* map)
{
	/* FIX: calloc so free_map is safe if a row malloc fails halfway */
	map->grid = calloc(map->rows, sizeof(char*));
	if (!map->grid)
		return 0;
	int i = 0;
	while( i < map->rows)
	{
		/* FIX: cols chars + '\n' + '\0' (was cols, one byte overflow) */
		map->grid[i] = malloc(sizeof(char) * (map->cols + 2));
		if (!map->grid[i])
			return 0;
		i++;
	}
	return 1;
}


int	extract_map(FILE* file, t_map* map)
{
	int i = 0;
	int j = 0;
	ssize_t r = 0;		/* FIX: getline returns ssize_t, -1 on EOF */
	size_t n = 0;
	char *buf = NULL;	/* FIX: getline needs NULL (or a malloc'd buffer) */
	r = getline(&buf, &n, file);
	/* FIX: need at least one cell plus '\n' */
	if (r < 2 || buf[r - 1] != '\n')
	{
		free(buf);
		return 0;
	}
	map->cols = r - 1;	/* FIX: don't count the '\n' as a column */
	if (!init_grid(map))
	{
		free(buf);
		return 0;
	}
	while(i < map->rows)
	{
		/* FIX: every line must have the same length and end in '\n' */
		if (r != map->cols + 1 || buf[r - 1] != '\n')
		{
			free(buf);
			return 0;
		}
		j = 0;
		while(j < map->cols)
		{
			/* FIX: only empty and obstacle chars allowed */
			if (buf[j] != map->empty && buf[j] != map->obstcl)
			{
				free(buf);
				return 0;
			}
			map->grid[i][j] = buf[j];
			j++;
		}
		map->grid[i][j] = '\n';
		map->grid[i][j + 1] = '\0';
		i++;
		if (i < map->rows)
		{
			r = getline(&buf, &n, file);
			if (r == -1)	/* FIX: fewer lines than announced */
			{
				free(buf);
				return 0;
			}
		}
	}
	/* FIX: more lines than announced */
	if (getline(&buf, &n, file) != -1)
	{
		free(buf);
		return 0;
	}
	free(buf);
	return (1);
}	

t_map*	read_map(char* path)
{
	t_map *map;
	FILE* file; 		
	file = fopen(path, "r");
	if (!file)		/* FIX: stop instead of continuing with NULL */
		return NULL;
	map = init_map();
	if (!map)
	{
		fclose(file);
		return NULL;
	}
	/* FIX: stop on any error instead of printing and carrying on */
	if (!extract_firstline(file, map) || !extract_map(file, map))
	{
		fclose(file);
		free_map(map);
		return NULL;
	}
	fclose(file);
	return map;	
}

t_valsqr	find_big_sq(t_map* map)
{
	t_valsqr square = {0};	/* FIX: defined result when no empty cell */
	int x_start = 0;
	int y_start = 0;
	int bsq = 0;
	int sq = 0;
	int vsq = 1;
	int i = 0;
	while(y_start < map->rows)
	{
		while (x_start < map->cols)
		{
			while (vsq && y_start + sq < map->rows && x_start + sq < map->cols)
			{
				while (i <= sq && vsq)
				{
					if (map->grid[y_start + i][x_start + sq ] == map->obstcl)
						vsq = 0;
					if (map->grid[y_start + sq ][x_start + i] == map->obstcl)
						vsq = 0;
					i++;
				}
				if (vsq)
					sq++;
				i = 0;
			}
			if (bsq < sq)
			{
				bsq = sq;
				square.x_start = x_start;
			       	square.x_end = x_start + sq;
				square.y_start = y_start;
				square.y_end = y_start + sq;
			}	
			sq = 0;
			x_start++;
			vsq = 1;
		}
		x_start = 0;
		y_start++;
	}
	return square;
}

void	fill_map(t_map *map, t_valsqr square)
{
	int x_start = square.x_start;
	int y_start = square.y_start;
	int i = 0;
	while(y_start < square.y_end)
	{
		while(x_start < square.x_end)
		{
			map->grid[y_start][x_start] = map->full;
			x_start++;
		}
		x_start = square.x_start;
		y_start++;
	}
	while( i < map->rows)
	{
			fprintf(stdout, "%s", map->grid[i]);
			i++;
	}
}


int main(int argc, char **argv)
{
	t_map *map = NULL;
	t_valsqr square;
	if (argc > 2)
	{
		fprintf(stderr,"map error\n");
		return 1;	/* FIX: stop here, map would be NULL */
	}
	if (argc == 1)
	{
		printf("read from stdinput\n");
		return 1;
	}
	map = read_map(argv[1]);
	if (!map)		/* FIX: any read/validation error ends up here */
	{
		fprintf(stderr, "map error\n");
		return 1;
	}
	square = find_big_sq(map);
	fill_map(map, square);
	free_map(map);		/* FIX: free everything */
	return (0);
}
