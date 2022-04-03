#include "../libft.h"
#include <stdio.h>
#include <ctype.h>



int main(void) {
  char nome[50] = {"bom dia mundo, meu nome é vetor!"}; 
  printf("%s\n", ft_strchr(nome, 'v'));
}
