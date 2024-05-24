CC := gcc
LDFLAGS := -ldl -lGLEW -lglfw -lGL -lEGL -lwayland-client -lwayland-cursor -lwayland-egl -lxkbcommon -lm -lpthread -lassimp
CFLAGS := -Wall -g

SRC_DIR := src
BUILD_DIR := build

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:%.c=%.o)
EXECUTABLE = $(BUILD_DIR)/miso

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(LDFLAGS) $(addprefix $(BUILD_DIR)/,$(notdir $^)) -o $@

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(addprefix $(BUILD_DIR)/,$(notdir $@))

run:
	./build/miso

debug:
	gdb ./build/miso

leak-check:
	#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=leak.txt ./build/app
	valgrind --leak-check=yes --log-file=leak.txt ./build/miso

clean:
	rm -rf $(BUILD_DIR)/*
