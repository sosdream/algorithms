#include <stdio.h>
#include <stdlib.h>
int fibbonace(int n)
{
    if (n == 0 || n == 1) {
        return 1;
    }
    return fibbonace(n - 1) + fibbonace(n - 2);
}

int fibonace(int n)
{
    int i;
    int term1 = 0, term2 = 1;
    int result;
    for (i = 2; i < n; i++) {
        result = term2 + term1;
        term1 = term2;
        term2 = result;
    }
    return result;
}

void usage(char *pname)
{
    printf("Usage: %s generation\n",
            pname);
}

int main(int argc, char **argv){
    if (argc != 2) {
        usage(argv[0]);
        exit(1);
    }
    int generation = atoi(argv[1]);
    printf("%d generation is %d\n", generation,
                fibonace(generation));

    return 0;
}
