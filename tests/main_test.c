#include "../libft.h"
#include <stdio.h>
#include <ctype.h> /* Isalpha, isnum ... */ 
#include <string.h>

char *functionsChar[] = {
      "ft_isalpha", "ft_isdigit", "ft_isalnum", "ft_isascii", 
      "ft_isprint"
};
char *stdLibFunctions[] = {
      "isalpha", "isdigit", "isalnum", "isascii", 
      "isprint"              
};

void testLibFtCharFunctions(int (*libftFunction)(int), int(*functionStdLib)(int)) {
  static int pos = 0; 
  for (unsigned int value = 0; value < 256; value++) {
    int v1, v2; 
    if ((v1 = libftFunction(value)) !=  (v2 = functionStdLib(value))) {
      if (v1 > 0 && v2 > 0) /* Muitas funções da  libc retornam um inteiro nao nulo, nao restrito ao numeor 1, pode ser um ponto de bug*/
        continue; 
      printf("Erro em %s, no cod ASC => %u\n", functionsChar[pos], value);
      printf("%s => %u, %s => %u\n", stdLibFunctions[pos], functionStdLib(value), functionsChar[pos],  libftFunction(value));
      return; 
    }
  }

  printf("Sucesso na Execução da função: %s\n", functionsChar[pos]);
  pos++;
}

void testLibStrLen(void) {
  char *strings[] = {
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit",
    "Cras laoreet scelerisque quam, eget molestie metus tincidunt eget. Etiam ultrices hendrerit nulla, eu iaculis neque suscipit sit amet. Nulla consectetur,", 
    "Vestibulum ut risus vel elit porttitor vehicula. Fusce eget malesuada lacus. Quisque placerat maximus tempor. Ut mattis orci quam, vitae ullamcorper nisl tempus eu. Sed elementum odio id egestas gravida. Suspendisse potenti. Aliquam non tellus in nisi commodo placerat. Orci varius natoque", 
    "Nullam nulla odio", 
    "Integer sollicitudin ante nunc, tempus vulputate nisl ornare ut. Sed lacinia, quam ut gravida tempus, nisi libero imperdiet enim, eu volutpat sapien ex vel nisi. Nulla urna tellus, facilisis ut porta eget, dapibus auctor nibh. Cras tortor ligula, tincidunt lobortis consectetur ac, sagittis ut lacus. Vivamus pellentesque pellentesque risus nec pulvinar. Praesent euismod dolor diam. Donec eget massa sapien. Aliquam nec rutrum metus. Sed gravida, purus ut mollis semper, est est placerat eros, sed fringilla ligula nisl sed purus.", 
    NULL
  };

  for (unsigned int i = 0; strings[i] != NULL; i++) {
    unsigned int v1, v2; 
    if ((v1 = ft_strlen(strings[i])) != (v2 = strlen(strings[i]))) {
      printf("Error, strlen = %u, ft_strlen => %u",  v1, v2);
      return; 
    }
  }
  printf("Sucesso na execução da função: ft_strlen\n");
}

void testLibMemSet(void) {
  char strA[50];
  char strB[50]; 
  memset(strA, 'a', 49);
  ft_memset(strB, 'a', 49); 
  strA[49] = 0; 
  strB[49] = 0;
  if (strcmp(strA, strB) != 0) {
    printf("Error na função memset");
    return;
  }
  memset(strA, 'b', 49);
  ft_memset(strB, 'b', 49); 
  strA[49] = 0; 
  strB[49] = 0;
  if (strcmp(strA, strB) != 0) {
    printf("Error na função memset");
    return;
  }
  memset(strA, 0, 49);
  ft_memset(strB, 0, 49); 
  strA[49] = 0; 
  strB[49] = 0;
  if (strcmp(strA, strB) != 0) {
    printf("Error na função memset");
  }
  printf("Sucesso na execução da função: ft_memset\n");
}


int main(void) {
  testLibFtCharFunctions(ft_isalpha, isalpha); 
  testLibFtCharFunctions(ft_isdigit, isdigit); 
  testLibFtCharFunctions(ft_isalnum, isalnum); 
  testLibFtCharFunctions(ft_isascii, isascii); 
  testLibFtCharFunctions(ft_isprint, isprint);
  
  testLibStrLen(); 
  testLibMemSet();   
}
