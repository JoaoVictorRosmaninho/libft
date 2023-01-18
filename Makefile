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

CC 		= clang

FLAGS 	= -Wall -Werror -Wextra -g

REMOVE 	= rm -f

LFLAGS =	-L. -lft 

TARGET 	 = utils/string/ft_isalpha.c 			\
					utils/string/ft_isdigit.c 			\
					utils/string/ft_isalnum.c 			\
					utils/string/ft_isascii.c 			\
					utils/string/ft_isspace.c 			\
					utils/string/ft_isprint.c 			\
					utils/string/ft_strlen.c 			  \
					utils/string/ft_strlcpy.c 			\
					utils/string/ft_strlcat.c 			\
					utils/string/ft_toupper.c 			\
					utils/string/ft_tolower.c 			\
					utils/string/ft_strchr.c 			  \
					utils/string/ft_strrchr.c 			\
					utils/string/ft_strncmp.c			  \
					utils/string/ft_strnstr.c			  \
					utils/string/ft_atoi.c 			    \
					utils/string/ft_strdup.c 			  \
					utils/string/ft_itoa.c 			    \
					utils/string/ft_substr.c	 		  \
					utils/string/ft_split.c 			  \
					utils/string/ft_strjoin.c 			\
					utils/string/ft_strtrim.c			  \
					utils/string/ft_strmapi.c 			\
					utils/string/ft_striteri.c 			\
					utils/memory/ft_bzero.c 			  \
					utils/memory/ft_calloc.c 			  \
					utils/memory/ft_memmove.c 			\
					utils/memory/ft_memset.c 			  \
					utils/memory/ft_memchr.c				\
					utils/memory/ft_memcpy.c 			  \
					utils/memory/ft_memcmp.c				\
					utils/input_output/utils/ft_putchar_fd.c 		          \
				  utils/input_output/utils/ft_putstr_fd.c 			        \
					utils/input_output/utils/ft_putendl_fd.c 		          \
					utils/input_output/utils/ft_putnbr_fd.c			          \
					utils/input_output/ft_printf/ft_printf.c 			        \
					utils/input_output/ft_printf/ft_printf_ptr.c          \
					utils/input_output/ft_printf/ft_printf_hex_lower.c 		\
					utils/input_output/ft_printf/ft_printf_hex_upper.c 		\
					utils/input_output/ft_printf/ft_printf_uint.c 		    \
					utils/input_output/ft_printf/ft_printf_utils.c 				\
					ds/ft_list/src/ft_lstnew.c		 			 \
					ds/ft_list/src/ft_lstadd_front.c	   \
					ds/ft_list/src/ft_lstadd_back.c	     \
					ds/ft_list/src/ft_lstdelone.c		     \
					ds/ft_list/src/ft_lstclear.c		     \
					ds/ft_list/src/ft_lstiter.c		       \
					ds/ft_list/src/ft_lstpop.c           \
					ds/ft_list/src/ft_lstpop_head.c      \
					ds/ft_list/src/ft_lstitem.c          \
					ds/ft_list/src/ft_lstmap.c           \
					ds/ft_list/utils/mk_int_content.c    \
					ds/ft_list/utils/mk_char_content.c   \
					ds/ft_list/utils/mk_float_content.c  \
					ds/ft_list/utils/mk_double_content.c \
					ds/ft_list/utils/mk_string_content.c 


SRCS 		= $(addprefix ./src/, $(TARGET))
OBJS 		= $(addprefix ./$(OBJ_DIR)/, $(TARGET:.c=.o)) 

OBJ_DIR  = obj
OBJ_DIRS = obj \
					 obj/ds \
					 obj/ds/ft_list \
					 obj/ds/ft_list/src \
					 obj/ds/ft_list/utils \
					 obj/utils/input_output 	\
					 obj/utils/input_output/ft_printf 	\
					 obj/utils/input_output/utils 	\
					 obj/utils/memory 	\
					 obj/utils/string 	

all:	${NAME}

test: $(NAME)
	$(CC) test/main.c $(LFLAGS) -o test_run

${NAME}:  $(OBJ_DIR)	$(OBJS) 
		@echo "\n$(NAME): $(NAME) was created"
		ar -rcs $(NAME) $(OBJS)

$(OBJ_DIR):
	mkdir -p ${OBJ_DIRS}

$(OBJ_DIR)/%.o: src/%.c
		@echo "$@: object files were created"
		$(CC) $(FLAGS) -c $< -o $@

clean:
		@echo "\n$(NAME): object files were deleted"
		${REMOVE} ${OBJS} 
		@echo

fclean:		clean
		@echo "$(NAME): $(NAME) was deleted"
		${REMOVE} ${NAME}
		@echo

re :		fclean all

so :
	$(CC) -nostartfiles -fPIC $(FLAGS) $(SRCS) $(BONUS_SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS) $(BONUS_OBJS)
