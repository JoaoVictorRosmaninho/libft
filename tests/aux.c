#include "../libft.h"
#include <stdio.h>
#include <ctype.h>



int main(void) {
  char nome[50] = {"bom dia mundo, meu nome é vetor!"};
  char *p = ft_strdup(nome); 
  printf("%s\n", p);
}
