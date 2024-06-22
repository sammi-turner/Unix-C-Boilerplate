#include "interface.h"

/* Terminal I/O operations */

void enable_single_character_input() 
{
    struct termios oldSettings, newSettings;
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
}

void restore_normal_input() 
{
    struct termios oldSettings;
    tcgetattr(STDIN_FILENO, &oldSettings);
    oldSettings.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
}

void hide_console_cursor() 
{
    printf("\x1B[?25l");
    fflush(stdout);
}

void show_console_cursor() 
{
    printf("\x1B[?25h");
    fflush(stdout);
}

void render_menu(const wchar_t *menu[], size_t size, size_t count)
{
    setlocale(LC_ALL, "");
    system("clear");
    wprintf(L"\n    %ls\n\n", menu[0]);
    for (size_t i = 1; i < size; i++) 
    {
        if (i == count) 
        {
            wprintf(L"  > %ls\n", menu[i]);
        } 
        else 
        {
            wprintf(L"    %ls\n", menu[i]);
        }
    }
    wprintf(L"\n");
}

int select_option(const wchar_t *menu[], size_t size)
{
    enable_single_character_input();
    hide_console_cursor();
    size_t value = 1;
    int ch;
    render_menu(menu, size, value);
    while ((ch = getwchar()) != L'\n')
    {
        if (ch == 27) 
        {
            getwchar();
            switch (getwchar()) 
            {
                case 'A':
                    value--;
                    if (value == 0) 
                    {
                        value = (size - 1);
                    }
                    render_menu(menu, size, value);
                    break;
                case 'B':
                    value++;
                    if (value == size) 
                    {
                        value = 1;
                    }
                    render_menu(menu, size, value);
                    break;
            }
        }
    }
    show_console_cursor();
    return value;
}

char* edit_prompt(const char *prompt, const char *buffer, size_t max) 
{
    printf("%s", prompt);
    if (strlen(prompt) != 0) 
    {
        printf(" ");
    }
    struct termios oldSettings, newSettings;
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
    char* s = malloc(max + 1);
    strncpy(s, buffer, max);
    s[max] = '\0';
    printf("%s", s);
    size_t cursorPos = strlen(s);
    char c;
    while ((c = getchar()) != '\n') 
    {
        if (c == 127 || c == 8) 
        {
            if (cursorPos > 0) 
            {
                memmove(&s[cursorPos - 1], &s[cursorPos], strlen(s) - cursorPos + 1);
                cursorPos--;
                printf("\b \b");
                for (size_t i = cursorPos; i < strlen(s); i++) 
                {
                    printf("%c", s[i]);
                }
                printf(" \b");
                for (size_t i = cursorPos; i < strlen(s); i++) 
                {
                    printf("\b");
                }
            }
        } 
        else if (c == 27) 
        {
            if ((c = getchar()) == 91) 
            {
                c = getchar();
                if (c == 68 && cursorPos > 0) 
                {
                    cursorPos--;
                    printf("\b");
                } 
                else if (c == 67 && cursorPos < strlen(s)) 
                {
                    cursorPos++;
                    printf("%c", s[cursorPos - 1]);
                }
            }
        } 
        else if (cursorPos < max) 
        {
            memmove(&s[cursorPos + 1], &s[cursorPos], strlen(s) - cursorPos + 1);
            s[cursorPos] = c;
            cursorPos++;
            for (size_t i = cursorPos - 1; i < strlen(s); i++) 
            {
                printf("%c", s[i]);
            }
            for (size_t i = cursorPos; i < strlen(s); i++) 
            {
                printf("\b");
            }
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
    printf("\n");
    return s;
}