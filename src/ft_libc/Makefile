SRCS := ft_atoi.c ft_realloc.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_strlen.c

OBJ_DIR := ../../obj

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CFLAGS := -I../../includes -Wall -Werror -Wextra

all: $(OBJS)

$(OBJ_DIR)/%.o: %.c
	$(info Compiling $(notdir $@)) 
	@$(CC) $< -o $@ -c $(DEBUG) $(CFLAGS)

debug: DEBUG = -g 
debug: all