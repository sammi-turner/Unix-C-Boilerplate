#include "interface.h"

bool is_sqlite_installed()
{
    char *result = shell("sqlite3 --version", 256);
    return (result[0] == '3');
}

char* create_key_value_table(const char* t)
{
    char* query = NULL;
    size_t query_size;
    char* result;
    query_size = snprintf(NULL, 0, "CREATE TABLE %s (key VARCHAR(50) PRIMARY KEY, value TEXT);", t) + 1;
    query = calloc(1, query_size);
    if (query == NULL)
    {
        return NULL;
    }
    snprintf(query, query_size, "CREATE TABLE %s (key VARCHAR(50) PRIMARY KEY, value TEXT);", t);
    result = execute_sqlite_command(query, t);
    free(query);
    return result;
}

bool table_contains_key(const char* t, const char* k)
{
    char *all = select_all_keys(t);
    char* token = strtok(all, "\n");
    while (token != NULL) 
    {
        if (strcmp(token, k) == 0) 
        {
            return true;
        }
        token = strtok(NULL, "\n");
    }
    return false;
}

char* execute_sqlite_command(const char* query, const char* table)
{
    char* command = NULL;
    char* output = NULL;
    char* temp = NULL;
    FILE* fp = NULL;
    size_t command_size;
    size_t output_size = 0;
    size_t buffer_size;
    command_size = snprintf(NULL, 0, COMMAND_FORMAT, query, table) + 1;
    command = calloc(1, command_size);
    if (command == NULL)
    {
        return NULL;
    }
    snprintf(command, command_size, COMMAND_FORMAT, query, table);
    fp = popen(command, "r");
    if (fp == NULL)
    {
        free(command);
        return NULL;
    }
    buffer_size = command_size;
    output = calloc(1, buffer_size);
    if (output == NULL)
    {
        pclose(fp);
        free(command);
        return NULL;
    }
    while (fgets(output + output_size, buffer_size - output_size, fp) != NULL)
    {
        output_size += strlen(output + output_size);
        if (output_size + 1 >= buffer_size)
        {
            buffer_size *= 2;
            temp = realloc(output, buffer_size);
            if (temp == NULL)
            {
                free(output);
                pclose(fp);
                free(command);
                return NULL;
            }
            output = temp;
        }
    }
    pclose(fp);
    free(command);
    return output;
}

char* insert_key_value_pair(const char* t, const char* k, const char* v)
{
    char* query = NULL;
    size_t query_size;
    char* result;
    query_size = snprintf(NULL, 0, INSERT_QUERY, t, k, v) + 1;
    query = calloc(1, query_size);
    if (query == NULL)
    {
        return NULL;
    }
    snprintf(query, query_size, INSERT_QUERY, t, k, v);
    result = execute_sqlite_command(query, t);
    free(query);
    return result;
}

char* select_all_keys(const char* t)
{
    char* query = NULL;
    size_t query_size;
    char* result;
    query_size = snprintf(NULL, 0, SELECT_ALL_KEYS_QUERY, t) + 1;
    query = calloc(1, query_size);
    if (query == NULL)
    {
        return NULL;
    }
    snprintf(query, query_size, SELECT_ALL_KEYS_QUERY, t);
    result = execute_sqlite_command(query, t);
    free(query);
    return result;
}

char* select_all_values(const char* t)
{
    char* query = NULL;
    size_t query_size;
    char* result;
    query_size = snprintf(NULL, 0, SELECT_ALL_VALUES_QUERY, t) + 1;
    query = calloc(1, query_size);
    if (query == NULL)
    {
        return NULL;
    }
    snprintf(query, query_size, SELECT_ALL_VALUES_QUERY, t);
    result = execute_sqlite_command(query, t);
    free(query);
    return result;
}

char* delete_key_value_pair(const char* t, const char* k)
{
    char* query = NULL;
    size_t query_size;
    char* result;
    query_size = snprintf(NULL, 0, DELETE_QUERY, t, k) + 1;
    query = calloc(1, query_size);
    if (query == NULL)
    {
        return NULL;
    }
    snprintf(query, query_size, DELETE_QUERY, t, k);
    result = execute_sqlite_command(query, t);
    free(query);
    return result;
}

char* select_all_pairs(const char* t)
{
    char* query = NULL;
    size_t query_size;
    char* result;
    query_size = snprintf(NULL, 0, SELECT_ALL_QUERY, t) + 1;
    query = calloc(1, query_size);
    if (query == NULL)
    {
        return NULL;
    }
    snprintf(query, query_size, SELECT_ALL_QUERY, t);
    result = execute_sqlite_command(query, t);
    free(query);
    return result;
}

char* select_row_from_key(const char* t, const char* k)
{
    char* query = NULL;
    size_t query_size;
    char* result;
    query_size = snprintf(NULL, 0, SELECT_ROW_QUERY, t, k) + 1;
    query = calloc(1, query_size);
    if (query == NULL)
    {
        return NULL;
    }
    snprintf(query, query_size, SELECT_ROW_QUERY, t, k);
    result = execute_sqlite_command(query, t);
    free(query);
    return result;
}

char* select_value_from_key(const char* t, const char* k)
{
    char* query = NULL;
    size_t query_size;
    char* result;
    query_size = snprintf(NULL, 0, SELECT_VALUE_QUERY, t, k) + 1;
    query = calloc(1, query_size);
    if (query == NULL)
    {
        return NULL;
    }
    snprintf(query, query_size, SELECT_VALUE_QUERY, t, k);
    result = execute_sqlite_command(query, t);
    free(query);
    return result;
}