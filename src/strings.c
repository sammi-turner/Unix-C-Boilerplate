#include "interface.h"

/* string helper functions */

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

char* join_strings_by_char(char **arg, char c, size_t size) 
{
    size_t total_length = 0;
    for (size_t i = 0; i < size; i++) 
    {
        total_length += strlen(arg[i]) + 1;
    }
    char *result = (char*)calloc(1, total_length);
    char *current = result;
    for (size_t i = 0; i < size; i++) 
    {
        strcpy(current, arg[i]);
        current += strlen(arg[i]);
        *current = c;
        current++;
    }
    *(current - 1) = '\0';
    return result;
}

char** split_string_by_char(const char *s, char c) 
{
    size_t len = strlen(s);
    size_t num_strings = 0;
    for (size_t i = 0; i < len; i++) 
    {
        if (s[i] == c) 
        {
            num_strings++;
        }
    }
    num_strings++;
    char** result = (char**)calloc(num_strings, sizeof(char*));
    size_t start = 0;
    size_t current_string = 0;
    for (size_t i = 0; i <= len; i++) 
    {
        if (s[i] == c || i == len) 
        {
            int length = i - start;
            result[current_string] = (char*)calloc(1, length + 1);
            strncpy(result[current_string], &s[start], length);
            result[current_string][length] = '\0';
            current_string++;
            start = i + 1;
        }
    }
    return result;
}