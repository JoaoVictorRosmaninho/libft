
NAME		= libft.a

GREEN		= \033[0;32m
RED		= \033[0;31m
RESET		= \033[0m

CC 		= gcc

FLAGS 		= -Wall -Werror -Wextra -g3

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
		ft_memchr.c 			\
		ft_toupper.c 			\
		ft_tolower.c 			\
		ft_strchr.c 			\
		ft_strrchr.c 			\
		ft_strncmp.c			\
		ft_memcmp.c			\
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

BONUS_SRCS  	= ft_lstnew.c		\
		ft_lstadd_front.c	\
		ft_lstsize.c		\
		ft_lstlast.c		\
		ft_lstadd_back.c	\
		ft_lstdelone.c		\
		ft_lstclear.c		\
		ft_lstiter.c		\
		ft_lstmap.c

OBJS 		= $(SRCS:.c=.o)

BONUS_OBJS 	= $(BONUS_SRCS:.c=.o)

all:		${NAME}

${NAME}: 	${OBJS}
		@echo "\n$(NAME): $(GREEN)$(NAME) was created$(RESET)"
		ar -rcs ${NAME} ${OBJS}

bonus:		${NAME} ${BONUS_OBJS}
		@echo "\n$(NAME): $(GREEN)$(NAME) was created with Bonus$(RESET)"
		ar -rcs ${NAME} ${BONUS_OBJS}
		@echo

.c.o:
		@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
		${CC} ${FLAGS} -c $< -o ${<:.c=.o} ${INCLUDE}

clean:
		@echo "\n$(NAME): $(RED)object files were deleted$(RESET)"
		${REMOVE} ${OBJS} ${BONUS_OBJS}
		@echo

fclean:		clean
		@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"
		${REMOVE} ${NAME}
		@echo

re :		fclean all

so :
	$(CC) -nostartfiles -fPIC $(FLAGS) $(SRCS) $(BONUS_SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS) $(BONUS_OBJS)
