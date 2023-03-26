#include "../../../test.h"


void    get_next_line_test(void)
{
    int fd = 0;
    char *line = get_next_line(fd);

    ft_printf("get_next_line_test: ");

    {
        ft_printf("it expect return NULL: ");
        assert(line == NULL);
    }

}


