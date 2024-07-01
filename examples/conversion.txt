#include "interface.h"

void print_dynamic_string(Dynamic_String* ds) 
{
    if (ds && ds->data) 
    {
        wprintf(L"String: %ls (Size: %zu)\n", ds->data, ds->size);
    } 
    else 
    {
        wprintf(L"Empty or NULL Dynamic_String\n");
    }
}

void print_dynamic_string_list(Dynamic_String_List* list) 
{
    if (list) 
    {
        wprintf(L"List (Count: %zu, Capacity: %zu):\n", list->count, list->capacity);
        for (size_t i = 0; i < list->count; i++) 
        {
            wprintf(L"  [%zu] ", i);
            print_dynamic_string(list->strings[i]);
        }
    } 
    else 
    {
        wprintf(L"Empty or NULL Dynamic_String_List\n");
    }
}

int main() 
{
    // Set locale for wide character support
    setlocale(LC_ALL, "");

    // Test dynamic_string_to_list
    wprintf(L"Testing dynamic_string_to_list:\n");
    Dynamic_String* test_string = init_dynamic_string(L"apple,banana,cherry,date");
    wprintf(L"Original ");
    print_dynamic_string(test_string);

    Dynamic_String_List* result_list = dynamic_string_to_list(test_string, L',');
    wprintf(L"Resulting ");
    print_dynamic_string_list(result_list);

    // Test list_to_dynamic_string
    wprintf(L"\nTesting list_to_dynamic_string:\n");
    Dynamic_String* reconstructed = list_to_dynamic_string(result_list, L',');
    wprintf(L"Reconstructed ");
    print_dynamic_string(reconstructed);

    // Test with different delimiter
    wprintf(L"\nTesting with different delimiter:\n");
    Dynamic_String* test_string2 = init_dynamic_string(L"Hello|World|How|Are|You");
    wprintf(L"Original ");
    print_dynamic_string(test_string2);

    Dynamic_String_List* result_list2 = dynamic_string_to_list(test_string2, L'|');
    wprintf(L"Resulting ");
    print_dynamic_string_list(result_list2);

    Dynamic_String* reconstructed2 = list_to_dynamic_string(result_list2, L' ');
    wprintf(L"Reconstructed with space delimiter ");
    print_dynamic_string(reconstructed2);

    // Clean up
    free_dynamic_string(test_string);
    free_dynamic_string_list(result_list);
    free_dynamic_string(reconstructed);
    free_dynamic_string(test_string2);
    free_dynamic_string_list(result_list2);
    free_dynamic_string(reconstructed2);

    return 0;
}