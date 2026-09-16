#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

typedef int (*Comparator)(const void*, const void *);

void  PrintArray            (const double* nums, int length);

int   CompareDouble         (const void* a, const void* b);

int   CompareInts           (const void* value_a, const void* value_b);

void  SwapValues            (void* value1, void* value2, size_t N);

void* GetShift              (const void* first, size_t elem_size, int shift);

int   MyDivideByEnd         (const void* nums, int left, int right, size_t elem_size, Comparator comp);

void  Myqsort               (const void* arr, int left, int right, size_t elem_size, Comparator comp);


void PrintArray(const double* nums, int length)
{
    assert(nums);

    for (int i = 0; i < length; i++)
        printf("%lf ", nums[i]);
    printf("\n");
}

void SwapValues(void* value1, void* value2, size_t N)
{
    assert(value1);
    assert(value2);

    char temp[N]; 

    memcpy(temp, value1, N);
    memcpy(value1, value2, N);
    memcpy(value2, temp, N);
    // printf("I swapped values\n");
}


int MyDivideByEnd(const void* nums, int left, int right, size_t elem_size, Comparator comp)
{
    assert(nums);
    assert(comp);

    void* main_elem = GetShift(nums, elem_size, right);

    int less_nums_index = left;

    void* curr_elem = NULL;

    for (int i = left; i <= right; i++)
    {
        curr_elem = GetShift(nums, elem_size, i);

        if (comp(curr_elem, main_elem) <= 0)
        {
            SwapValues(curr_elem, GetShift(nums, elem_size, less_nums_index), elem_size);
            less_nums_index++;
        }
    }

    return less_nums_index - 1;
}


void Myqsort(const void* nums, int left, int right, size_t elem_size, Comparator comp) //TODO: #typedef DONE
{
    assert(nums);
    assert(comp);
    // printf("Executing Myqsort...\n");
    if (left < right)
    {
        int division = MyDivideByEnd(nums, left, right, elem_size, comp);

        Myqsort(nums, left, division - 1, elem_size, comp);
        Myqsort(nums, division + 1, right, elem_size, comp); //FIXME:
    }
}

void* GetShift(const void* first, size_t elem_size, int shift)
{   
    assert(first);
    return (void*)((char*)first + elem_size * shift);
}


int CompareDouble(const void* value_a, const void* value_b)
{   
    assert(value_a);
    assert(value_b);

    double a = *(double*)value_a;
    double b = *(double*)value_b;

    if (a > b)
        return 1;
    else if (a < b)
        return -1;
    return 0;
}

int CompareInts(const void* value_a, const void* value_b)
{
    assert(value_a);
    assert(value_b);

    int a = *(int*)value_a;
    int b = *(int*)value_b;

    if (a > b)
        return 1;
    else if (a < b)
        return -1;
    return 0;
}