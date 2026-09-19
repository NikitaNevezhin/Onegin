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

int   CompareLines          (const void* s1_value, const void* s2_value);

int   CompareLinesByEnd     (const void* s1_value, const void* s2_value);

int   CompareLinesAddress   (const void* s1_value, const void* s2_value);


// ONEGIN COMPARATORS



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
        SkipNotLetters(s1, &i, FORWARDS);
        SkipNotLetters(s2, &j, FORWARDS);

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
        SkipNotLetters(s1, &i, BACKWARDS);
        SkipNotLetters(s2, &j, BACKWARDS);
        
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
