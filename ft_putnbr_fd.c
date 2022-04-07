#include "./libft.h"

void ft_putnbr_fd(int n, int fd) 
{
 char *number = ft_itoa(n); 
 write(fd, number, ft_strlen(number)); 
}
