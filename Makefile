NAME := clox
MODE := debug
SOURCE_DIR := Sources
BUILD_DIR := Build

CC=clang
CFLAGS := -std=c11 -Wall -Wextra -Werror -Wno-unused-parameter

# Mode configuration
ifeq ($(MODE),debug)
	CFLAGS += -O0 -DDEBUG -g
	OBJECT_DIR := $(BUILD_DIR)/debug
else
	CFLAGS += -O3 -flto
	OBJECT_DIR := $(BUILD_DIR)/release
endif

# Files
HEADERS := $(wildcard $(SOURCE_DIR)/*.h)
SOURCES := $(wildcard $(SOURCE_DIR)/*.c)
OBJECTS := $(addprefix $(OBJECT_DIR)/, $(notdir $(SOURCES:.c=.o)))
APP_NAME := $(BUILD_DIR)/$(NAME)-$(MODE)

# Targets ---------------------------------------------------------------------

# Compile object files
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.c $(HEADERS)
# @ printf "%s %s %s\n" $(CC) $< "$(CFLAGS)"
	@ mkdir -p $(OBJECT_DIR)
	@ $(CC) -c $(CFLAGS) -o $@ $<

# Link
$(APP_NAME): $(OBJECTS)
# @ printf "%s %s %s\n" $(CC) $@ "$(CFLAGS)"
	@ mkdir -p $(BUILD_DIR)
	@ $(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	@ rm -f $(OBJECT_DIR)/*.o
	@ rm -f $(APP_NAME)

.PHONY: default
