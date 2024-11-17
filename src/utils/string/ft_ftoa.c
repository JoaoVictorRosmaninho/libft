

#include "../../../includes/libft.h"


char* ft_ftoan(double n, t_coliseu* coliseu, unsigned char precision) {

    int n_int    = (int) n;

    int decimal  = (int)((n - n_int) *  pow(10, precision));

    char* number = ft_calloc(12, sizeof(char), coliseu);

    ft_strlcpy(number, ft_itoa(n_int, coliseu), 12);

    ft_strlcat(number, ".", 12);

    ft_strlcat(number, ft_itoa(decimal, coliseu), 12);

    return number;
}


char*   ft_ftoa(double n, t_coliseu* coliseu) {
    return ft_ftoan(n, coliseu, 6);
}
