

#ifndef TUI_H
# define TUI_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define TUI_KEY_UP 4283163
# define TUI_KEY_DOWN 4348699
# define TUI_KEY_LEFT 4479771
# define TUI_KEY_RIGHT 4414235
# define TUI_KEY_ESC 27
# define TUI_KEY_SPACE 32
# define TUI_KEY_ENTER 10

typedef struct tools_s
{
    void *background_color;
    void *foreground_color;
    int terminal_cols;
    int terminal_rows;
    int terminal_center_col;
    int terminal_center_row;
    void *page;
} tools_t;

typedef struct page_s
{
    void *background_color;
    void *foreground_color;
    int page_cols;
    int page_rows;
} page_t;

enum colors_e
{
    RED = 0,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    BLACK,
    DEFAULT
};


void get_terminal_size(tools_t *);
void set_tui_background_color(int, void *);
void set_tui_foreground_color(int, void *);
void *new_page();


#endif