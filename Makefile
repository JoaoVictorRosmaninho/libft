# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jv <jv@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/17 20:28:19 by jv                #+#    #+#              #
#    Updated: 2022/04/19 19:50:22 by jv               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC 		= gcc

FLAGS 		= -Wall -Werror -Wextra

REMOVE 		= rm -f

SRCS 		= ft_isalpha.c 			\
		ft_isdigit.c 			\
		ft_isalnum.c 			\
		ft_isascii.c 			\
		ft_isspace.c 			\
		ft_isprint.c 			\
		ft_strlen.c 			\
		ft_memset.c 			\
		ft_bzero.c 			\
		ft_memcpy.c 			\
		ft_memmove.c 			\
		ft_strlcpy.c 			\
		ft_strlcat.c 			\
		ft_toupper.c 			\
		ft_tolower.c 			\
		ft_strchr.c 			\
		ft_strrchr.c 			\
		ft_strncmp.c			\
		ft_memcmp.c				\
		ft_memchr.c				\
		ft_strnstr.c			\
		ft_atoi.c 			\
		ft_strdup.c 			\
		ft_calloc.c 			\
		ft_itoa.c 			\
		ft_substr.c	 		\
		ft_split.c 			\
		ft_strjoin.c 			\
		ft_strtrim.c			\
		ft_strmapi.c 			\
		ft_striteri.c 			\
		ft_putchar_fd.c 		\
		ft_putstr_fd.c 			\
		ft_putendl_fd.c 		\
		ft_putnbr_fd.c			\
		ft_printf.c 			\
		ft_printf_ptr.c   \
		ft_printf_hex_lower.c 		\
		ft_printf_hex_upper.c 		\
		ft_printf_uint.c 		\
		ft_printf_utils.c 		\

BONUS_SRCS  	= ft_lstnew.c		\
		ft_lstadd_front.c	\
		ft_lstadd_back.c	\
		ft_lstdelone.c		\
		ft_lstclear.c		\
		ft_lstiter.c		\
		ft_lstpop.c \
		ft_lstpop_head.c \
		ft_lstitem.c \
		ft_mlsort.c \
		ft_lstmap.c

OBJS 		= $(SRCS:.c=.o)

BONUS_OBJS 	= $(BONUS_SRCS:.c=.o)

all:	${NAME} bonus

${NAME}: 	${OBJS}
		@echo "\n$(NAME): $(NAME) was created"
		ar -rcs ${NAME} ${OBJS}

bonus:		${NAME} ${BONUS_OBJS}
		@echo "\n$(NAME): $(NAME) was created with Bonus"
		ar -rcs ${NAME} ${BONUS_OBJS}
		@echo

.c.o:
		@echo "\n$(NAME): object files were created"
		${CC} ${FLAGS} -c $< -o ${<:.c=.o} ${INCLUDE}

clean:
		@echo "\n$(NAME): object files were deleted"
		${REMOVE} ${OBJS} ${BONUS_OBJS}
		@echo

fclean:		clean
		@echo "$(NAME): $(NAME) was deleted"
		${REMOVE} ${NAME}
		@echo

re :		fclean all

so :
	$(CC) -nostartfiles -fPIC $(FLAGS) $(SRCS) $(BONUS_SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS) $(BONUS_OBJS)
