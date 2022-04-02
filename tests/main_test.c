#include "../libft.h"
#include <stdio.h>
#include <ctype.h> /* Isalpha, isnum ... */ 
#include <string.h>
#include <stdlib.h>

char *functionsChar[] = {
      "ft_isalpha", "ft_isdigit", "ft_isalnum", "ft_isascii", 
      "ft_isprint"
};
char *stdLibFunctions[] = {
      "isalpha", "isdigit", "isalnum", "isascii", 
      "isprint"              
};
char *strings[] = {
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit",
    "Cras laoreet scelerisque quam, eget molestie metus tincidunt eget. Etiam ultrices hendrerit nulla, eu iaculis neque suscipit sit amet. Nulla consectetur,", 
    "Vestibulum ut risus vel elit porttitor vehicula. Fusce eget malesuada lacus. Quisque placerat maximus tempor. Ut mattis orci quam, vitae ullamcorper nisl tempus eu. Sed elementum odio id egestas gravida. Suspendisse potenti. Aliquam non tellus in nisi commodo placerat. Orci varius natoque", 
    "Nullam nulla odio", 
    "Integer sollicitudin ante nunc, tempus vulputate nisl ornare ut. Sed lacinia, quam ut gravida tempus, nisi libero imperdiet enim, eu volutpat sapien ex vel nisi. Nulla urna tellus, facilisis ut porta eget, dapibus auctor nibh. Cras tortor ligula, tincidunt lobortis consectetur ac, sagittis ut lacus. Vivamus pellentesque pellentesque risus nec pulvinar. Praesent euismod dolor diam. Donec eget massa sapien. Aliquam nec rutrum metus. Sed gravida, purus ut mollis semper, est est placerat eros, sed fringilla ligula nisl sed purus.",
    "After the descriptions in the previous sections it is clear that there are many, many opportunities for programmers to influence a program's performance, positively or negatively. And this is for memory-related operations only. We will proceed in covering the opportunities from the ground up, starting with the lowest levels of physical RAM access and L1 caches, up to and including OS functionality which influences memory handling.",
    NULL
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
  if (memcmp(strA, strB, 50) != 0) {
    printf("Error na função memset");
    return;
  }
  memset(strA, 'b', 49);
  ft_memset(strB, 'b', 49); 
  strA[49] = 0; 
  strB[49] = 0;
  if (memcmp(strA, strB, 50) != 0) {
    printf("Error na função memset");
    return;
  }
  memset(strA, 0, 49);
  ft_memset(strB, 0, 49); 
  strA[49] = 0; 
  strB[49] = 0;
  if (memcmp(strA, strB, 50) != 0) {
    printf("Error na função memset");
  }
  printf("Sucesso na execução da função: ft_memset\n");
}

void testLibBzero(void) {
  char strA[50];
  char strB[50]; 
  bzero(strA, 50);
  ft_bzero(strB, 50);
  if (memcmp(strA, strB, 50) != 0) {
    printf("Error na função ft_bzero\n"); 
  }
  printf("Sucesso na execução da função: ft_bzero\n");
}

void testLibMemCpy(void) {
  char *ptrA = NULL; 
  char *ptrB = NULL; 
  int arrayA[] = {10,20,30,40,50,60,70,80,90,100,0};
  int arrayB[11];
  for(int i = 0; strings[i] != NULL; i++) {
    size_t size = ft_strlen(strings[i]) + 1;
    ptrA = (char *) malloc(size); 
    ptrB = (char *) malloc(size);
    ft_memcpy(ptrA, strings[i], size); 
    memcpy(ptrB, strings[i], size);
    if (memcmp(ptrA, ptrB, size) != 0) {
      printf("Erro na função memcmp\n");
      return; 
    }
    free(ptrA); free(ptrB); 
  }
  ft_memcpy(arrayB, arrayA, 11); 
  if (memcmp(arrayA, arrayB, 11) != 0) {
      printf("Erro na função memcmp\n");
      return; 
  }

  printf("Sucesso na execução da função: ft_memcpy\n");
} 


int main(void) {
  testLibFtCharFunctions(ft_isalpha, isalpha); 
  testLibFtCharFunctions(ft_isdigit, isdigit); 
  testLibFtCharFunctions(ft_isalnum, isalnum); 
  testLibFtCharFunctions(ft_isascii, isascii); 
  testLibFtCharFunctions(ft_isprint, isprint);
  
  testLibStrLen(); 
  testLibMemSet();
  testLibBzero();
  testLibMemCpy();
}
