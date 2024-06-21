#ifndef INTERFACE_H
#define INTERFACE_H

#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <wctype.h>
#include <wchar.h>
#include <time.h>
#include <math.h>

#define RED "\033[31m"
#define BRIGHT_RED "\033[91m"
#define GREEN "\033[32m"
#define BRIGHT_GREEN "\033[92m"
#define YELLOW "\033[33m"
#define BRIGHT_YELLOW "\033[93m"
#define BLUE "\033[34m"
#define BRIGHT_BLUE "\033[94m"
#define MAGENTA "\033[35m"
#define BRIGHT_MAGENTA "\033[95m"
#define CYAN "\033[36m"
#define BRIGHT_CYAN "\033[96m"
#define RESET "\033[0m"

/* list.c */

typedef struct List {
    char** list;
    int size;
} List;

List* init_list(const char** str_array);
void free_list(List* l);
int add_item(List* l, const char* s);
int update_item(List* l, const char* s, int i);
int insert_item(List* l, const char* s, int n);
int swap_items(List* l, int i, int j);
int delete_item(List* l, int n);
void print_list(List* l);
char* get_item(List* l, int n);

/* dstring.c */

typedef struct Dstring
{
    char* data;
    int size;
} Dstring;

Dstring* init_dstring(const char* str);
void free_dstring(Dstring* ds);
void append_to_dstring(Dstring* ds, const char* str);
void prepend_to_dstring(Dstring* ds, const char* str);
void replace_dstring(Dstring* ds, const char* new_data);
void substitute_in_dstring(Dstring* ds, const char* old_substr, const char* new_substr);

/* terminal.c */

void enable_single_character_input();
void restore_normal_input();
void hide_console_cursor();
void show_console_cursor();
void render_menu(const char** menu, const int size, const int count);
int select_option(const char** menu, const int size);
char* edit_prompt(const char* prompt, const char* buffer, size_t max);

/* files.c */

bool file_exists(const char* name);
wchar_t* read_file_to_wchar(const char* name);
bool write_wchar_to_file(const char* name, const wchar_t* wide_string);
bool append_wchar_to_file(const char* name, const wchar_t* wide_string);

/* misc.c */

bool is_pos_int(const wchar_t* arg);
bool is_neg_int(const wchar_t* arg);
bool is_int(const wchar_t* arg);
int to_int(const wchar_t* arg);
int is_char_digit(const wchar_t arg);
int is_char_hex_digit(const wchar_t arg);
int is_char_alpha_numeric(const wchar_t arg);
int is_char_letter(const wchar_t arg);
int is_char_lower_case(const wchar_t arg);
int is_char_upper_case(const wchar_t arg);
int is_char_punct(const wchar_t arg);
int is_char_white_space(const wchar_t arg);
int is_char_graphical(const wchar_t arg);
int pseudo(const int arg);
void seed();

#endif