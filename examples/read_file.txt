#include "interface.h"

int main() 
{
    // Set locale for wide character output
    setlocale(LC_ALL, "");

    // read file into array of wide chars
    wchar_t *r = read_file_to_wchar("test.txt");

    // print out contents of wide char array
    wprintf(L"%ls\n", r);
    return 0;
}