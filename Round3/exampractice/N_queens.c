# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>


void    solve_nqueens(int n, int r, int *col, int *pos, int *adiag, int *mdiag)
{
    int i = 0;
    int c = 0;

    if (r == n)
    {
        while (i < n)
        {
            //printf("%d i and %d n\n", i, n);
            printf("%d,", pos[i]);
            i++;
        }
        printf("\n");
        return;
    }

    while (c < n)
    {
        int a = c - r + (n - 1);
        int m = c + r;

        if (!col[c] && !adiag[a] && !mdiag[m])
        {
            col[c] = 1;
            adiag[a] = 1;
            mdiag[m] = 1;
            pos[r] = c;
            //printf(" r %d = a solution on col %d\n", r, c);
            solve_nqueens(n, r + 1, col, pos, adiag, mdiag);
            col[c] = 0;
            adiag[a] = 0;
            mdiag[m] = 0;
            //solve_nqueens(n, r + 1, col, pos, adiag, mdiag);
        }
     c++;   
    }
}

int main()
{
    int n = 4;
    int *col = calloc(n, sizeof(int));
    int *pos = calloc(n, sizeof(int));
    int *adiag = calloc((2 * n - 1), sizeof(int));
    int *mdiag = calloc((2 * n - 1), sizeof(int));
    solve_nqueens(n, 0, col, pos, adiag, mdiag);
}