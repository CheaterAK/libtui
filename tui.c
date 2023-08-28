#include "tui.h"

void get_terminal_size(window_t *window)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    window->terminal_rows = w.ws_row;
    window->terminal_cols = w.ws_col;
}

void  set_background_color(int color, void *window)
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
    *(void **)window = (void *)colors[color];
}

void set_foreground_color(int color, void *window)
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
    window += sizeof(void *);
    *(void**)window = (void *)colors[color];
}

window_t *create_tui(void)
{
    window_t *window;
    window = malloc(sizeof(window_t));
    if (!window)
    {
        fprintf(stderr, "Error: allocation failed to create window\n");
        return NULL;
    }
    get_terminal_size(window);
    window->terminal_center_col = window->terminal_cols / 2;
    window->terminal_center_row = window->terminal_rows / 2;
    window->buffer = malloc(sizeof(char) * window->terminal_cols * window->terminal_rows);
    if (!window->buffer)
    {
        fprintf(stderr, "Error: allocation failed to create window buffer\n");
        return NULL;
    }
    set_background_color(DEFAULT, window);
    set_foreground_color(DEFAULT, window);
    return window;
}

int create_blank_screen(window_t *window)
{
    int i = 0;
    int j = 0;
    int col_page_start = window->terminal_center_col - (((page_t *)window->page)->page_cols / 2); 
    int row_page_start = window->terminal_center_row - (((page_t *)window->page)->page_rows / 2);
    int col_page_end = window->terminal_center_col + (((page_t *)window->page)->page_cols / 2);
    int row_page_end = window->terminal_center_row + (((page_t *)window->page)->page_rows / 2);
    while (i < window->terminal_rows)
    {
        write(STDOUT_FILENO, window->background_color, 7);
        write(STDOUT_FILENO, window->foreground_color, 7);
        while (j < window->terminal_cols)
        {
            if ((i >= row_page_start && i < row_page_end) && j == col_page_start)
            {
                write(STDOUT_FILENO, ((page_t *)window->page)->background_color, 7);
                write(STDOUT_FILENO, ((page_t *)window->page)->foreground_color, 7);
                while (j - col_page_start < ((page_t *)window->page)->page_cols)
                {
                    if (write(STDOUT_FILENO, " ", 1) != 1)
                        return 0;
                    j++;
                }
                write(STDOUT_FILENO, window->background_color, 7);
                write(STDOUT_FILENO, window->foreground_color, 7);
            }
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