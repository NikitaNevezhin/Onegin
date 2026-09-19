#ifndef OneginHelpers_cpp

#define OneginHelpers_cpp

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

int     LFstrlen            (const char* s);

int     StrCount            (char* string, char symb);

void    PrintStrings        (char* strings[], int n);

int LFstrlen(const char* s) // returns length including '\n' but without '\0'
{
    assert(s);

    int i = 0;

    for (; s[i] != '\n' && s[i] != '\0'; i++)
        continue;

    if (s[i] == '\n')
        return i + 1;
    
    return i;
}

int StrCount(char* string, char symb)
{
    int count = 0;
    int length = strlen(string);

    for (int i = 0; i < length; i++)
    {
        if (string[i] == symb)
            count++;
    }

    return count;
}

void PrintStrings(char* strings[], int n)
{   
    assert(strings);

    for (int i = 0; i < n; i++)
    {       
            int length = LFstrlen(strings[i]);
            printf("[address: %p] ", strings[i]);
            putchar('<');

            for (int j = 0; j < length - 2; j++)
                fputc(strings[i][j], stdout);
            
            
            if (strings[i][length - 2] != '\r')
            {
                printf("%c%c", strings[i][length - 2], strings[i][length - 1]);
                length += 2; // for correct tabulation in last printf
            }
            
            putchar('>');
            printf("%*s %d\n", 60 - length, "Length:", length - 2); // length - 2 -> '\r\n' are not counted
    }
}

#endif
