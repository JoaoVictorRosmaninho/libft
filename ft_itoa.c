#include "./libft.h"


void	ft_rev(char *s1, int size)
{
	int		ini;
	char	aux;

	ini = 0;
	while (ini < size)
	{
		aux = s1[ini];
		s1[ini] = s1[size];
		s1[size] = aux;
		ini++;
		size--;
	}
}

void	convert(int nb, char *number, int index)
{
	if (nb >= 0)
	{
		while (nb > 0)
		{
			number[index++] = '0' + (nb % 10);
			nb /= 10;
		}
		if (index == 0)
			number[index++] = '0';
		number[index] = '\0';
	}
	else
	{
		number[index++] = '0' + ((nb % -10) * -1);
		nb /= -10;
		while (nb > 0)
		{
			number[index++] = '0' + (nb % 10);
			nb /= 10;
		}
		number[index++] = '-';
		number[index] = '\0';
	}
}

char *ft_itoa(int n) 
{
	char	*number;

	number = ft_calloc(12, sizeof(char)); 
        convert(n, number, 0);
	ft_rev(number, ft_strlen(number) - 1);
        return(number); 
}


