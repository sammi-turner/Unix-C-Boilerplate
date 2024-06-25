#include "interface.h"

int main() 
{
    // Set locale for wide character output
    setlocale(LC_ALL, "");

    // Initialize a wide character string array
    const wchar_t* hello[] = 
    {
        L"Hello",
        L"世界",
        L"안녕하세요",
        L"Привет",
        NULL
    };

    // Create a new Wchar_Array_List
    Wchar_Array_List *wal = init_list(hello);

    // Print the initial list
    wprintf(L"Initial list:\n");
    print_list(wal);

    // Add a new item
    add_item(wal, L"Bonjour");
    wprintf(L"\nAfter adding an item:\n");
    print_list(wal);

    // Update an item
    update_item(wal, L"Updated", 1);
    wprintf(L"\nAfter updating an item:\n");
    print_list(wal);

    // Insert an item
    insert_item(wal, L"Inserted", 2);
    wprintf(L"\nAfter inserting an item:\n");
    print_list(wal);

    // Swap items
    swap_items(wal, 0, 3);
    wprintf(L"\nAfter swapping items:\n");
    print_list(wal);

    // Delete an item
    delete_item(wal, 1);
    wprintf(L"\nAfter deleting an item:\n");
    print_list(wal);

    // Get an item
    wchar_t* item = get_item(wal, 1);
    wprintf(L"\nRetrieved item: %ls\n", item);
    free(item);

    // Free the Wchar_Array_List
    free_list(wal);
    return 0;
}