# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joao <joao@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/17 20:28:19 by jv                #+#    #+#              #
#    Updated: 2024/11/16 21:04:35 by joao             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC 		= clang

GDB_FLAG  	= -ggdb -g -fsanitize=address -fno-omit-frame-pointer

FLAGS 	= -Wall -Werror -Wextra -g

REMOVE 	= rm -f

LFLAGS =	-L. -lft 

VALGRIND_FLAGS = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

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
					utils/string/ft_ftoa.c 			    \
					utils/string/ft_substr.c	 		  \
					utils/string/ft_split.c 			  \
					utils/string/ft_strjoin.c 			\
					utils/string/ft_strtrim.c			  \
					utils/string/ft_strmapi.c 			\
					utils/string/ft_striteri.c 			\
					utils/string/ft_strtok.c				\
					utils/string/ft_strndup.c				\
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
					utils/input_output/get_next_line/get_next_line.c 				\
					ds/ft_list/src/ft_lstnew_node.c		 	 \
					ds/ft_list/src/ft_lstnew.c		 	     \
					ds/ft_list/src/ft_lstprint.c		 		 \
					ds/ft_list/src/ft_lstadd_front.c	   \
					ds/ft_list/src/ft_lstadd_back.c	     \
					ds/ft_list/src/ft_lstdelone.c		     \
					ds/ft_list/src/ft_lst_for_each.c		     \
					ds/ft_list/src/ft_lstclear.c		     \
					ds/ft_list/src/ft_lst_include.c		     \
					ds/ft_list/src/ft_lst_remove_node.c		     \
					ds/ft_list/src/ft_lst_search_and_pop.c		     \
					ds/ft_list/src/ft_lstiter.c		       \
					ds/ft_list/src/ft_lstpop.c           \
					ds/ft_list/src/ft_lstpop_head.c      \
					ds/ft_list/src/ft_lstpop_tail.c      \
					ds/ft_list/src/ft_lstitem.c          \
					ds/ft_list/src/ft_lstmap.c           \
					ds/ft_list/src/ft_lst_mv_next_to_front.c           \
					ds/ft_list/utils/mk_int_content.c    \
					ds/ft_list/utils/mk_char_content.c   \
					ds/ft_list/utils/mk_generic_content.c   \
					ds/ft_list/utils/mk_float_content.c  \
					ds/ft_list/utils/mk_double_content.c \
					ds/ft_list/utils/mk_string_content.c \
					memory/arena.c \
					memory/arena_utils.c \
					memory/arena_align_utils.c \

TEST_TARGET = test/main.c \
			  test/test_utils.c \
			  test/utils/input_output/get_next_line/get_next_line_test.c \
			  test/utils/string/ft_strtok_test.c


SRCS 		= $(addprefix ./src/, $(TARGET))
OBJS 		= $(addprefix ./$(OBJ_DIR)/, $(TARGET:.c=.o)) 
OBJS_TEST   = $(addprefix ./$(OBJ_DIR)/, $(TEST_TARGET:.c=.o))

OBJ_DIR  = obj

OBJ_DIRS = 	 obj \
			 obj/ds \
			 obj/ds/ft_list \
			 obj/ds/ft_list/src \
			 obj/ds/ft_list/utils \
			 obj/utils/input_output 	\
			 obj/utils/input_output/ft_printf 	\
			 obj/utils/input_output/utils 	\
			 obj/utils/input_output/get_next_line	\
			 obj/utils/memory 	\
			 obj/memory \
			 obj/utils/string	\
			 obj/test	\
			 obj/test/utils	\
			 obj/test/utils/input_output \
			 obj/test/utils/string

all:	${NAME}

test: $(NAME) $(OBJS_TEST) 
	$(CC) $(OBJS_TEST) $(LFLAGS) -o $(NAME)_test
	@clear
	@./$(NAME)_test 

$(NAME):  $(OBJ_DIR) $(OBJS) 
		@echo "\n$(NAME): $(NAME) was created"
		ar -rcs $(NAME) $(OBJS)

$(OBJ_DIR):
	mkdir -p ${OBJ_DIRS}

$(OBJ_DIR)/%.o: src/%.c
	@echo "$@: object files were created"
	$(CC) $(FLAGS)  $(GDB_FLAG) -c $< -o $@

$(OBJ_DIR)/test/%.o: test/%.c 
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
