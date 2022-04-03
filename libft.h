#ifndef LIBFT_H
# include <stdlib.h>
int ft_isalpha(int C); 
int ft_isdigit(int C);
int ft_isalnum(int C);
int ft_isascii(int C);
int ft_isprint(int C);
int ft_toupper(int C);
int ft_tolower(int C);
unsigned int ft_strlen(const char *S); 
void *ft_memset(void *BLOCK, int C, unsigned int SIZE); 
void *ft_bzero(void *BLOCK, unsigned int SIZE); 
void *ft_memcpy(void *TO, const void *FROM, unsigned int size);
void *ft_memmove(void *dest, const void *src, size_t n); 
size_t ft_strlcpy(char *dst, const char *src, size_t size); 
size_t ft_strlcat(char *dst, const char *src, size_t size); 
char *ft_strchr(const char *STRING, int C); 

#endif
