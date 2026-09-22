#ifndef COMPARATORS_CPP

#define COMPARATORS_CPP

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

    const LineInfo* s1_info = *(const LineInfo* const*)s1_value;
    const LineInfo* s2_info = *(const LineInfo* const*)s2_value;
    // printf("s1 = %s", s1);
    // printf("s2 = %s", s2);

    int i = 0, j = 0;

    while(s1_info->line[i] != '\n' && s2_info->line[j] != '\n')
    {
        SkipNotLetters(s1_info->line, &i, FORWARDS);
        SkipNotLetters(s2_info->line, &j, FORWARDS);

        while (!(isalpha(s2_info->line[j])) && s2_info->line[j] != '\n')
            j++;
        
        if (s1_info->line[i] == '\n' || s2_info->line[i] == '\n')
            break;

        int curr_s1_symb = (char)tolower(s1_info->line[i]);
        int curr_s2_symb = (char)tolower(s2_info->line[j]);

        if (curr_s1_symb != curr_s2_symb)
        {   
            return (int)(curr_s1_symb) - (int)(curr_s2_symb);
        }
        
        i++;
        j++;
    }

    return (int)(s1_info->line[i]) - (int)(s2_info->line[j]);
}

int CompareLinesByEnd(const void* s1_value, const void* s2_value)
{   
    assert(s1_value);
    assert(s2_value);

    const LineInfo* s1_info = *(const LineInfo* const*)s1_value;
    const LineInfo* s2_info = *(const LineInfo* const*)s2_value;
    
    int length1 = s1_info->length;
    int length2 = s2_info->length;

    int i = 0, j = 0;

    while((length1 - i - 1) >= 0 && (length2 - j - 1) >= 0)
    {   
        SkipNotLetters(s1_info->line, &i, BACKWARDS);
        SkipNotLetters(s2_info->line, &j, BACKWARDS);
        
        if ((length1 - i - 1) < 0 || (length2 - j - 1) < 0)
            break;

        int curr_s1_symb = tolower(s1_info->line[length1 - i - 1]);
        int curr_s2_symb = tolower(s2_info->line[length2 - j - 1]);

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

    const LineInfo* s1_info = *(const LineInfo* const*)s1_value;
    const LineInfo* s2_info = *(const LineInfo* const*)s2_value;

    return (int)s1_info->line - (int)s2_info->line;
}

#endif
