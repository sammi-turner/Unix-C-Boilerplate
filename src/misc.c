#include "interface.h"

/* Pseudo-random number generation */

int pseudo(const int arg) 
{
    int result = 0;
    if (arg > 1) 
    {
        result = (rand() % arg) + 1;
    }
    return result;
}

void seed() 
{
    srand((unsigned int)time(NULL));
}

/* Wide char arrays representing integers */

int to_int(const wchar_t *arg) 
{
    return (int)wcstol(arg, NULL, 10);
}

bool is_int(const wchar_t *arg) 
{
    wchar_t* endptr;
    wcstol(arg, &endptr, 10);
    return (*endptr == L'\0');
}

bool is_pos_int(const wchar_t *arg) 
{
    if (is_int(arg)) 
    {
        int n = to_int(arg);
        return n > 0;
    }
    return false;
}

bool is_neg_int(const wchar_t *arg) 
{
    if (is_int(arg)) 
    {
        int n = to_int(arg);
        return n < 0;
    }
    return false;
}

/* Wide char classification */

bool is_wchar_digit(const wchar_t arg)
{
    return (isdigit(arg) > 0);
}

bool is_wchar_hex_digit(const wchar_t arg)
{
    return (isxdigit(arg) > 0);
}

bool is_wchar_alpha_numeric(const wchar_t arg)
{
    return (isalnum(arg) > 0);
}

bool is_wchar_letter(const wchar_t arg)
{
    return (isalpha(arg) > 0);
}

bool is_wchar_lower_case(const wchar_t arg)
{
    return (islower(arg) > 0);
}

bool is_wchar_upper_case(const wchar_t arg)
{
    return (isupper(arg) > 0);
}

bool is_wchar_punct(const wchar_t arg)
{
    return (ispunct(arg) > 0);
}

bool is_wchar_white_space(const wchar_t arg)
{
    return (isspace(arg) > 0);
}

bool is_wchar_graphical(const wchar_t arg)
{
    return (isgraph(arg) > 0);
}