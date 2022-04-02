#ifndef LIBFT_H

int ft_isalpha(int C); 
int ft_isdigit(int C);
int ft_isalnum(int C);
int ft_isascii(int C);
int ft_isprint(int C);
unsigned int ft_strlen(const char *S); 
void *ft_memset(void *BLOCK, int C, unsigned int SIZE); 
void *ft_bzero(void *BLOCK, unsigned int SIZE); 
void *ft_memcpy(void *TO, void *FROM, unsigned int size); 

#endif
