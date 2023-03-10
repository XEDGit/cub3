NAME := cub3

SRC_DIR := src

SRC := $(wildcard $(SRC_DIR)/*)

SRCS := $(wildcard src/*/*.c)

OBJ_DIR := obj

OBJ := $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

FLAGS := -Wall -Werror -Wextra -Wpedantic

MLX_NAME := build/libmlx42.a

MLX_FLAGS := -lglfw -framework Cocoa -framework OpenGL -framework IOKit

INC := -I includes

all: $(NAME)

$(NAME): $(MLX_NAME) $(SRCS) | $(OBJ_DIR)
	@$(foreach var, $(SRC), echo "Making $(var)"; $(MAKE) $(DEBUG) -C $(var) --quiet;)
	@echo "Linking objects into $@"
	@$(CC) $(FLAGS) $(INC) -o $@ $(OBJ) $(MLX_NAME) $(MLX_FLAGS) -lm
	@echo "Done"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(MLX_NAME):
	@echo "Making MLX42"
	@cmake -S MLX42 -B build
	@cmake --build build -j4

clean:
	$(info Cleaning objects)
	@rm -rf $(OBJ_DIR)/

fclean:
	$(info Cleaning objects, library and executable)
	@rm -rf $(OBJ_DIR)/ $(NAME) build

re: fclean $(NAME)

rel: fclean linux

debug: FLAGS = -g -fsanitize=address
debug: DEBUG = debug
debug: fclean $(NAME)

linux: MLX_FLAGS = -ldl -pthread
linux: all

sym: FLAGS = -g
sym: fclean $(NAME)

nf: FLAGS = 
nf: fclean $(NAME)

r: all
	./$(NAME)

rl: linux
	./$(NAME) $(1)
