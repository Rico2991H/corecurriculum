#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_valid(char *s)
{
    int i = 0, bal = 0;
    while (s[i])
    {
        if (s[i] == '(')
            bal++;
        else if (s[i] == ')')
        {
            if (bal == 0)
                return 0;
            bal--;
        }
        i++;
    }
    return bal == 0;
}

// Check if s was already printed
int exists(char **printed, int count, char *s)
{
    for (int i = 0; i < count; i++)
        if (strcmp(printed[i], s) == 0)
            return 1;
    return 0;
}

void solve_parent(int removeclose, int removeopen, char *s1, int len, int pos, 
                  char **printed, int *printed_count)
{
    int i = pos;

    if (removeclose == 0 && removeopen == 0)
    {
        if (is_valid(s1) && !exists(printed, *printed_count, s1))
        {
            printf("%s\n", s1);
            printed[*printed_count] = strdup(s1);
            (*printed_count)++;
        }
        return;
    }

    while (i < len)
    {
        if (s1[i] == '(' && removeopen > 0)
        {
            s1[i] = ' ';
            solve_parent(removeclose, removeopen - 1, s1, len, i + 1, printed, printed_count);
            s1[i] = '(';  // backtrack
        }
        else if (s1[i] == ')' && removeclose > 0)
        {
            s1[i] = ' ';
            solve_parent(removeclose - 1, removeopen, s1, len, i + 1, printed, printed_count);
            s1[i] = ')';  // backtrack
        }
        i++;
    }
}

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 0;

    char *input = argv[1];
    int len = ft_strlen(input);

    int i = 0;
    int removeclose = 0;
    int removeopen = 0;
    int balance = 0;

    // count how many parentheses need to be removed
    while (input[i])
    {
        if (input[i] == '(')
            balance++;
        else if (input[i] == ')')
        {
            if (balance == 0)
                removeclose++;
            else
                balance--;
        }
        i++;
    }
    removeopen = balance;

    // printed strings tracker
    char *printed[2000];
    int printed_count = 0;

    solve_parent(removeclose, removeopen, input, len, 0, printed, &printed_count);

    // free allocated strings
    for (i = 0; i < printed_count; i++)
        free(printed[i]);

    return 0;
}
