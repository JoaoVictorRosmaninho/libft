#include "../libft.h"
#include <stdio.h>
#include <ctype.h> /* Isalpha, isnum ... */

char *functionsChar[] = {"ft_isalpha", "ft_isdigit", "ft_isalnum"};
char *stdLibFunctions[] = {"isalpha", "isdigit", "isalnum"};

void testLibFtCharFunctions(int (*libftFunction)(int), int(*functionStdLib)(int)) {
  static int pos = 0; 
  for (unsigned int value = 0; value < 256; value++) {
    int v1, v2; 
    if ((v1 = libftFunction(value)) !=  (v2 = functionStdLib(value))) {
      if (v1 > 0 && v2 > 0) /* Muitas funções da  libc retornam um inteiro nao nulo, nao restrito ao numeor 1 */
        continue; 
      printf("Erro em %s, no cod ASC => %u\n", functionsChar[pos], value);
      printf("%s => %u, %s => %u\n", stdLibFunctions[pos], functionStdLib(value), functionsChar[pos],  libftFunction(value));
      return; 
    }
  }

  printf("Sucesso na Execução da função: %s\n", functionsChar[pos++]);
}


int main(void) {
  testLibFtCharFunctions(ft_isalpha, isalpha); 
  testLibFtCharFunctions(ft_isdigit, isdigit); 
  testLibFtCharFunctions(ft_isalnum, isalnum); 
}
