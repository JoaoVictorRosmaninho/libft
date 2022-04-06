#ifndef LIBFT_H
# define LIBFT_H 
# include <stdlib.h>
# include <unistd.h>
int ft_isalpha(int C); 
int ft_isdigit(int C);
int ft_isalnum(int C);
int ft_isascii(int C);
int ft_isprint(int C);
int ft_toupper(int C);
int ft_tolower(int C);
int ft_isspace(int C);
size_t ft_strlen(const char *S); 
void *ft_memset(void *BLOCK, int C, size_t SIZE); 
void *ft_bzero(void *BLOCK, size_t SIZE); 
void *ft_memcpy(void *TO, const void *FROM, size_t size);
void *ft_memmove(void *dest, const void *src, size_t n); 
size_t ft_strlcpy(char *dst, const char *src, size_t size); 
size_t ft_strlcat(char *dst, const char *src, size_t size); 
char *ft_strchr(const char *STRING, int C);
char *ft_strrchr(const char *STRING, int C);
int ft_strncmp(const char *S1, const char *S2, size_t SIZE);
int ft_memcmp(const void *A1, const void *A2, size_t SIZE);
char *ft_strnstr(const char *big, const char *little, size_t len);
int ft_atoi(const char *STRING);
char *ft_strdup(const char *S);
void *ft_calloc(size_t COUNT, size_t ELTSIZE);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strtrim(char const *s1, char const *set);
char **ft_split(char const *s, char c);
char *ft_itoa(int n);
char *ft_strmapi(char const *s, char (*f)(unsigned int, char));
void ft_striteri(char *s, void (*f)(unsigned int,char*));
void ft_putchar_fd(char c, int fd);
#endif
