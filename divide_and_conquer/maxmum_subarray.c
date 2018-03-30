#include <stdio.h>

struct subarray_result {
    int max_value;
    int low;
    int high;
};

struct subarray_result combine_subarray(int *array,
                int low_indices, int mid_indices, int high_indices)
{
    int i, max = 0, left_max = 0, right_max = 0;
    int result_low, result_high;
    struct subarray_result result;
    for (i = mid_indices; i >= low_indices; i--) {
        max += array[i];
        if (max > left_max) {
            left_max = max;
            result_low = i;
        }
    }
    max = 0;
    for (i = mid_indices + 1; i <= high_indices; i++) {
        max += array[i];
        if (max > right_max) {
            right_max = max;
            result_high = i;
        }
    }

    max = left_max + right_max;
    result.max_value = max;
    result.low = result_low;
    result.high = result_high;
    return result;
}


struct subarray_result search_maxmum_subarray(int *array, int low_indices, int high_indices)
{
    struct subarray_result left_result, right_result, cross_result;
    int mid_indices = (low_indices + high_indices) / 2;
    if (low_indices == high_indices) {
        left_result.max_value = array[low_indices];
        left_result.low = low_indices;
        left_result.high = low_indices;
        return left_result;
    } else {
        left_result = search_maxmum_subarray(array, low_indices, mid_indices);
        right_result = search_maxmum_subarray(array, mid_indices + 1, high_indices);
        /* combine result */
        cross_result = combine_subarray(array, low_indices, mid_indices, high_indices);
        if (left_result.max_value > right_result.max_value &&
                        left_result.max_value > cross_result.max_value) {
            return left_result;
        } else if (right_result.max_value > left_result.max_value &&
                    right_result.max_value > cross_result.max_value) {
            return right_result;
        } else
            return cross_result;
    }
}

struct subarray_result search_maxmun_nonrecurency(int *array, int size)
{
    int i;
    int max = 0, tmp_record = 0;
    int high, low;
    tmp_record = array[0];
    for (i = 1; i < size - 1; i++) {
        tmp_record = tmp_record > array[i] ? tmp_record : array[i];
        printf("[%d]:%d count: %d max:%d \n", i, array[i], tmp_record, max);
        if (tmp_record > max) {
            max = tmp_record;
            high = i;
        }
    }
    tmp_record = 0;
    for (i = high; i >= 0; i--) {
        tmp_record += array[i];
        if (tmp_record > max) {
            max = tmp_record;
            low = i;
        }
    }
    struct subarray_result result;
    result.max_value = max;
    result.low = low;
    result.high = high;
    return result;
}

struct subarray_result max_subarray_normal(int *array, int size)
{
    int i, j;
    int tmp_max = 0;
    struct subarray_result result = {0,0,0};
    for (i = 0; i < size; i++) {
        tmp_max = 0;
        for (j = i; j < size; j++) {
            tmp_max += array[j];
            if (result.max_value < tmp_max) {
                result.max_value = tmp_max;
                result.low = i;
                result.high = j;
            }
        }
    }
    return result;
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

void print_array_withresult(int *array, struct subarray_result *result)
{
    int i;
    printf("sum: %d\n", result->max_value);
    for (i = result->low; i <= result->high; i++) {
        printf("%d ", array[i]);
    }

    putchar('\n');
}

int main()
{
    struct subarray_result result;
    int array[] = {-2,32,4,23,9,-2,2,-89,65,4,-82};
    int size = sizeof(array)/sizeof(int);
    //result = search_maxmum_subarray(array, 0, size - 1);
    //result = max_subarray_normal(array, size);
    result = search_maxmun_nonrecurency(array, size);
    print_array(array, 0, size - 1);
    print_array_withresult(array, &result);
    return 0;
}
