# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jv <jv@student.42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/17 20:28:19 by jv                #+#    #+#              #
#    Updated: 2024/04/06 16:38:01 by jv               ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    	:= libft.a

CC 			:= clang

#DEV_FLAGS  := -ggdb -g -fsanitize=address -fno-omit-frame-pointer

CFLAGS 		:= -Wall -Werror -Wextra -I./includes

REMOVE 		:= rm -f

LFLAGS	 	:=	-L. -lft 

VALGRIND_FLAGS = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

# Make does not offer a recursive wildcard function, so here's one:
SOURCES 	:= $(shell find src -type f -name '*.c')

OBJ_DIR  	:= dist

OBJS 		:= $(addprefix $(OBJ_DIR)/, $(notdir $(SOURCES:.c=.o))) 

HEADERDIR   := includes

SOURCEDIR	:= $(dir $(SOURCES))


vpath %.h $(HEADERDIR)
vpath %.c $(SOURCEDIR)

all: $(NAME)

debug:
	@echo $(SOURCEDIR)

$(NAME): $(OBJS) 
		@echo "\n$(NAME): $(NAME) was created"
		ar -rcs $(NAME) $(OBJS)

$(OBJ_DIR):
	@echo "comendaod"
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	$(CC) $(CFLAGS) $(DEV_FLAGS) -c $< -o $@
	
clean:
		@echo "\n$(NAME): object files were deleted"
		${REMOVE} ${OBJS} 

fclean: clean
		@echo "$(NAME): $(NAME) was deleted"
		${REMOVE} ${NAME}
		@echo

re :   fclean all

so :
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SOURCES) $(BONUS_SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS) $(BONUS_OBJS)
