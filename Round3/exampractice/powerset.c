/*print all possible sum from the first number in a string of numbers "10 2 4 4 6 2 3"*/
/**/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void    solve_subset(int *arr, int size, int l, int r)
{
    int sum = 0;
    int *buf = malloc(sizeof(int) * size);
    int j = r;
    int i = l;
    if (l == size)
    {
        return;
    }
    sum = arr[l];
    while (j < size)
    {
        sum += arr[j];
        //printf(" l = %d not part of solution %d ,\n",l,  arr[r]);
        solve_subset(arr, size, l + 1, r);
        if (sum == 10)
        {
            while(i < 10)
            {
                printf(" %d whutt %d ,", l, arr[i]);
                i++;
            }
            printf("\n");
            sum -= arr[r];
            i = l;
        }
        j++;
    }   
}

int *argv_to_int_array(int argc, char **argv, int *size)
{
    int i = 0;
    int *arr;

    *size = argc - 1;              // how many numbers we expect
    arr = malloc(sizeof(int) * (*size));
    if (!arr)
        return NULL;

    while (i < *size)
    {
        arr[i] = atoi(argv[i + 1]);  // convert & store
        i++;
    }

    return arr;
}

int main(int argc, char **argv)
{
    int size;
    int *nums = argv_to_int_array(argc, argv, &size);

    if (!nums)
        return 1;

    solve_subset(nums, size, 1, 1 );

    free(nums);
    return 0;
}