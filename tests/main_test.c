#include "../libft.h"
#include <stdio.h>
#include <ctype.h> /* Isalpha, isnum ... */ 
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <bsd/string.h>


#define SIZE_STRINGS 5
char *functionsChar[] = {
      "ft_isalpha", "ft_isdigit", "ft_isalnum", "ft_isascii", 
      "ft_isprint", "ft_toupper", "ft_tolower"
};
char *stdLibFunctions[] = {
      "isalpha", "isdigit", "isalnum", "isascii", 
      "isprint", "toupper", "tolower"              
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
      printf("Erro na função ft_memove\n");
      return; 
    }
    free(ptrA); free(ptrB); 
  }
  ft_memcpy(arrayB, arrayA, 11); 
  if (memcmp(arrayA, arrayB, 11) != 0) {
      printf("Erro na função ft_memmove\n");
      return; 
  }

  printf("Sucesso na execução da função: ft_memcpy\n");
} 

void testLibMemMove(void) {
  char *ptrA = NULL; 
  char *ptrB = NULL; 
  int arrayA[] = {10,20,30,40,50,60,70,80,90,100,0};
  int arrayB[11];
  for(int i = 0; strings[i] != NULL; i++) {
    size_t size = ft_strlen(strings[i]) + 1;
    ptrA = (char *) malloc(size); 
    ptrB = (char *) malloc(size);
    ft_memmove(ptrA, strings[i], size); 
    memmove(ptrB, strings[i], size);
    if (memcmp(ptrA, ptrB, size) != 0) {
      printf("Erro na função ft_memmove\n");
      return; 
    }
    free(ptrA); free(ptrB); 
  }
  ft_memmove(arrayB, arrayA, 11); 
  if (memcmp(arrayA, arrayB, 11) != 0) {
      printf("Erro na função ft_memmove\n");
      return; 
  }

  printf("Sucesso na execução da função: ft_memmove\n");
} 

void testLibStrLcpy(void) {
  char strA[30] = {0}; 
  char strB[30] = {0}; 
  for (unsigned int i = 0; strings[i] != NULL; i++) {
    ft_strlcpy(strA, strings[i], 30);
    strlcpy(strB, strings[i], 30);
    if (strcmp(strA, strB) != 0) { // memcmp nao funcionou
      printf("Erro na função ft_strlcpy\n");
      printf("%s\n", strA);
      printf("%s\n", strB);
      return;
    }
  }
  printf("Sucesso na execução da função: ft_strlcpy\n");
}

void testLibStrlCat(void) {
  /* incrementar os testes  */
  char str[10] = {0};
  char str2[10] = {0};
  ft_strlcat(str, "joao", 10); 
  strlcat(str2, "joao", 10); 
  if (memcmp(str, str2, 10) != 0) 
  {
    printf("%s <=> %s\n", str, str2);
    puts("Erro na função ft_strlcat");
    return;
  }
  ft_strlcat(str, "dskdasdsadklsdlkksdop", 10); 
  strlcat(str2, "dskdasdsadklsdlkksdop", 10); 
  if (memcmp(str, str2, 10) != 0) 
  {
    puts("Erro na função ft_strlcat");
    return;
  }
  char s1[20] = "Bom dia";
  char s2[20] = "Bom dia";
  ft_strlcat(s1, ", Boa noite", 20); 
  strlcat(s2, ", Boa noite", 20); 
  if (memcmp(s1, s2, 20) != 0) 
  {
    puts("Erro na função ft_strlcat");
    return;
  }
  printf("Sucesso na execução da função: ft_strlcat\n");
} 

void testLibStrChr(char *(flibft)(const char *, int), char *(flibc)(const char *, int), char *name) 
{
  for(int i = 0; strings[i] != NULL; i++) {
    for(char letter = 'a'; letter <= 'z'; letter++) {
      if (flibft(strings[i], letter) != flibc(strings[i], letter)) {
        printf("Erro na função: %s\n", name);
        return; 
      }
    }
  }
  printf("Sucesso na execução da função: %s\n", name);
}

/* Incrementar os testes  */
void testLibStrnCmp(void) {
  for(int i = 0; strings[i] != NULL; i++) {
   if (ft_strncmp(strings[i], strings[i], 10) != strncmp(strings[i], strings[i], 10)) {
     printf("Erro na função: ft_strncmp");
     return;
   } 
  }
  for (int i = SIZE_STRINGS, j = 0; i > 0; i--, j++) {
    if (ft_strncmp(strings[i], strings[j], 12) != strncmp(strings[i], strings[j], 12)) {
     printf("Erro na função: ft_strncmp");
     return;
    }
  }  
  for (int i = SIZE_STRINGS, j = 0; i > 0; i--, j++) {
    if (ft_strncmp(strings[i], strings[j], ft_strlen(strings[i])) != strncmp(strings[i], strings[j], ft_strlen(strings[i]))) {
     printf("Erro na função: ft_strncmp");
     return;
    }
  }  
  printf("Sucesso na execução da função: ft_strncmp\n");

}

void  testLibMemCmp(void) {
  int arrayA[] = {10,20,30}; 
  int arrayB[] = {10,20,40};
  int arrayC[] = {5,10,20};
  int arrayD[] = {5,21,32}; 
  int v1, v2;
  if ((v1 = ft_memcmp(arrayA, arrayB, sizeof(arrayA))) != (v2 = memcmp(arrayA, arrayB, sizeof(arrayA)))) {
     printf("Erro na função: ft_memcmp\n");
     printf("ft_memcmp: %d,  memcmp: %d\n", v1, v2);
     return;
  }
  if (ft_memcmp(arrayA, arrayA, sizeof(arrayA)) != memcmp(arrayA, arrayA, sizeof(arrayA))) {
     printf("Erro na função: ft_memcmp");
     return;
  }
  if ((v1 = ft_memcmp(arrayC, arrayD, sizeof(arrayC))) != (v2 = memcmp(arrayC, arrayD, sizeof(arrayC)))) {
     printf("Erro na função: ft_memcmp\n");
     printf("ft_memcmp: %d,  memcmp: %d\n", v1, v2);
     return;
  }
  if (ft_memcmp(arrayC, arrayC, sizeof(arrayC)) != memcmp(arrayC, arrayC, sizeof(arrayC))) {
     printf("Erro na função: ft_memcmp");
     return;
  }
  printf("Sucesso na execução da função: ft_memcmp\n");
}

void testLibStrnstr(void) {
  FILE *text = fopen("./files/strstr.txt", "r");
  FILE *textInput = fopen("./files/strInput.txt", "r");
  char buff_frase[254];
  char buff_word[16];
  while (fread(buff_frase, 254, 1, text) != 0) {
   while (fscanf(textInput, "%s", buff_word) != EOF) {
     char *p1, *p2; 
      if ((p1 = ft_strnstr(buff_frase, buff_word, 254 )) != (p2 = strnstr(buff_frase, buff_word, 254))) {
        printf("Erro na função: ft_strnstr\n");
        printf("input: %s\nft_strnstr: %s\nstrnstr: %s", buff_word, p1,  p2);
        return; 
    }
   }
}
  fclose(text); fclose(textInput);
  printf("Sucesso na execução da função: ft_strnstr\n");
}

void testLibatoi(void) {
  FILE *input = fopen("./files/atoi.txt", "r"); 
  char buff[32]; 
  while (fscanf(input, "%s", buff) != EOF) {
    register int v1, v2; 
    if ((v1 = ft_atoi(buff)) !=  (v2 = atoi(buff))) {
      printf("Error na função: ft_atoi\n value: %s\n", buff);
      printf("ft_atoi: %d, atoi: %d", v1, v2); 
      return;
    }
  }
  fclose(input);
  printf("Sucesso na execução da função: ft_atoi\n");
}

void testLibstrdup(void) {
  for(int i = 0; strings[i] != NULL; i++) {
   char *str = ft_strdup(strings[i]);
   if(ft_memcmp(str, strings[i], ft_strlen(strings[i])) != 0) {
     puts("Erro na função ft_strdup");
     return; 
   }
   free(str);
  }
  printf("Sucesso na execução da função ft_strdup\n");
}

void testLibcalloc(void) {
  int *numbers = ft_calloc(10, sizeof(int)); 
  int *numbers_aux = calloc(10, sizeof(int)); 
  if (ft_memcmp(numbers, numbers_aux, 10 * sizeof(int)) != 0) {
     puts("Erro na função ft_calloc");
     return;
  }
  free(numbers); free(numbers_aux);
  printf("Sucesso na execução da função ft_calloc\n");

}

/* Incrementar os testes */
void testLibftSubStr(void) {
  char str[] = "bom dia C, já é cedo hora de ir codar, bora bora bora!";
  char *ptr = ft_substr(str, 4, 3);
  if (ft_memcmp(ptr, "dia", 3) != 0) {
    printf("Error na função ft_substr: %s\n", ptr); 
    free(ptr);
    return; 
  }
  free(ptr);
  ptr = ft_substr(str, 18, 4); 
  if (ft_memcmp(ptr, "cedo", 4) != 0) {
    printf("Error na função ft_substr: %s\n", ptr); 
    free(ptr);
    return; 
  }
  free(ptr);
  ptr = ft_substr(str, 0, 3); 
  if (ft_memcmp(ptr, "bom", 4) != 0) {
    printf("Error na função ft_substr: %s\n", ptr); 
    free(ptr);
    return; 
  }
  
  free(ptr);  
  ptr = ft_substr(str, 46, 5); 
  if (ft_memcmp(ptr, "bora!", 4) != 0) {
    printf("Error na função ft_substr: %s", ptr); 
    free(ptr);
    return; 
  } 
  puts("Sucesso na execução da função ft_substr");
  free(ptr);
}

/* Incrementar testes com arquivo de texto*/
void testLibstrJoin(void) 
{
 char *ptr = ft_strjoin("joao", "victor");
 if (ft_memcmp(ptr, "joaovictor", ft_strlen("joaovictor")) != 0) {
   printf("Error na função: ft_strjoin, erro: %s\n", ptr);
   return; 
 }
 ptr = ft_strjoin(NULL, NULL); 
 if (ptr !=  NULL) {
   printf("Error na função: ft_strjoin, erro: %s\n", ptr);
   return; 
 }
 ptr = ft_strjoin(" teste", " -teste");
 if (ft_memcmp(ptr, " teste -teste", ft_strlen(ptr)) != 0) {
   printf("Error na função: ft_strjoin, erro: %s\n", ptr);
   return; 
 }
 ptr = ft_strjoin("AAAAA", "BBBBBB   ");
 if (ft_memcmp(ptr, "AAAAABBBBBB   ", ft_strlen(ptr)) != 0) {
   printf("Error na função: ft_strjoin, erro: %s\n", ptr);
   return; 
 }
 puts("Sucesso na execução da função: ft_strjoin");
}


void testLibstrTrim(void) {
  char str[] = "aaaavaaaa";
  if (ft_memcmp(ft_strtrim(str, "a"), "v", 1) != 0) { 
   printf("Error na função: ft_strtrim, erro: %s\n", str);
   return; 
  }
  char str2[] = "TjoaoAjoaoa";
  if (ft_memcmp(ft_strtrim(str2, "joaoa"), "TjoaoA", 6) != 0) {
   printf("Error na função: ft_strtrim, erro: %s\n", str);
   return; 
  }
  char str3[] = "kopAkop";
  if (ft_memcmp(ft_strtrim(str3, "kop"), "A", 1) != 0) {
   printf("Error na função: ft_strtrim, erro: %s\n", str);
   return; 
  }
  puts("Sucesso na execução da função: ft_strtrim"); 
}


// desemvolver testes
void testLibFtSplit(void)
{
  char str[] = "bom,,dia,macaco,careca,abobora,noite,cabeça,televisao,teste!,,doritos,,,macaco,"; 
  char **splited = ft_split(str, ',');
  for(int i = 0; splited[i] != NULL; i++)
    printf(splited[i]);
  putchar('\n');
  char str2[] = "bom####dia#macaco#car#e#c#a#abo#b####ora#noite##ca#beça#t###elevisao##teste!#d###orito#s####macaco#"; 
  splited = ft_split(str2, '#');
  for(int i = 0; splited[i] != NULL; i++)
    printf(splited[i]); 
  putchar('\n');
  char *str3 = "split  ||this|for|me|||||!|";
  splited = ft_split(str3, '|');
  for(int i = 0; splited[i] != NULL; i++)
    printf(splited[i]); 
  putchar('\n');  
  char *str4 = "      split       this for   me  !       ";
  splited = ft_split(str4, ' ');
  for(int i = 0; splited[i] != NULL; i++)
    printf(splited[i]); 
  putchar('\n');
  char str5[] = ""; 
  splited = ft_split(str2, '#');
  for(int i = 0; splited[i] != NULL; i++)
    printf(splited[i]); 
  putchar('\n');

  puts("Sucesso na execução da função: ft_strsplit, porém devo implementar os testes"); 
}


// testes + complemento de dois
void testLibft_itoa(void) {
  char *number = ft_itoa(500);
  if (ft_memcmp("500", number, 3) != 0) {
    printf("Error na função: ft_memcmp, value: %s\n", number);
    return; 
  }
  free(number); 
  number = ft_itoa(00);
  if (ft_memcmp("0", number, 1) != 0) {
    printf("Error na função: ft_itoa, value: %s\n", number);
    return; 
  }
  free(number); 
  number = ft_itoa(0);
  if (ft_memcmp("0", number, 0) != 0) {
    printf("Error na função: ft_itoa, value: %s\n", number);
    return; 
  } 
  free(number); 
  number = ft_itoa(11531);
  if (ft_memcmp("11531", number, 5) != 0) {
    printf("Error na função: ft_itoa, value: %s\n", number);
    return; 
  }
  free(number); 
  number = ft_itoa(-11531);
  if (ft_memcmp("-11531", number, 6) != 0) {
    printf("Error na função: ft_itoa, value: %s\n", number);
    return; 
  }
  free(number); 
  number = ft_itoa(INT_MAX);
  if (ft_memcmp("2147483647", number, 10) != 0) {
    printf("Error na função: ft_itoa, value: %s\n", number);
    return; 
  }
  free(number); 
  number = ft_itoa(INT_MIN);
  if (ft_memcmp("-2147483648", number, 11) != 0) {
    printf("Error na função: ft_itoa, value: %s\n", number);
    return; 
  }
  puts("Sucesso na execução da função: ft_itoa"); 
}


void upper(unsigned int index, char *ch) {
  *ch = ft_toupper(*ch); 
}


void lower(unsigned int index, char *ch) {
  *ch = ft_tolower(*ch); 
}

char mapi_upper(unsigned int index, char ch) {
  return ft_toupper(ch); 
}


char mapi_lower(unsigned int index, char ch) {
  return ft_tolower(ch); 
}

 void testFtStrTriteri(void) {
   char nome[] = "joao victor"; 
   char tst[] = "oLa45"; 
   ft_striteri(nome, upper);
   if (ft_memcmp(nome, "JOAO VICTOR", 11) != 0) {
     puts("Error na função ft_striteri");
     return; 
   }
   ft_striteri(nome, lower);
   if (ft_memcmp(nome, "joao victor", 11) != 0) {
     puts("Error na função ft_striteri");
     return; 
   }
   ft_striteri(tst, upper);
   if (ft_memcmp(tst, "OLA45", 5) != 0) {
     puts("Error na função ft_striteri");
     return; 
   }
   ft_striteri(tst, lower);
   if (ft_memcmp(tst, "ola45", 5) != 0) {
     puts("Error na função ft_striteri");
     return; 
   }
   puts("Sucesso na execução da função: ft_striteri"); 
}

 void testFtstrmapi(void) {
   char *nome = ft_strmapi("joao victor", mapi_upper);
   if (ft_memcmp(nome, "JOAO VICTOR", 11) != 0) {
     printf("Error na função ft_strmapi, error: %s\n", nome);
     return; 
   }
   free(nome); 
   nome = ft_strmapi("joao victor", mapi_lower);
   if (ft_memcmp(nome, "joao victor", 11) != 0) {
     printf("Error na função ft_strmapi, error: %s\n", nome);
     return; 
   }
   char *tst = ft_strmapi("oLa45", mapi_upper);
   if (ft_memcmp(tst, "OLA45", 5) != 0) {
     printf("Error na função ft_strmapi, error: %s\n", tst);
     return; 
   }
   free(tst);
   tst = ft_strmapi("OLa45", mapi_lower);
   if (ft_memcmp(tst, "ola45", 5) != 0) {
     printf("Error na função ft_strmapi, error: %s\n", tst);
     return; 
   } 
   puts("Sucesso na execução da função: ft_strmapi"); 
}




void printElement(t_list *node, char *log) {
  FILE *fp = fopen(log, "w"); 
  if (!fp) {
    puts("Erro ao abrir o arquivo\n"); 
    return;
  }
  if (!node) {
    puts("A lista está vazia");
    return ;
  }
  while (node != NULL) {
    fprintf(fp, "%d ", *(int *) node->content); 
    node = node->next; 
  }
  fprintf(fp, "%c", '\n');
  fclose(fp);
}


void *retorna(void *tmp) {

  *(int *) tmp *= 1;
  return tmp;
}


void retorna_mapi(void *tmp) 
{
  *(int *) tmp *= -1;
}

void nullInt(void *ptr) {
  *(int *)ptr = 0; 
}

void testListAddandSize(void) {
  t_list *list = NULL;

  for (int i = 0; i < 255; i++) {
    ft_lstadd_back(&list, ft_lstnew(&i));
  }
  int value;
  if ((value = ft_lstsize(list)) != 255) {
    printf("Erro na função ft_lstsize e/ou na ft_lstadd_back\n");
    printf("retorno: %d\n", value);
    return; 
  }
  printElement(list, "listAddBack"); 
  ft_lstclear(&list, NULL); 
  if (list != NULL) {
    printf("Erro na função: ft_lstclear\n");
    return; 
  }
  puts("Sucesso na execução da função: ft_lstsize, ft_lstadd_back e ft_lstclear"); 
}
void testListAddFrontandSize(void) {
  t_list *list = NULL;

  for (int i = 0; i < 255; i++) {
    ft_lstadd_front(&list, ft_lstnew(&i));
  }
  int value;
  if ((value = ft_lstsize(list)) != 255) {
    printf("Erro na função ft_lstsize e/ou na ft_lstadd_front\n");
    printf("retorno: %d\n", value);
    return; 
  }
  printElement(list, "listAddFront"); 
  ft_lstclear(&list, NULL); 
  if (list != NULL) {
    printf("Erro na função: ft_lstclear\n");
    return; 
  }
  puts("Sucesso na execução da função: ft_lstsize, ft_lstadd_front e ft_lstclear"); 
}

void test_ftlstiler(void) {
  t_list *list = NULL; 
  for (int i = 0; i < 255; i++)  
    ft_lstadd_front(&list, ft_lstnew(&i));
  ft_lstiter(list, retorna_mapi);
  printElement(list, "listDobrada"); 
  ft_lstclear(&list, NULL);
  if (list != NULL) {
    printf("Erro na função: ft_lstclear\n");
    return; 
  }
  puts("Sucesso na execução da função: ft_lstiter, ft_lstadd_front e ft_lstclear"); 
}


void test_ftlstmap(void) {
  t_list *list = NULL; 
  /*
  for (int i = 0; i < 255; i++)  
    ft_lstadd_front(&list, ft_lstnew(&i));
  */ 
  
  int a = 1;
  int b = 2;
  int c = 3;
  ft_lstadd_front(&list, ft_lstnew(&a));
  ft_lstadd_front(&list, ft_lstnew(&b));
  ft_lstadd_front(&list, ft_lstnew(&c));
  
  t_list *new_list = ft_lstmap(list, retorna, nullInt);
  printElement(list, "OldListMapi"); 
  printElement(new_list, "NewListMapi");
  if (list == new_list) {
    printf("Erro na função: ft_lstmap\n");
  }
  ft_lstclear(&list, NULL); 
  ft_lstclear(&new_list, NULL); 
  puts("Sucesso na execução da função: ft_lstmap ft_lstadd_front, ft_lstadd_front e ft_lstclear"); 
}


int main(void) 
{
 
  testLibFtCharFunctions(ft_isalpha, isalpha); 
  testLibFtCharFunctions(ft_isdigit, isdigit); 
  testLibFtCharFunctions(ft_isalnum, isalnum); 
  testLibFtCharFunctions(ft_isascii, isascii); 
  testLibFtCharFunctions(ft_isprint, isprint);
  testLibFtCharFunctions(ft_toupper, toupper);
  testLibFtCharFunctions(ft_tolower, tolower);

  testLibStrLen(); 
  testLibMemSet();
  testLibBzero();
  testLibMemCpy();
  testLibMemMove();
  testLibStrLcpy();
  testLibStrlCat();
  testLibStrChr(ft_strchr, strchr, "ft_strchr");
  testLibStrChr(ft_strrchr, strrchr, "ft_strrchr");
  testLibStrnCmp();
  testLibMemCmp();  
  testLibStrnstr();  
  testLibatoi();
  testLibstrdup();
  testLibcalloc();
  testLibftSubStr();
  testLibstrJoin();
  testLibstrTrim(); 
  testLibft_itoa();
  testLibFtSplit();
  testListAddFrontandSize();
  testFtStrTriteri();
  testFtstrmapi();
  testListAddandSize();
  test_ftlstiler();
  test_ftlstmap();
  
  /*
  int a = 10;
  int b = 20;
  ft_lstadd_front(&list, ft_lstnew(&a));
  ft_lstadd_front(&list, ft_lstnew(&b)); 
  //ft_lstadd_front(&list, ft_lstnew(3));
  //ft_lstadd_front(&list, ft_lstnew(4)); 
 // printElement(list);
  //ft_lstclear(&list, retorna);  
  printElement(list);
  t_list *t = ft_lstmap(list, retorna, NULL); 
  printElement(t);
  */
}
