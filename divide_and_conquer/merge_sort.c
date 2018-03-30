#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct array {
    int item_num;
    int data[];
} array_t;
array_t *combine_sort(array_t *array1, array_t *array2)
{
    int i = 0,j = 0;
    array_t *new_array;
    int all_num = array1->item_num + array2->item_num;
    new_array = malloc(sizeof(*new_array) + all_num * sizeof(int));
    new_array->item_num = 0;

    while (all_num--) {
        if (i < array1->item_num && j < array2->item_num) {
            new_array->data[new_array->item_num++] =
                        array1->data[i] > array2->data[j] ?
                                        array1->data[i++] :
                                        array2->data[j++] ;
        } else if (i < array1->item_num) {
            new_array->data[new_array->item_num++] =
                            array1->data[i++];
        } else {
            new_array->data[new_array->item_num++] =
                        array2->data[j++];
        }
    }
#if 0
    while (all_num--) {
        if (i >= array1->item_num) {
            memcpy(&new_array->data[new_array->item_num],
                        &array2->data[j], array2->item_num - j);
            new_array->item_num = all_num;
            break;
        } else {
            memcpy(&new_array->data[new_array->item_num],
                        &array1->data[j], array1->item_num - i);
            new_array->item_num = all_num;
            break;
        }
        if (array1->data[i] > array2->data[j]) {
            new_array->data[new_array->item_num++] = array1->data[i++];
        } else {
            new_array->data[new_array->item_num++] = array2->data[j++];
        }
    }
#endif
    return new_array;
}

array_t *merge_sort(int *array, int low, int high)
{
    array_t *array1, *array2, *new_array;
    int mid = (low + high) / 2;
    if (low == high) {
        new_array = malloc(sizeof(*new_array) + sizeof(int));
        new_array->item_num = 1;
        new_array->data[0] = array[low];
        return new_array;
    } else {
        array1 = merge_sort(array, low, mid);
        array2 = merge_sort(array, mid + 1, high);
        new_array = combine_sort(array1, array2);
        free(array1);
        free(array2);
        return new_array;
    }
}
void print_array(int *array, int low, int high)
{
    int i;
    printf("Array: [");
    for (i = low; i <= high; i++) {
        printf("%d,", array[i]);
    }
    printf("]\n");
}

void print_array_withresult(array_t *array)
{
    int i;
    for (i = 0; i < array->item_num; i++) {
        printf("%d ", array->data[i]);
    }

    putchar('\n');
}

int main()
{
    array_t *new_array;
    int array[] = {3,2,34,3,3,5,5,4,62,64,6,56};
    int size = sizeof(array)/sizeof(int);
    new_array = merge_sort(array, 0, size - 1);
    print_array(array, 0, size - 1);
    print_array_withresult(new_array);
    free(new_array);
}
