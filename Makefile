NAME = push_swap

.DEFAULT_GOAL := all
# used for make init
.SECONDEXPANSION:

CC         = cc
CFLAGS     = -Wall -Wextra -Werror -fPIE
ifeq ($(TURNIN_RUN),true)
CFLAGS    += -DNDEBUG
endif

RM = rm -rf

RELEASE_TAG  ?=
RELEASE_NAME = push_swap_turnin_$(RELEASE_TAG).tar.gz
#strip tar and gz
RELEASE_BASE = $(basename $(basename $(RELEASE_NAME)))

# code
SRC_DIR      := src

# build output
BUILD_DIR    := build
OBJ_DIR      := $(BUILD_DIR)/obj
SRC_OBJ_DIR  := $(OBJ_DIR)/src

# build results
BIN_DIR      := $(BUILD_DIR)/bin
SRC_BIN_DIR  := $(BIN_DIR)/src

# external libraries
EXTERNAL_DIR      := external
LIBFT_DIR         := $(EXTERNAL_DIR)/libs/libft
LIBFT_INCLUDE_DIR := $(LIBFT_DIR)/include
LIBFT             := $(LIBFT_DIR)/build/lib/libft.a

# external tools
VISUALIZER_DIR       := $(EXTERNAL_DIR)/tools/push_swap_visualizer
VISUALIZER_BUILD_DIR := $(VISUALIZER_DIR)/build
VISUALIZER           := $(VISUALIZER_BUILD_DIR)/bin/visualizer
TESTER_DIR           := $(EXTERNAL_DIR)/tools/push_swap_tester
TESTER_BUILD_DIR     := $(BUILD_DIR)/tester
TESTER_YFU_DIR       := $(EXTERNAL_DIR)/test/push_swap_tester-yfu
TESTER_YFU_BUILD_DIR := $(BUILD_DIR)/tester-yfu

# dist
DIST_DIR := $(BUILD_DIR)/dist

INCLUDES = -I./$(SRC_DIR) \
           -I./$(SRC_DIR)/free \
           -I./$(SRC_DIR)/init \
           -I./$(SRC_DIR)/sort \
           -I./$(SRC_DIR)/sort/algo \
           -I./$(SRC_DIR)/sort/algo/n_algo \
           -I./$(SRC_DIR)/sort/helpers \
           -I./$(SRC_DIR)/stackops \
           -I$(LIBFT_INCLUDE_DIR)

# nested layout, single source of truth for both dev and turnin
FILES = main \
        free/freearr \
        free/freecharr \
        free/freestacks \
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
        sort/algo/sort_3 \
        sort/algo/sort_4or5 \
        sort/algo/sort_n \
        sort/algo/n_algo/push_non_lis \
        sort/algo/n_algo/lis_tabulation \
        sort/algo/n_algo/sort_into_a \
        sort/algo/n_algo/min_to_top \
        sort/helpers/cost_ops \
        sort/helpers/pickop \
        sort/helpers/value_fetchers \
        sort/helpers/idx_of_min \
        sort/helpers/get_final_idxs

HEADERS = stacks \
          free/freearr \
          free/freecharr \
          free/freestacks \
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
          sort/algo/sort_3 \
          sort/algo/sort_4or5 \
          sort/algo/sort_n \
          sort/algo/n_algo/push_non_lis \
          sort/algo/n_algo/lis_tabulation \
          sort/algo/n_algo/sort_into_a \
          sort/algo/n_algo/min_to_top \
          sort/helpers/cost_ops \
          sort/helpers/pickop \
          sort/helpers/value_fetchers \
          sort/helpers/idx_of_min \
          sort/helpers/get_final_idxs

SRCS = $(FILES:%=$(SRC_DIR)/%.c)
HDRS = $(HEADERS:%=$(SRC_DIR)/%.h)
OBJS = $(FILES:%=$(SRC_OBJ_DIR)/%.o)

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

# move flat sources/headers from root to nested src/
# secondary expansion:
# only one $ gets consumed during parse time
# thus expansion of $$ gets deferred to build time
# instead of running notdir on a literal %
# it gets run on the target known at buildtime
# for target src/foo/bar.c, prereq becomes bar.c (root)
$(SRC_DIR)/%.c: $$(notdir %).c
	@mkdir -p $(@D)
	mv $< $@

$(SRC_DIR)/%.h: $$(notdir %).h
	@mkdir -p $(@D)
	mv $< $@

# wildcard returns empty if no match
# if wildcard return isnt equal to empty
# thus if libft exists in root,
# move libft from root into external/libs/ 
ifneq ($(wildcard libft),)
$(LIBFT_DIR): libft | $(EXTERNAL_DIR)
	mkdir -p $(EXTERNAL_DIR)/libs
	mv $< $@
endif

# build libft
$(LIBFT): | $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR)

# create source obj directory
$(SRC_OBJ_DIR): | $(BUILD_DIR)
	mkdir -p $(SRC_OBJ_DIR)

# create src bin directory
$(SRC_BIN_DIR): | $(BUILD_DIR)
	mkdir -p $(SRC_BIN_DIR)

# create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# create external directory
$(EXTERNAL_DIR):
	mkdir -p $(EXTERNAL_DIR)

# create dist directory
$(DIST_DIR): | $(BUILD_DIR)
	mkdir -p $(DIST_DIR)

# initialize project structure:
#   - unflattens src tree in turnin 
#   - re-nests libft if its fclean has flattened it
init: $(SRCS) $(HDRS) | $(LIBFT_DIR)
	$(MAKE) -C $(LIBFT_DIR) init

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

# remove object files
clean:
	$(RM) $(OBJ_DIR)
	-$(MAKE) -C $(LIBFT_DIR) clean

# remove all build artifacts (and unflatten in turnin)
fclean: clean
	$(RM) $(BUILD_DIR)
	$(RM) $(NAME)
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

# build visualizer 
visualizer: $(VISUALIZER)

$(VISUALIZER):
	cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
		-DCMAKE_CXX_FLAGS="-Wno-error=ignored-attributes" \
		-S $(VISUALIZER_DIR) -B $(VISUALIZER_BUILD_DIR)
	$(MAKE) -C $(VISUALIZER_BUILD_DIR)

# build tester: stage, compile in dist, copy tester files
tester: stage
	$(MAKE) -C $(DIST_DIR)/$(RELEASE_BASE)
	mkdir -p $(TESTER_BUILD_DIR)
	cp $(DIST_DIR)/$(RELEASE_BASE)/push_swap $(TESTER_BUILD_DIR)/
	cp $(TESTER_DIR)/checker_linux $(TESTER_DIR)/pro_checker $(TESTER_BUILD_DIR)/
	cp $(TESTER_DIR)/push_swap_test_linux.sh $(TESTER_DIR)/push_swap_test.sh $(TESTER_BUILD_DIR)/
	chmod +x $(TESTER_BUILD_DIR)/checker_linux $(TESTER_BUILD_DIR)/pro_checker
	chmod +x $(TESTER_BUILD_DIR)/push_swap_test_linux.sh $(TESTER_BUILD_DIR)/push_swap_test.sh

# build yfu tester: stage, compile in dist, stage tester dir with binary one level up
# yfu scripts hardcode ROOT=.. and call `make -C $ROOT`,
# place push_swap and a no-op Makefile in tester-yfu/
# and copy the submodule contents into tester-yfu/tester/.
tester-yfu: stage
	$(MAKE) -C $(DIST_DIR)/$(RELEASE_BASE)
	$(RM) $(TESTER_YFU_BUILD_DIR)
	mkdir -p $(TESTER_YFU_BUILD_DIR)
	cp $(DIST_DIR)/$(RELEASE_BASE)/push_swap $(TESTER_YFU_BUILD_DIR)/
	printf 'all:\n\t@:\n' > $(TESTER_YFU_BUILD_DIR)/Makefile
	cp -r $(TESTER_YFU_DIR) $(TESTER_YFU_BUILD_DIR)/tester

.PHONY: all init stage dist clean fclean re visualizer tester tester-yfu
