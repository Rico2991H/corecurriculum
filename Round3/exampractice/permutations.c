# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

void ft_swap(char *s1, char *s2)
{
    char tmp;
    tmp = *s2;
    *s2 = *s1;
    *s1 = tmp;
}
void    permutate(int r, char *ar, int l)
{
    int i = l;
    if (l == r)
    {
        i = 0;
        printf("%s\n", ar);
    }
    while (i < r)
    {
        ft_swap(&ar[l],&ar[i]);
        permutate(r, ar, l + 1);
        ft_swap(&ar[l],&ar[i]);
        i++;
    }
}


int main(int argc, char **argv)
{
    int i = 0;
    if (argc == 2)
    {
        while(argv[1][i])
        {
            i++;
        }
        permutate(i, &argv[1][0], 0);
    }
}