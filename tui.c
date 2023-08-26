#include "tui.h"

void get_terminal_size(tools_t *tools)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    tools->terminal_rows = w.ws_row;
    tools->terminal_cols = w.ws_col;
}

void  set_tui_background_color(int color, void *tools)
{ 
    const char *colors[] = {
        "\e[1;41m",
        "\e[1;42m",
        "\e[1;43m",
        "\e[1;44m",
        "\e[1;45m",
        "\e[1;46m",
        "\e[1;47m",
        "\e[1;48m",
        "\e[1;49m"};

    printf("%p\n", tools);
    *(void **)tools = (void *)colors[color];
}

void set_tui_foreground_color(int color, void *tools)
{
        const char *colors[] = {
        "\e[1;31m",
        "\e[1;32m",
        "\e[1;33m",
        "\e[1;34m",
        "\e[1;35m",
        "\e[1;36m",
        "\e[1;37m",
        "\e[1;38m",
        "\e[1;39m"};

    tools += sizeof(void *) * 1;
    *(void**)tools = (void *)colors[color];
}

void  create_tui(tools_t *tools)
{
    get_terminal_size(tools);
    tools->terminal_center_col = tools->terminal_cols / 2;
    tools->terminal_center_row = tools->terminal_rows / 2;
}

int create_blank_screen(tools_t *tools)
{
    int i = 0;
    int j = 0;
    write(STDOUT_FILENO, tools->background_color, 7);
    write(STDOUT_FILENO, tools->foreground_color, 7);
    while (i < tools->terminal_rows)
    {
        while (j < tools->terminal_cols)
        {
            if (write(STDOUT_FILENO, " ", 1) != 1)
                return 0;
            j++;
        }
        if (write(STDOUT_FILENO, "\n", 1) != 1)
            return 0;
        j= 0;
        i++;
    }
}

void *new_page(int cols, int rows)
{
    page_t *page = malloc(sizeof(page_t));
    if (page == NULL)
        return NULL;
    page->page_cols = cols;
    page->page_rows = rows;
    return page;

}

void set_page_colors()
{

}