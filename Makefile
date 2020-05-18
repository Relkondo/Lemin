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
L_PATH = libft/

LIBFT = $(addprefix $(S_PATH), $(L_PATH))
FLAGS = -Wall -Wextra -Werror
CC = clang

SRC:=$(addprefix $(S_PATH),$(addsuffix .c,$(BASE_SRC)))
OBJ:=$(addprefix $(O_PATH),$(addsuffix .o,$(BASE_SRC)))

RED		=	\033[0;31m
GREEN	=	\033[0;32m
NC		=	\033[0m

all: $(NAME)

check: check_leak check_error

check_leak:

check_error:

$(NAME): $(LIBFT)libft.a $(OBJ)
	@echo "$(GREEN)compiling $@...$(NC)"
	@$(CC) -o $(NAME) $(OBJ) $(FLAGS) -I $(L_PATH)$(H_PATH) -L $(LIBFT) -lft
	@echo "$(GREEN)$@ is ready$(NC)"

$(O_PATH)%.o: $(S_PATH)%.c
	@mkdir -p $(O_PATH)
	@$(CC) $(FLAGS) -I $(H_PATH) -c $< -o $@

$(LIBFT)libft.a: FORCE
	@echo "$(GREEN)compiling $@...$(NC)"
	$(MAKE) -C $(LIBFT)
	@echo "$(GREEN)$@ is ready$(NC)"

FORCE:

clean:
	@echo "$(RED)deleting objects...$(NC)"
	@make -C $(LIBFT) clean
	@/bin/rm -rf $(O_PATH)

fclean : clean
	@echo "$(RED)deleting executable...$(NC)"
	@make -C $(LIBFT) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re FORCE check check_leak check_error
