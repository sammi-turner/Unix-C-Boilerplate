#include "interface.h"

void print_dwc_array(Dynamic_Wchar_Array *dwa) 
{
    wprintf(L"String: %ls\n", dwa->data);
    wprintf(L"Size: %d\n", dwa->size);
}

int main() 
{
    setlocale(LC_ALL, "");  // Set locale for wide character output

    // Test init_dwc_array
    Dynamic_Wchar_Array *dwa = init_dwc_array(L"Hello 世界 🔥");
    wprintf(L"After initialization:\n");
    print_dwc_array(dwa);

    // Test append_to_dwc_array
    append_to_dwc_array(dwa, L" How are you?");
    wprintf(L"\nAfter appending:\n");
    print_dwc_array(dwa);

    // Test prepend_to_dwc_array
    prepend_to_dwc_array(dwa, L"Greetings! ");
    wprintf(L"\nAfter prepending:\n");
    print_dwc_array(dwa);

    // Test replace_dwc_array
    replace_dwc_array(dwa, L"This is a new string.");
    wprintf(L"\nAfter replacing:\n");
    print_dwc_array(dwa);

    // Test substitute_in_dwc_array
    substitute_in_dwc_array(dwa, L"new", L"modified");
    wprintf(L"\nAfter substitution:\n");
    print_dwc_array(dwa);

    // Test free_dwc_array
    free_dwc_array(dwa);
    wprintf(L"\nDynamic_Wchar_Array freed.\n");

    return 0;
}