/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jv <jv@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 15:58:20 by jv                #+#    #+#             */
/*   Updated: 2023/01/17 16:38:11 by jv               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H 
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h> 
# include "../src/ds/ft_list/linked.h"

int			ft_isalpha(int C);
int			ft_isdigit(int C);
int			ft_isalnum(int C);
int			ft_isascii(int C);
int			ft_isprint(int C);
int			ft_toupper(int C);
int			ft_tolower(int C);
int			ft_isspace(int C);
size_t		ft_strlen(const char *S);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
void		*ft_memset(void *BLOCK, int C, size_t SIZE);
void		ft_bzero(void *BLOCK, size_t SIZE);
void		*ft_memcpy(void *TO, const void *FROM, size_t size);
void		*ft_memmove(void *dest, const void *src, size_t n);
char		*ft_strchr(const char *STRING, int C);
char		*ft_strrchr(const char *STRING, int C);
int			ft_strncmp(const char *S1, const char *S2, size_t SIZE);
int			ft_memcmp(const void *A1, const void *A2, size_t SIZE);
void		*ft_memchr(const void *BLOCK, int C, size_t SIZE);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_atoi(const char *STRING);
char		*ft_strdup(const char *S);
void		*ft_calloc(size_t COUNT, size_t ELTSIZE);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
ssize_t		ft_putchar_fd(char c, int fd);
ssize_t		ft_putstr_fd(char *s, int fd);
ssize_t		ft_putendl_fd(char *s, int fd);
ssize_t		ft_putnbr_fd(int n, int fd);
int			ft_printf(const char *TEMPLATE, ...);
ssize_t		ft_printf_hex_lower(int n);
ssize_t		ft_printf_hex_upper(int n);
ssize_t		ft_printf_uint(unsigned	int n);
void		reverse_array(char *str, int end);
char		*int2hex(unsigned int n, unsigned char op);
char		*lint2hex(unsigned long int n);
ssize_t		ft_printf_ptr(unsigned long int n);
#endif