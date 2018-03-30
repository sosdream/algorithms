#include <stdio.h>
#include <stdlib.h>
#define ERROR 0xFFFFFFE1
struct result {
    int x;
    int y;
};
void print_array(int *array, int low, int high)
{
    int i;
    printf("Array: [");
    for (i = low; i <= high; i++) {
        printf("%d,", array[i]);
    }
    printf("]\n");
}
int binary_search(int *array, int low, int high, int key)
{
    int mid = (low + high)/2;
    if (low == mid) {
        if (array[mid] == key) {
            return low;
        } else {
            return ERROR;
        }
    }
    if (array[mid] >= key) {
        return binary_search(array, low, mid, key);
    } else {
        return binary_search(array, mid + 1, high, key);
    }
    
}

void search_sum_term(int *array, int size, int m)
{
    int i, j, swap, complement;
    /* sort */
    for (i = 1; i < size; i++) {
        for (j = i; j > 0; j--) {
            if (array[j] < array[j - 1]) {
                swap = array[j];
                array[j] = array[j - 1];
                array[j - 1] = swap;
            }
        }
    }
    print_array(array, 0, size - 1);
    for (i = 0; i < size; i++) {
        int position;
        complement = m - array[i];
        position = binary_search(array, 0, size - 1, complement);
        if (position != ERROR) {
            printf("[%d]:%d + [%d]:%d = %d\n", i, array[i],
                            position, array[position],
                            m);
        }
    }
}

void usage(char *pname)
{
    printf("Usage: %s value\n",
                pname);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        usage(argv[0]);
        exit(1);
    }
    int m = atoi(argv[1]);
    int array[] = {1,2,4,54,5,7,5,3,46,34,78,8,23,6,6,21,1,32,6,3};
    int size = sizeof(array)/sizeof(int);
    search_sum_term(array, size, m);
    return 0;
}
