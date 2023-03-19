SRCS := cub3.c linegen.c movement.c raycam.c rendering.c rendering_utils.c fog.c

OBJ_DIR := ../../obj

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CFLAGS := -I../../includes # -Wall -Werror -Wextra

all: $(OBJS)

$(OBJ_DIR)/%.o: %.c
	$(info Compiling $(notdir $@))
	@$(CC) $< -o $@ -c $(DEBUG) $(CFLAGS)

debug: DEBUG = -g 
debug: all
