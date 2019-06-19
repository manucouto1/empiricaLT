CC=gcc
CFLAGS=-Wall -g
LIBS=-lm

SRC_DIRS ?= ../lib
BUILD_DIR ?= ../build

SRCS := $(shell find $(SRC_DIRS) -name '*.c')
OBJS := $(patsubst $(SRC_DIRS)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

$(BUILD_DIR)/%.o : $(SRC_DIRS)/%.c
	$(MKDIR_P) $(dir $@) 
	$(CC) $(CFLAGS) -c $< -o $@

%:  $(OBJS) 
	$(CC) $(OBJS) $@.c -o $(BUILD_DIR)/$@  $(LIBS)

.PHONY: clean

clean: 
	$(RM) -r $(BUILD_DIR)

MKDIR_P ?= mkdir -p

print-%  : ; @echo $* = $($*)