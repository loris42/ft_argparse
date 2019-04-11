# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laranda <laranda@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/11 16:48:09 by laranda           #+#    #+#              #
#    Updated: 2019/04/11 17:13:49 by laranda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_parse_options.a

SRC = ft_parse_options.c

OBJ_DIR = obj

OBJ := $(SRC:.c=.o)
OBJ := $(addprefix $(OBJ_DIR)/, $(OBJ))

FLAGS = -Wall -Werror -Wextra

OK_COLOR = \033[1;32m
ERROR_COLOR = \033[1;31m
TEXT_COLOR = \033[0;33m
NO_COLOR = \033[m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "$(OK_COLOR)[ FT_PARSE_OPTIONS COMPILED ]$(NO_COLOR)"

$(OBJ_DIR):
	@-mkdir -p $(OBJ_DIR)

$(OBJ): ft_parse_options.h | $(OBJ_DIR)
$(OBJ): $(OBJ_DIR)/%.o : %.c
	@echo "$(TEXT_COLOR)[Compiling $@]$(NO_COLOR) . . . \c"
	@gcc -c -Iincludes $(FLAGS) $< -o $@
	@echo "$(OK_COLOR)[ OK ]$(NO_COLOR)"

clean:
	@-rm -Rf $(OBJ_DIR)
	@echo "$(ERROR_COLOR)[ Removed OBJ folder ]$(NO_COLOR)"

fclean: clean
	@-rm -f $(NAME)
	@echo "$(ERROR_COLOR)[ Removed the LIBRARY ]$(NO_COLOR)"

re: fclean all