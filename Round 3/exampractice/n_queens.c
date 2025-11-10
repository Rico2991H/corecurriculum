/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:54:53 by rhoogend          #+#    #+#             */
/*   Updated: 2025/11/10 16:04:01 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

void print_matrix(int rows, int cols, int chessboard[rows][cols]) 
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", chessboard[i][j]);
        }
        printf("\n");
    }
}

int     fill_board(int n, int i, int chessboard[n][n], int queen)
{
    int row = n;
    int col = n;
    int j = 0;
    int i = 0;
        while( i < row )
        {
                chessboard[i][0] = 1;
            if (j < col)
            {
                    chessboard[0][j] = 1;
                j++;
            }
            i++;
            chessboard[i][j] = 1;
        }
    return (1);
}

void    n_queens(int n, int chessboard[n][n])
{
    int i = 0;
    fill_board(n, i, chessboard, queen);
    print_matrix(n, n, chessboard);
    printf("\n");
}

int main(int argc, char **argv)
{
    
    if (argc == 2 && (argv[1][0] >= '0' && argv[1][0] <= '9'))
    {   
        int n = atoi(argv[1]);
        int chessboard [n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                chessboard[i][j] = 0;
        n_queens(n, chessboard);
    }
}