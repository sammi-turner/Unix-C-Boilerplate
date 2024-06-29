#include "interface.h"

int main() 
{
    // Set locale for wide character output
    setlocale(LC_ALL, "");

    // append array of wide chars to a file
    append_wchar_to_file("nerds.txt", L"Hello nerds! 🤓 👋🏻");
    return 0;
}
