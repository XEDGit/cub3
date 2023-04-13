NAME := cub3

SRC_DIR := src

CC = clang

SRC := src/ft_libc src/get_next_line src/main src/map_parsing

SRCS := src/ft_libc/ft_atoi.c src/ft_libc/is_space.c src/ft_libc/ft_realloc.c src/ft_libc/ft_strchr.c src/ft_libc/ft_strcmp.c src/ft_libc/ft_strdup.c src/ft_libc/ft_strlen.c src/get_next_line/get_next_line.c src/get_next_line/get_next_line_utils.c src/main/cub3.c src/main/linegen.c src/main/movement.c src/main/raycam.c src/main/rendering.c src/main/rendering_utils.c src/map_parsing/2d_char_utils.c src/map_parsing/cell_utils.c src/map_parsing/map.c src/map_parsing/map_utils.c src/map_parsing/parsing.c src/map_parsing/parsing_settings.c src/map_parsing/player.c src/map_parsing/skip_spaces.c src/main/fog.c src/main/init.c

OBJ_DIR := obj

OBJ := $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

FLAGS := -Wall -Werror -Wextra -Wpedantic

MLX_NAME := build/libmlx42.a

MLX_FLAGS := -L "/Users/$(USER)/.brew/lib" -lglfw -framework Cocoa -framework OpenGL -framework IOKit

INC := -I includes

all: $(NAME)

$(NAME): $(MLX_NAME) $(SRCS) | $(OBJ_DIR)
	@$(foreach var, $(SRC), echo "Making $(var)"; $(MAKE) $(DEBUG) -C $(var);)
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

linux: MLX_FLAGS = -ldl -pthread -lglfw -pthread -lm
linux: all

sym: FLAGS = -g3
sym: DEBUG = debug
sym: fclean $(NAME)

nf: FLAGS = 
nf: fclean $(NAME)

nfl: FLAGS = 
nfl: MLX_FLAGS = -ldl -pthread -lglfw -pthread -lm
nfl: fclean $(NAME)

r: all
	./$(NAME)

rl: linux
	./$(NAME) $(1)

mem:
	memdetect src -Lbuild -lmlx42 $(MLX_FLAGS) $(INC) -a $(1)