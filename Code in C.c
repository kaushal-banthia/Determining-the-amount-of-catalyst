#include <stdio.h>
#include <stdlib.h>


//base case is make all top row elements of array prob 1, and all first column elements starting from index 1 as 0
//statement is max(prob[i-1][j-k]*arr[i-1][k-1]) over all i, j, and k
void main()
{
    FILE *f = fopen("input.txt", "r");
    if (f == NULL)
        return -1;
    int N, C;
    fscanf(f, "%d", &N);//number of rows
    fscanf(f, "%d", &C);//number of cols

    float arr[N][C];

    for(int i=0; i<N; i++)
        for(int j=0; j<C; j++)
            fscanf(f, "%f", &arr[i][j]);
    fclose(f);

    float prob[N+1][C+1];
    for(int i = 0; i < C+1; i++)
    {
        prob[0][i] = 1;
    }

    for (int i = 1; i < N+1; i++)
    {
        prob[i][0] = 0;
    }

    for (int i = 1; i < N+1; i++)
    {
        for (int j = 1; j < C+1; j++)
        {
            float max = 0;
            for (int k = 1; k <= j; k++)
            {
                if (max < prob[i-1][j-k]*arr[i-1][k-1])
                {
                    max = prob[i-1][j-k]*arr[i-1][k-1];
                }
            }
            prob[i][j] = max;
        }
    }


    FILE *writer = fopen("output.txt", "w");
    fprintf(writer, "%s %f", "The maximum success probability is:", prob[N][C]);

    int i = N, j = C;
    float num = prob[N][C];
    while (i > 1)
    {
        //printf("%f ", num);
        for (int x = 1; x < j; x++)
        {
            if (prob[i-1][j-x]*arr[i-1][x-1] == num)
            {
                i--;
                j-=x;
                num = prob[i][j];
                fprintf(writer, "\nComponent %d: %d ",i+1, x);
                break;
            }
        }
    }
    fprintf(writer, "\nComponent %d: %d", i, j);
}
