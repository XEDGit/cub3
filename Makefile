NAME := cub3

SRC_F := src

SRC := $(wildcard $(SRC_F)/*.c)

OBJ_F := obj

OBJ := $(addprefix $(OBJ_F)/, $(notdir $(SRC:.c=.o)))

FLAGS := -Wall -Werror -Wextra -Wpedantic

INC := -I includes

all: $(NAME)

$(NAME): $(OBJ)
	$(info Linking objects into $@)
	@$(CC) $(FLAGS) $(INC) -o $@ $(OBJ)

$(OBJ): | $(OBJ_F)

$(OBJ_F):
	@mkdir -p $(OBJ_F)

$(OBJ_F)/%.o: $(SRC_F)/%.c
	$(info Compiling $<)
	@$(CC) -c $(FLAGS) $(INC) $< -o $@

clean:
	$(info Cleaning objects)
	@rm -rf $(OBJ_F)/

fclean:
	$(info Cleaning objects and executable)
	@rm -rf $(OBJ_F)/ $(NAME)

re: fclean $(NAME)

debug: FLAGS = -g -fsanitize=address
debug: fclean $(NAME)

nf: FLAGS = 
nf: fclean $(NAME)

r: $(NAME)
	./$(NAME)