#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

int ft_strlen(char *s1)
{
    int i = 0;
    while(s1[i])
    {
        i++;
    }
    return(i);
}

char *ft_strdup(char *s1)
{
    int len = ft_strlen(s1);
    char *ret;
    int i = 0;
    ret = malloc(sizeof(char) * len + 1);
    if(!ret)
    {
        free(ret);
        return (NULL);
    }
    while(s1[i])
    {
        ret[i] = s1[i];
        i++;
    }
    ret[i] = '\0';
    return(ret);
}

int isvalid(char *s1)
{
    int open = 0;
    int close = 0;
    int i = 0;
    while(s1[i])
    {
        if (s1[i] == ')')
        {
            close++;
            if (close > open)
                return(0);
        }
        if (s1[i] == '(')
            open++;
        i++;
    }
    return(1);
}

 
int exists(char *ar, char **solutions, int solved)
{
    int i = 0;
    int j = 0;
    if(!solutions)
        return(0);

    while(j < solved)
    {
        while(ar[i] == solutions[j][i])
        {
            if (ar[i] != solutions[j][i])
                break;
            i++;
            if (ar[i] == '\0')
                return(1);
        }
        i = 0;
        j++;
    }
    return(0);
}

void solve_rip(int removeclose, int removeopen, char *ar, int i, int len, char **solutions, int *solved)
{
    if (removeclose == 0 && removeopen == 0)
    {
        //printf("This is ar[i] %s and this is solutions %s\n", ar , solutions[i] );
        if(!exists(ar, solutions, *solved) && isvalid(ar))
        {
            solutions[*solved] = ft_strdup(ar);
            (*solved)++;
            printf("%s,\n", ar);
        }
    }
    while (i < len)
    {
        if(ar[i] == '(')
        {
            ar[i] = ' ';
            solve_rip(removeclose, removeopen - 1, ar, i + 1, len, solutions, solved);
            ar[i] = '(';
            solve_rip(removeclose, removeopen, ar, i + 1, len, solutions, solved);
        }
        if(ar[i] == ')')
        {
            ar[i] = ' ';
            solve_rip(removeclose - 1, removeopen, ar, i + 1, len, solutions, solved);
            ar[i] = ')';
            solve_rip(removeclose, removeopen, ar, i + 1, len, solutions, solved);
        }
        i++;
    }
}

int main(int argc, char **argv)
{
    int removeopen = 0;
    int removeclose = 0;
    int nb;
    int i = 0;
    char *solutions[200];
    while(argv[1][i])
    {
        if(argv[1][i] == '(')
            removeopen++;
        if(argv[1][i] == ')')
        {
            if (removeopen == 0)
                removeclose++;
            else
                removeopen--;
        }
        i++;
    }
    solve_rip(removeclose, removeopen, argv[1], 0, i, solutions, &nb);
}