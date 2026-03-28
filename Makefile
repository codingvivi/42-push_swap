NAME = push_swap
TEST_NAME = runner

.DEFAULT_GOAL := all

CC         = cc
CFLAGS     = -Wall -Wextra -Werror -fPIE
TEST_CFLAGS = $(CFLAGS)
INCLUDES   = -I./src -I./include -I$(LIBFT_INCLUDE_DIR)

RM = rm -rf

RELEASE_TAG  ?=
RELEASE_NAME = push_swap_turnin_$(RELEASE_TAG).tar.gz
RELEASE_BASE = $(basename $(basename $(RELEASE_NAME)))


FILES = main


# code
SRC_DIR     := src
INCLUDE_DIR := include
TEST_SRC_DIR := test

# build output
BUILD_DIR   := build
OBJ_DIR     := $(BUILD_DIR)/obj
SRC_OBJ_DIR := $(OBJ_DIR)/src
TEST_OBJ_DIR := $(OBJ_DIR)/test

# build results
BIN_DIR      := $(BUILD_DIR)/bin
SRC_BIN_DIR  := $(BIN_DIR)/src
TEST_BIN_DIR := $(BIN_DIR)/test
# external libraries
EXTERNAL_DIR     := external
LIBFT_DIR        := $(EXTERNAL_DIR)/lib/libft
LIBFT_INCLUDE_DIR := $(LIBFT_DIR)/include
LIBFT            := $(LIBFT_DIR)/build/lib/libft.a

# dist
DIST_DIR := $(BUILD_DIR)/dist

HEADER_FILES =

TEST_FILES = main

SRCS = $(FILES:%=$(SRC_DIR)/%.c)
HDRS = $(HEADER_FILES:%=$(INCLUDE_DIR)/%.h)
OBJS = $(FILES:%=$(SRC_OBJ_DIR)/%.o)
TEST_SRCS = $(TEST_FILES:%=$(TEST_SRC_DIR)/%.c)
TEST_OBJS = $(TEST_FILES:%=$(TEST_OBJ_DIR)/%.o)

DIST_FILES = Makefile README.md $(SRCS) $(HDRS)
# build
all: init $(NAME) | $(LIBFT_DIR)

ifeq ($(TURNIN_RUN),true)
cp $(SRC_BIN_DIR)/$(NAME) $(NAME)
endif
# link objects into executable
$(NAME): $(OBJS) $(LIBFT) | $(SRC_BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(SRC_BIN_DIR)/$(NAME)

# compile source files to objects
$(SRC_OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(SRC_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# move flat source files into src/ if they exist in root
$(SRC_DIR)/%.c: %.c | $(SRC_DIR)
	mv $< $@

# move flat headers into include/ if they exist in root
$(INCLUDE_DIR)/%.h: %.h | $(INCLUDE_DIR)
	mv $< $@
# move libft into external/lib/ if it exists in root
$(LIBFT_DIR): libft | $(EXTERNAL_DIR)
	mkdir -p $(EXTERNAL_DIR)/lib
	mv $< $@

# build libft
$(LIBFT): | $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR)

# create source obj directory
$(SRC_OBJ_DIR): | $(BUILD_DIR)
	mkdir -p $(SRC_OBJ_DIR)

# create test obj directory
$(TEST_OBJ_DIR): | $(BUILD_DIR)
	mkdir -p $(TEST_OBJ_DIR)

# create src bin directory
$(SRC_BIN_DIR): | $(BUILD_DIR)
	mkdir -p $(SRC_BIN_DIR)

# create test bin directory
$(TEST_BIN_DIR): | $(BUILD_DIR)
	mkdir -p $(TEST_BIN_DIR)

# create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# create src directory
$(SRC_DIR):
	mkdir -p $(SRC_DIR)

# create include directory
$(INCLUDE_DIR):
	mkdir -p $(INCLUDE_DIR)

# create external directory
$(EXTERNAL_DIR):
	mkdir -p $(EXTERNAL_DIR)
# create dist directory
$(DIST_DIR): | $(BUILD_DIR)
	mkdir -p $(DIST_DIR)

# initialize project structure from flat layout
init: $(SRCS) $(HDRS) $(LIBFT_DIR)

# create flat distribution environment for turnin
stage: | $(DIST_DIR)
	$(RM) $(DIST_DIR)/$(RELEASE_BASE)
	mkdir -p $(DIST_DIR)/$(RELEASE_BASE)
cp $(DIST_FILES) $(DIST_DIR)/$(RELEASE_BASE)/
sed -i '1i TURNIN_RUN = true' $(DIST_DIR)/$(RELEASE_BASE)/Makefile
cp -r $(LIBFT_DIR) $(DIST_DIR)/$(RELEASE_BASE)/libft
# create a distribution tarball with the submission files
dist: stage
	tar -czf $(DIST_DIR)/$(RELEASE_NAME) -C $(DIST_DIR) $(RELEASE_BASE)

# build and run tests
test: $(TEST_NAME)

# link test runner
$(TEST_NAME): $(NAME) $(TEST_OBJS) | $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) $(TEST_OBJS) -o $(TEST_BIN_DIR)/$(TEST_NAME)

# compile test files to objects
$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c | $(TEST_OBJ_DIR)
	$(CC) $(TEST_CFLAGS) $(INCLUDES) -c $< -o $@

# remove object files
clean:
	$(RM) $(OBJ_DIR)

# remove all build artifacts
hclean: clean
$(RM) $(SRC_BIN_DIR)/$(NAME) $(TEST_BIN_DIR)/$(TEST_NAME)
$(MAKE) -C $(LIBFT_DIR) hclean
$(RM) $(NAME)
$(RM) $(DIST_DIR)/$(RELEASE_BASE)

# flatten back to root (undo init)
fclean: hclean
-mv $(SRC_DIR)/*.c .
	-mv $(INCLUDE_DIR)/*.h .
-mv $(LIBFT_DIR) libft
ifeq ($(TURNIN_RUN),true)
-rmdir $(SRC_DIR) $(INCLUDE_DIR) 2>/dev/null; true
-$(RM) $(EXTERNAL_DIR)
endif
# full rebuild
re: hclean all

.PHONY: all init stage dist test clean hclean fclean re
