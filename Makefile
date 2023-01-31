NAME := cub3

SRC_F := src

SRC := $(wildcard $(SRC_F)/*)

SRCS := $(wildcard src/*/*.c)

OBJ_F := obj

DEBUG := 

OBJ := $(addprefix $(OBJ_F)/, $(notdir $(SRCS:.c=.o)))

FLAGS := -Wall -Werror -Wextra -Wpedantic

INC := -I includes

all: $(NAME)

$(NAME): $(SRCS) | $(OBJ_F)
	@$(foreach var, $(SRC), $(info Compiling $(var)) $( $(MAKE) $(DEBUG) -C $(var)))
	@$(info Linking objects into $@)
	@$(CC) $(FLAGS) $(INC) -o $@ $(OBJ)

$(OBJ_F):
	@mkdir -p $(OBJ_F)

clean:
	$(info Cleaning objects)
	@rm -rf $(OBJ_F)/

fclean:
	$(info Cleaning objects and executable)
	@rm -rf $(OBJ_F)/ $(NAME)

re: fclean $(NAME)

debug: FLAGS = -g -fsanitize=address
debug: DEBUG = debug
debug: fclean $(NAME)

sym: FLAGS = -g
sym: fclean $(NAME)

nf: FLAGS = 
nf: fclean $(NAME)

r: $(NAME)
	./$(NAME)