#ifndef Comparators_cpp

#define Comparators_cpp

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "OneginHelpers.cpp"

typedef int (*Comparator)(const void*, const void *);

enum COMPARE_FLAGS
{
    LESS = -1,
    EQUAL = 0,
    MORE = 1
};

int   CompareDouble         (const void* a, const void* b);

int   CompareInts           (const void* value_a, const void* value_b);

void  SwapValues            (void* value1, void* value2, size_t N);

int   CompareLines          (const void* s1_value, const void* s2_value);

int   CompareLinesByEnd     (const void* s1_value, const void* s2_value);

int   CompareLinesAddress   (const void* s1_value, const void* s2_value);


int CompareDouble(const void* value_a, const void* value_b)
{   
    assert(value_a);
    assert(value_b);

    double a = *(const double*)value_a;
    double b = *(const double*)value_b;

    if (a > b)
        return MORE;
    else if (a < b)
        return LESS;
    return EQUAL;
}

int CompareInts(const void* value_a, const void* value_b)
{
    assert(value_a);
    assert(value_b);

    int a = *(const int*)value_a;
    int b = *(const int*)value_b;

    if (a > b)
        return MORE;
    else if (a < b)
        return LESS;
    return EQUAL;
}

// ONEGIN COMPARATORS

#ifdef OneginHelpers_cpp

int CompareLines(const void* s1_value, const void* s2_value)
{   
    assert(s1_value);
    assert(s2_value);

    const char* s1 = *(const char* const*)s1_value;
    const char* s2 = *(const char* const*)s2_value;
    // printf("s1 = %s", s1);
    // printf("s2 = %s", s2);

    int i = 0, j = 0;

    while(s1[i] != '\n' && s2[j] != '\n')
    {
        while (!(isalpha(s1[i])) && s1[i] != '\n')
            i++;

        while (!(isalpha(s2[j])) && s2[j] != '\n')
            j++;
        
        if (s1[i] == '\n' || s2[i] == '\n')
            break;

        int curr_s1_symb = (char)tolower(s1[i]);
        int curr_s2_symb = (char)tolower(s2[j]);

        if (curr_s1_symb != curr_s2_symb)
        {   
            return (int)(curr_s1_symb) - (int)(curr_s2_symb);
        }
        
        i++;
        j++;
    }

    return (int)(s1[i]) - (int)(s2[j]);
}

int CompareLinesByEnd(const void* s1_value, const void* s2_value)
{   
    assert(s1_value);
    assert(s2_value);

    const char* s1 = *(const char* const*)s1_value;
    const char* s2 = *(const char* const*)s2_value;
    
    int length1 = LFstrlen(s1);
    int length2 = LFstrlen(s2);

    int i = 0, j = 0;

    while((length1 - i - 1) >= 0 && (length2 - j - 1) >= 0)
    {   
        while (!(isalpha(s1[length1 - i - 1])) && (length1 - i - 1) >= 0)
            i++;

        while (!(isalpha(s2[length2 - j - 1])) && (length2 - j - 1) >= 0)
            j++;
        
        if ((length1 - i - 1) < 0 || (length2 - j - 1) < 0)
            break;

        int curr_s1_symb = tolower(s1[length1 - i - 1]);
        int curr_s2_symb = tolower(s2[length2 - j - 1]);

        if (curr_s1_symb != curr_s2_symb)
        {   
            return (int)(curr_s1_symb) - (int)(curr_s2_symb);
        }

        i++;
        j++;  
    }

    if ((length1 - i - 1) < 0 && (length2 - j - 1) >= 0)
        return LESS;

    else if ((length2 - j - 1) < 0 && (length1 - i - 1) >= 0)
        return MORE;

    return EQUAL;   
}

int CompareLinesAddress(const void* s1_value, const void* s2_value)
{
    assert(s1_value);
    assert(s2_value);

    const char* s1 = *(const char* const*)s1_value;
    const char* s2 = *(const char* const*)s2_value;

    return (int)s1 - (int)s2;
}

#endif


#endif
