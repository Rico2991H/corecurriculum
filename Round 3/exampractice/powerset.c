#include <stdio.h>

void printSubset(char set[], int subset[], int n)
{
    int i = 0;
    printf("{ ");
    while (i < n)
    {
        printf("%c ", set[subset[i]]);
        i++;
    }
    printf("}\n");
}

void generatePowerset(char set[], int n, int index, int subset[], int subsetSize)
{
    if (index == n)
    {
        printSubset(set, subset, subsetSize);
        return;
    }

    // Case 1: exclude set[index]
    generatePowerset(set, n, index + 1, subset, subsetSize);

    // Case 2: include set[index]
    subset[subsetSize] = index;
    generatePowerset(set, n, index + 1, subset, subsetSize + 1);
}

int main(void)
{
    char set[] = {'a', 'b', 'c'};
    int n = 3;
    int subset[32];  // temporary storage for indices

    generatePowerset(arg, n, 0, subset, 0);
    return 0;
}



#include <stdio.h>

// helper to print one subset
void printSubset(int set[], int subset[], int subsetSize)
{
    int i = 0;
    printf("{ ");
    while (i < subsetSize)
    {
        printf("%d ", set[subset[i]]);
        i++;
    }
    printf("}\n");
}

// recursive function to find subsets summing to target
void subsetSum(int set[], int n, int index, int subset[], int subsetSize, int currentSum, int target)
{
    // base case: end of array
    if (index == n)
    {
        if (currentSum == target)
            printSubset(set, subset, subsetSize);
        return;
    }

    // Case 1: exclude current element
    subsetSum(set, n, index + 1, subset, subsetSize, currentSum, target);

    // Case 2: include current element
    subset[subsetSize] = index;
    subsetSum(set, n, index + 1, subset, subsetSize + 1, currentSum + set[index], target);
}

int main(void)
{
    int set[] = {2, 3, 5, 6, 8};
    int n = sizeof(set) / sizeof(set[0]);
    int target = 10;

    int subset[64]; // store indices of elements in current subset

    printf("Subsets that sum to %d:\n", target);
    subsetSum(set, n, 0, subset, 0, 0, target);

    return 0;
}
