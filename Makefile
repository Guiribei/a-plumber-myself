NAME = pipex
PATH_SRC = ./sources/
PATH_OBJ = ./objects/

SRC = error.c init.c parsing.c pipex.c utils.c

OBJ = ${SRC:%.c=$(PATH_OBJ)%.o}

INCLUDES = -I ./includes/
LIBFT = ./libft/libft.a
FLAGS = -Wall -Wextra -Werror

all:		$(NAME)

$(NAME): 	$(LIBFT) $(OBJ)
	cc $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make all -C ./libft/

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	mkdir -p $(PATH_OBJ)
	cc $(FLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[1;92m[SUCCESS] $@ Objects creation done!\033[0m"

clean:
	@make clean -C ./libft/
	@rm -rf $(PATH_OBJ)
	@echo "\33[1;93m[SUCCESS] Objects removal done!\33[0m"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./libft/
	@echo "\033[1;93m[SUCCESS] Library removal done!\33[0m"

re: fclean all

.PHONY: all clean fclean re