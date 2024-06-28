#include "interface.h"

bool compare_lengths(const char *str1, const char *str2) 
{
    return strlen(str1) == strlen(str2);
}

bool compare_first_char(const char *str1, const char *str2) 
{
    return str1[0] == str2[0];
}

bool compare_full_strings(const char *str1, const char *str2) 
{
    return strcmp(str1, str2) == 0;
}

bool compare_optimized(const char *str1, const char *str2) 
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    if (len1 != len2) 
    {
        return false;
    }
    return strcmp(str1, str2) == 0;
}