#include <stdio.h>

void selection_sort(int *array, int length);
void print_array(int *array, int length);
void bubble_sort(int *array, int length);
void merge_sort(int *array, int first, int last);
void merge(int *array, int first, int middle, int last);

int main(void)
{
    // Selection Sort
    int array1[] = {23, 87, 12, 45, 98, 34, 67, 10, 56, 77};
    int size = sizeof(array1) / sizeof(array1[0]);
    printf("Original Array: ");
    print_array(array1, size);
    selection_sort(array1, size);
    printf("\n");
    printf("Sorted Array: ");
    print_array(array1, size);

    // Bubble Sort
    int array2[] = {5, 99, 42, 18, 64, 73, 81, 27, 33, 50};
    size = sizeof(array2) / sizeof(array2[0]);
    printf("\nOriginal Array: ");
    print_array(array2, size);
    bubble_sort(array2, size);
    printf("\n");
    printf("Sorted Array: ");
    print_array(array2, size);
    bubble_sort(array2, size);

    // Merge Sort
    int array3[] = {91, 6, 38, 79, 25, 58, 44, 16, 89, 72};
    size = sizeof(array3) / sizeof(array3[0]);
    printf("\nOriginal Array: ");
    print_array(array3, size);
    merge_sort(array3, 0, size - 1);
    printf("\n");
    printf("Sorted Array: ");
    print_array(array3, size);

    return 0;
}

void print_array(int *array, int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
}

void selection_sort(int *array, int length)
{
    for (int i = 0; i < length; i++)
    {
        int minimun = i;
        for (int j = i + 1; j < length; j++)
        {
            if (array[j] < array[minimun])
            {
                minimun = j;
            }
        }
        int aux = array[i];
        array[i] = array[minimun];
        array[minimun] = aux;
    }
}

void bubble_sort(int *array, int length)
{
    for (int i = length; i >= 0; i--)
    {
        int changes = 0;
        for (int j = 1; j < i; j++)
        {
            if (array[j] < array[j - 1])
            {
                int aux = array[j];
                array[j] = array[j - 1];
                array[j - 1] = aux;
                changes++;
            }
        }
        if (i == length && changes == 0)
        {
            printf("\nArray is already sorted!");
            return;
        }
    }
}

void merge_sort(int *array, int first, int last)
{
    if (first >= last)
        return;

    int middle = first + (last - first) / 2;
    merge_sort(array, first, middle);
    merge_sort(array, middle + 1, last);
    merge(array, first, middle, last);
}

void merge(int *array, int first, int middle, int last)
{
    int left_size = middle - first + 1;
    int right_size = last - middle;

    int left_temp[left_size];
    int right_temp[right_size];

    for (int i = 0; i < left_size; i++)
    {
        left_temp[i] = array[first + i];
    }

    for (int i = 0; i < right_size; i++)
    {
        right_temp[i] = array[middle + 1 + i];
    }

    int i, j, k;
    i = j = 0;
    k = first;

    while (i < left_size && j < right_size)
    {
        if (left_temp[i] <= right_temp[j])
        {
            array[k] = left_temp[i];
            i++;
        }
        else
        {
            array[k] = right_temp[j];
            j++;
        }
        k++;
    }

    while (i < left_size)
    {
        array[k] = left_temp[i];
        i++;
        k++;
    }

    while (j < right_size)
    {
        array[k] = right_temp[j];
        j++;
        k++;
    }
}
