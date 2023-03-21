SRCS := 2d_char_utils.c cell_utils.c map.c map_utils.c parsing.c parsing_settings.c player.c skip_spaces.c

CC = clang

OBJ_DIR := ../../obj

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CFLAGS := -I../../includes -Wall -Werror -Wextra

all: $(OBJS)

$(OBJ_DIR)/%.o: %.c
	$(info Compiling $(notdir $@))
	@$(CC) $< -o $@ -c $(DEBUG) $(CFLAGS)

debug: DEBUG = -g 
debug: all
