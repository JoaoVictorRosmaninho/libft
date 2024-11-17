TESTS := vector

CYAN  := \33[1;36m
RESET := \033[0m
LOG   := printf "[$(CYAN)INFO$(RESET)] %s\n"

SRC_DIR   := .
OBJ_DIR   := ../obj
LIBFT_DIR := ../
LIBFT     := libft.a
INC_DIRS  := ../includes
SRC_DIRS  := $(shell find $(SRC) -type d)

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

SOURCES := $(shell find $(SRC_DIR) -name '*.c' -exec basename {} \; | uniq)
SOURCES := $(filter-out main.c, $(SOURCES))
OBJS    := $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))
SOURCES := $(shell find $(SRC_DIR) -name '*.c')

CC     	:= clang
CFLAGS  := -Wall -Werror -Wextra -O3 -ggdb  -c 
LDFLAGS := -L$(LIBFT_DIR)
GFLAGS  := -fsanitize=address
LDLIBS  := -lft -lcriterion

define run
 	$(CC) $^ $(LDFLAGS)  $(LDLIBS) $(GFLAGS) -o $@ && ./$@ 
endef

################################################################################
##                                 TESTS                                      ##
################################################################################

all: $(TESTS) clean

.PHONY: memory

debug:
	@echo $(OBJS)

memory: arena_memory_test.c $(LIBFT)
	cp ../libft.a .
	@$(call run, "$^")

list: linked_list_test.c $(LIBFT)
	cp ../libft.a .
	@$(call run, "$^")

printf: ft_printf_test.c $(LIBFT)
	cp ../libft.a .
	@$(call run, "$^")

main: main.c $(LIBFT)
	cp ../libft.a .
	@$(call run, "$^")

$(LIBFT):
	make -C ..

$(OBJS): $(SOURCES)
	$(CC) $(CFLAGS) $< -o $@

fclean: 
	rm -f $(LIBFT)

dclean: fclean
	make -C .. fclean



# Makefile rules to clean stdin/stdout/stderr test's files
clean:
	@$(RM) -r $(TESTS)
	@$(RM) -r $(UTILS:.c=.o)
	@$(LOG) "Removing objects"

fclean: clean

re: fclean all

.PHONY: all clean fclean re
