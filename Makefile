CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

SRC_DIR = src
BUILD_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

OUT = $(BUILD_DIR)/Program

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) -o $@ $^

# Regra para compilar .c → .o dentro de build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)