SRCS := $(wildcard *.c)

OBJ_DIR := ../../obj

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

CFLAGS := -I../../includes

all: $(OBJS)

$(OBJ_DIR)/%.o: %.c
	@$(CC) $< -o $@ -c $(DEBUG) $(CFLAGS)

debug: DEBUG = -g 
debug: all