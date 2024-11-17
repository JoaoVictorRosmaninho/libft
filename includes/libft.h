/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:58:20 by jv                #+#    #+#             */
/*   Updated: 2024/11/16 23:43:30 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H 
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdarg.h> 
# include "arena.h"
# include "linked.h"
# include "ft_printf.h"

# define BUFFER_SIZE 64
# define NUMBER_OF_COLISEUS 2

# define ABS(x) ( ( (x) < 0) ? -(x) : (x) )

int			ft_isalpha(int C);
int			ft_isdigit(int C);
int			ft_isalnum(int C);
int			ft_isascii(int C);
int			ft_isprint(int C);
int			ft_toupper(int C);
int			ft_tolower(int C);
int			ft_isspace(int C);
int			ft_strncmp(const char *S1, const char *S2, size_t SIZE);
int			ft_memcmp(const void *A1, const void *A2, size_t SIZE);
int			ft_atoi(const char *STRING);

size_t		ft_strlen(const char *S);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);

void		*ft_memset(void *BLOCK, int C, size_t SIZE);
void		ft_bzero(void *BLOCK, size_t SIZE);
void		*ft_memcpy(void *TO, const void *FROM, size_t size);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memchr(const void *BLOCK, int C, size_t SIZE);
void		*ft_calloc(size_t COUNT, size_t ELTSIZE, t_coliseu* coliseu);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));


char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strdup(const char *S, t_coliseu* coliseu);
char		*ft_strchr(const char *STRING, int C);
char		*ft_strrchr(const char *STRING, int C);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n, t_coliseu* coliseu);
char		*ft_ftoa(double n, t_coliseu* coliseu);
char		*ft_ftoan(double n, t_coliseu* coliseu, unsigned char precision);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strtok(char *str, const char *delimiter);
char	    *ft_strndup(const char *str, unsigned int n);

ssize_t		ft_putchar_fd(char c, int fd);
ssize_t		ft_putstr_fd(char *s, int fd);
ssize_t		ft_putendl_fd(char *s, int fd);
ssize_t		ft_putnbr_fd(int n, int fd);
int			ft_printf(const char *TEMPLATE, ...);
int         ft_fprintf(int fout, const char *TEMPLATE, ...);
ssize_t		ft_printf_hex_lower(int n);
ssize_t		ft_printf_hex_upper(int n);
ssize_t		ft_printf_uint(unsigned	int n);
void		reverse_array(char *str, int end);
char		*int2hex(unsigned int n, unsigned char op, char* buffer);
char		*lint2hex(unsigned long int n);
ssize_t		ft_printf_ptr(unsigned long int n);

/* get_next_line */

char  *get_next_line(int fd);
#endif
