# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scoron <scoron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/03 12:40:23 by scoron            #+#    #+#              #
#    Updated: 2020/05/17 00:53:58 by scoron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:= lem-in

BASE_SRC = $(shell find src -type f | grep -E "\.c" | grep -v "libft" | sed 's/src\///g' | sed 's/\.c//g')

S_PATH = src/
H_PATH = includes/
O_PATH = obj/
O_PATH_V = obj_v/
L_PATH = libft/

LIBFT = $(addprefix $(S_PATH), $(L_PATH))
W_FLAGS = -Wall -Wextra -Werror
FSANITIZE= -fsanitize=address,undefined
FLAGS= $(W_FLAGS) $(FSANITIZE)
CC = clang

SRC:=$(addprefix $(S_PATH),$(addsuffix .c,$(BASE_SRC)))
OBJ:=$(addprefix $(O_PATH),$(addsuffix .o,$(BASE_SRC)))
OBJ_V:=$(addprefix $(O_PATH_V),$(addsuffix .o,$(BASE_SRC)))

RED		=	\033[0;31m
GREEN	=	\033[0;32m
YELLOW	=	\033[0;33m
NC		=	\033[0m

all: $(NAME)

check: check_invalid check_valid

check_valid: $(NAME)
	@echo "$(YELLOW) CHECKING VALID MAPS WITH FSANITIZER$(NC)" 
	cd bashTests;bash check_valid.sh ../lem-in;
	
check_invalid: $(NAME)
	@echo "$(YELLOW) CHECKING INVALID MAPS WITH FSANITIZER$(NC)" 
	cd bashTests;bash check_invalid.sh ../lem-in; cd ..

check_valgrind: check_invalid_valgrind check_valid_valgrind

check_valid_valgrind: val
	@echo "$(YELLOW) CHECKING VALID MAPS WITH VALGRIND$(NC)" 
	cd bashTests;bash check_valid.sh -v ../lem-in;cd ..
	@$(RM) -rf $(O_PATH_V)
	@$(RM) -rf $(LIBFT)libft.a
	
check_invalid_valgrind: val
	@echo "$(YELLOW) CHECKING INVALID MAPS WITH VALGRIND$(NC)" 
	cd bashTests;bash check_invalid.sh -v ../lem-in; cd ..
	@$(RM) -rf $(O_PATH_V)
	@$(RM) -rf $(LIBFT)libft.a

val: $(LIBFT)libft.a $(OBJ_V)
	@echo "$(GREEN)compiling lem-in... without fsanitizer to avoid conflicts with valgrind$(NC)" 
	@make val -C $(LIBFT)
	@$(CC) -o $(NAME) $(OBJ_V) $(W_FLAGS) -I $(L_PATH)$(H_PATH) -L $(LIBFT) -lft
	@echo "$(GREEN)lem_in for valgrind is ready$(NC)"


$(NAME): $(LIBFT)libft.a $(OBJ)
	@echo "$(GREEN)compiling $@...$(NC)"
	@$(CC) -o $(NAME) $(OBJ) $(FLAGS) -I $(L_PATH)$(H_PATH) -L $(LIBFT) -lft
	@echo "$(GREEN)$@ is ready$(NC)"

$(O_PATH)%.o: $(S_PATH)%.c
	@mkdir -p $(O_PATH)
	@$(CC) $(FLAGS) -I $(H_PATH) -c $< -o $@

$(O_PATH_V)%.o: $(S_PATH)%.c
	@mkdir -p $(O_PATH_V)
	@$(CC) $(W_FLAGS) -I $(H_PATH) -c $< -o $@

$(LIBFT)libft.a: FORCE
	@echo "$(GREEN)compiling $@...$(NC)"
	@$(MAKE) -C $(LIBFT)
	@echo "$(GREEN)$@ is ready$(NC)"

FORCE:

clean:
	@echo "$(RED)deleting objects...$(NC)"
	@make -C $(LIBFT) clean
	@$(RM) -rf $(O_PATH) $(O_PATH_V)

fclean : clean
	@echo "$(RED)deleting executable...$(NC)"
	@make -C $(LIBFT) fclean
	@$(RM) $(NAME)

re: fclean all

push : fclean
	@git add -A
	@git commit -m "quick push"
	@git push origin master
	git status

.PHONY: all clean fclean re FORCE check check_invalid check_valid val
