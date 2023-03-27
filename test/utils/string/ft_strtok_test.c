#include "../../test.h"


void ft_strtok_test(void)
{
    ft_printf("ft_strtok_test: when a string with no delimiter match is passed\n");

    {
        char str[] = "testando ola mundo tetse quadrado";

        char *curr = ft_strtok(str, ";");

        ft_printf("\tcurrent token is expected to be null ");
        assert(curr == NULL);
        ft_printf("\n");

    }

    ft_printf("ft_strtok_test: when a valid string and delimiter is passed\n");
    {
        char str[] = "testando;ola;mundo";
        char *results[4];
        
        results[0] = ft_strdup(ft_strtok(str, ";"));
        results[1] = ft_strdup(ft_strtok(str, ";"));
        results[2] = ft_strdup(ft_strtok(str, ";"));
        results[3] = ft_strdup(ft_strtok(str, ";"));

        ft_printf("\texpected to return the correct results: ");

        assert(strcmp(results[0], "testando") == 0);

        assert(strcmp(results[1], "ola") == 0);
        
        assert(strcmp(results[2], "mundo") == 0);

        assert(results[3] == NULL);
        
        ft_printf("\n");


        free(results[0]);
        free(results[1]);
        free(results[2]);
    }
     ft_printf("ft_strtok_test: when a string with delimiter at end is passed\n");
    {
        char str[] = "ola mundo teste\n";

        char *results[2];

        results[0] = ft_strdup(ft_strtok(str, "\n"));
        results[1] = ft_strtok(str, "\n");

        ft_printf("\texpected to return the correct results: ");

        assert(strcmp(results[0], "ola mundo teste") == 0);
        assert(results[1] == NULL);

        free(results[0]);
    }
}