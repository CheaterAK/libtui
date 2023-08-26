
#include <asm/ioctls.h>

#include "tui.h"
int create_blank_screen(tools_t *tools);


int main(void)
{
    tools_t *tools;
    tools = malloc(sizeof(tools_t));
    printf("%p\n", &tools->background_color);
    printf("%p\n", &tools->foreground_color);
    get_terminal_size(tools);
    set_tui_background_color(BLUE, tools);
    set_tui_foreground_color(YELLOW, tools);
    create_blank_screen(tools);    
    printf("%p\n", &tools->background_color);
    printf("%p\n", &tools->foreground_color);
    printf("%p\n", tools->background_color);
    printf("%p\n", tools->foreground_color);
    while (1)
    {
        /* code */
    }
    
    return 0;  
}