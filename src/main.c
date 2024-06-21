#include "interface.h"

int main() 
{
    bool b = append_wchar_to_file("hey.txt", L"Hello! ✅");
    printf("%d\n", b);
}