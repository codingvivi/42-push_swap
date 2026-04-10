NAME = push_swap
TEST_NAME = runner

.DEFAULT_GOAL := all
.SECONDEXPANSION:

CC         = cc
CFLAGS     = -Wall -Wextra -Werror -fPIE
ifeq ($(TURNIN_RUN),true)
CFLAGS    += -DNDEBUG
endif
TEST_CFLAGS = $(CFLAGS)

RM = rm -rf

RELEASE_TAG  ?=
RELEASE_NAME = push_swap_turnin_$(RELEASE_TAG).tar.gz
RELEASE_BASE = $(basename $(basename $(RELEASE_NAME)))

# code
SRC_DIR      := src
TEST_SRC_DIR := test

# build output
BUILD_DIR    := build
OBJ_DIR      := $(BUILD_DIR)/obj
SRC_OBJ_DIR  := $(OBJ_DIR)/src
TEST_OBJ_DIR := $(OBJ_DIR)/test

# build results
BIN_DIR      := $(BUILD_DIR)/bin
SRC_BIN_DIR  := $(BIN_DIR)/src
TEST_BIN_DIR := $(BIN_DIR)/test

# external libraries
EXTERNAL_DIR      := external
LIBFT_DIR         := $(EXTERNAL_DIR)/libs/libft
LIBFT_INCLUDE_DIR := $(LIBFT_DIR)/include
LIBFT             := $(LIBFT_DIR)/build/lib/libft.a

# external tools
VISUALIZER_DIR       := $(EXTERNAL_DIR)/tools/push_swap_visualizer
VISUALIZER_BUILD_DIR := $(VISUALIZER_DIR)/build
VISUALIZER           := $(VISUALIZER_BUILD_DIR)/bin/visualizer

# dist
DIST_DIR := $(BUILD_DIR)/dist

INCLUDES = -I./$(SRC_DIR) \
           -I./$(SRC_DIR)/init \
           -I./$(SRC_DIR)/sort \
           -I./$(SRC_DIR)/sort/algo \
           -I./$(SRC_DIR)/sort/helper \
           -I./$(SRC_DIR)/stackops \
           -I$(LIBFT_INCLUDE_DIR)

# nested layout - single source of truth for both dev and turnin
FILES = main \
        freearr \
        freecharr \
        freestacks \
        print_stacks \
        init/init_stacks \
        init/get_args \
        init/safe_ft_atoi \
        stackops/get_idx \
        stackops/push \
        stackops/rotate \
        stackops/reverse_rotate \
        stackops/swap \
        sort/sort \
        sort/algo/push_non_lis \
        sort/helper/cost_ops \
        sort/helper/pickop \
        sort/helper/value_fetchers \
        sort/helper/idx_of_min \
        sort/helper/prepend \
        sort/algo/sort_into_a \
        sort/algo/min_to_top

HEADERS = stacks \
          freearr \
          freecharr \
          freestacks \
          print_stacks \
          init/init \
          init/get_args \
          init/safe_ft_atoi \
          stackops/get_idx \
          stackops/push \
          stackops/rotate \
          stackops/reverse_rotate \
          stackops/swap \
          sort/sort \
          sort/algo/push_non_lis \
          sort/helper/cost_ops \
          sort/helper/pickop \
          sort/helper/value_fetchers \
          sort/helper/idx_of_min \
          sort/helper/prepend \
          sort/algo/sort_into_a \
          sort/algo/min_to_top

TEST_FILES = \
            main \
            safe_ft_atoi

SRCS = $(FILES:%=$(SRC_DIR)/%.c)
HDRS = $(HEADERS:%=$(SRC_DIR)/%.h)
OBJS = $(FILES:%=$(SRC_OBJ_DIR)/%.o)
TEST_SRCS = $(TEST_FILES:%=$(TEST_SRC_DIR)/%.c)
TEST_OBJS = $(TEST_FILES:%=$(TEST_OBJ_DIR)/%.o)

# build
all: init $(NAME)

# link objects into executable
$(NAME): $(OBJS) $(LIBFT) | $(SRC_BIN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(SRC_BIN_DIR)/$(NAME)
ifeq ($(TURNIN_RUN),true)
	cp $(SRC_BIN_DIR)/$(NAME) $(NAME)
endif

# compile source files to objects
$(SRC_OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(SRC_OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# (turnin only) move flat sources/headers from root to nested src/
# secondary expansion: for target src/foo/bar.c, prereq becomes bar.c (root)
$(SRC_DIR)/%.c: $$(notdir %).c
	@mkdir -p $(@D)
	mv $< $@

$(SRC_DIR)/%.h: $$(notdir %).h
	@mkdir -p $(@D)
	mv $< $@

# (turnin only) move libft from root into external/libs/ if it exists
ifneq ($(wildcard libft),)
$(LIBFT_DIR): libft | $(EXTERNAL_DIR)
	mkdir -p $(EXTERNAL_DIR)/libs
	mv $< $@
endif

# build libft
$(LIBFT): | $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR)

# build visualizer (opt-in, not part of `all`)
visualizer: $(VISUALIZER)

$(VISUALIZER):
	cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
		-DCMAKE_CXX_FLAGS="-Wno-error=ignored-attributes" \
		-S $(VISUALIZER_DIR) -B $(VISUALIZER_BUILD_DIR)
	$(MAKE) -C $(VISUALIZER_BUILD_DIR)

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

# create external directory
$(EXTERNAL_DIR):
	mkdir -p $(EXTERNAL_DIR)

# create dist directory
$(DIST_DIR): | $(BUILD_DIR)
	mkdir -p $(DIST_DIR)

# initialize project structure (no-op in dev; unflatten in turnin)
init: $(SRCS) $(HDRS) | $(LIBFT_DIR)

# create flat distribution environment for turnin
stage: | $(DIST_DIR)
	$(RM) $(DIST_DIR)/$(RELEASE_BASE)
	mkdir -p $(DIST_DIR)/$(RELEASE_BASE)
	cp Makefile README.md $(DIST_DIR)/$(RELEASE_BASE)/
	cp $$(find $(SRC_DIR) -type f \( -name '*.c' -o -name '*.h' \)) $(DIST_DIR)/$(RELEASE_BASE)/
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
	-$(MAKE) -C $(LIBFT_DIR) clean

# remove all build artifacts (and unflatten in turnin)
fclean: clean
	$(RM) $(BIN_DIR)
	$(RM) $(NAME)
	$(RM) $(DIST_DIR)
	-$(MAKE) -C $(LIBFT_DIR) fclean
ifeq ($(TURNIN_RUN),true)
	-find $(SRC_DIR) -type f -name '*.c' -exec mv {} . \;
	-find $(SRC_DIR) -type f -name '*.h' -exec mv {} . \;
	-mv $(LIBFT_DIR) libft
	-find $(SRC_DIR) -type d -empty -delete
	$(RM) $(EXTERNAL_DIR)
endif

# full rebuild
re: fclean all

.PHONY: all init stage dist test clean fclean re visualizer
