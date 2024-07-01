#include "interface.h"

int main() 
{
    // Set locale for wide character output
    setlocale(LC_ALL, "");

    // Compare optimised
    char str0[] = "Hello";
    char str1[] = "Hello";
    char str2[] = "hello";
    bool t0 = compare_optimized(str0, str1);
    bool t1 = compare_optimized(str0, str2);
    printf("Comparison values are %d and %d\n", t0, t1);

    // Join strings by char
    char *arr[] = {"Oh", "hi", "Mark"};
    char *r0 = join_strings_by_char(arr, ' ', 3);
    printf("%s\n", r0);

    // Split strings by char
    char **r1 = split_string_by_char(r0, ' ');
    printf("%s\n%s\n%s\n", r1[0], r1[1], r1[2]);
    return 0;
}