NAME := cub3

SRC_DIR := src

SRC := $(wildcard $(SRC_DIR)/*)

SRCS := $(wildcard src/*/*.c)

OBJ_DIR := obj

OBJ := $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

FLAGS := -Wall -Werror -Wextra -Wpedantic

LIBRARY_FLAGS := -framework Cocoa -framework OpenGL -framework IOKit

INC := -I includes

all: $(NAME)

$(NAME): $(SRCS) | $(OBJ_DIR)
	@$(foreach var, $(SRC), echo "Making $(var)"; $(MAKE) $(DEBUG) -C $(var) --quiet;)
	@echo "Linking objects into $@"
	@$(CC) $(FLAGS) $(INC) -o $@ $(OBJ) -lm MLX42/build/libmlx42.a $(LIBRARY_FLAGS)
	@echo "Done"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	$(info Cleaning objects)
	@rm -rf $(OBJ_DIR)/

fclean:
	$(info Cleaning objects and executable)
	@rm -rf $(OBJ_DIR)/ $(NAME)

re: fclean $(NAME)

debug: FLAGS = -g -fsanitize=address
debug: DEBUG = debug
debug: fclean $(NAME)

linux: LIBRARY_FLAGS = -ldl -lglfw -pthread
linux: all

sym: FLAGS = -g
sym: fclean $(NAME)

nf: FLAGS = 
nf: fclean $(NAME)

r: $(NAME)
	./$(NAME)