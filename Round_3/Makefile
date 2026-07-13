# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/19 12:17:18 by dmungunt          #+#    #+#              #
#    Updated: 2026/02/26 12:39:53 by dmungunt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -lncurses

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a
SRC_DIR = src
TKN_DIR = $(SRC_DIR)/tokenization
PRS_DIR = $(SRC_DIR)/parsing
EXP_DIR = $(SRC_DIR)/expansion
EXC_DIR = $(SRC_DIR)/execution
RED_DIR = $(SRC_DIR)/redirection
MAIN_DIR = $(SRC_DIR)/main_dir
INC_DIR = includes

SRC = \
	$(MAIN_DIR)/main.c $(MAIN_DIR)/global.c $(MAIN_DIR)/history.c $(MAIN_DIR)/signal.c $(MAIN_DIR)/copy_env.c $(MAIN_DIR)/copy_env2.c $(MAIN_DIR)/copy_env_to_alist.c \
	$(MAIN_DIR)/init_tokenlist.c $(MAIN_DIR)/freefile.c $(MAIN_DIR)/freefile2.c $(MAIN_DIR)/freefile3.c $(MAIN_DIR)/one_line.c \
	$(TKN_DIR)/tokencounter.c $(TKN_DIR)/extra_tokencounter.c \
	$(TKN_DIR)/tokenizer.c $(TKN_DIR)/tokenizer2.c $(TKN_DIR)/tokenizer3.c \
	$(PRS_DIR)/parsing.c $(PRS_DIR)/pars_red.c $(PRS_DIR)/parse_arg.c $(PRS_DIR)/parse_assign.c $(PRS_DIR)/parse_cmd.c $(PRS_DIR)/parse_op.c $(PRS_DIR)/recursion.c \
	$(PRS_DIR)/pars_red_helper.c $(PRS_DIR)/parse_ass_helper.c $(PRS_DIR)/parse_ass_helper2.c \
	$(EXP_DIR)/expansion.c $(EXP_DIR)/extract_assignments.c $(EXP_DIR)/ast_expansion.c $(EXP_DIR)/expansion_helpers.c $(EXP_DIR)/expansion_traversers.c \
	$(EXP_DIR)/ast_expansion_helpers.c $(EXP_DIR)/exp_trav_helpers.c $(EXP_DIR)/ast_red_expansion.c $(EXP_DIR)/check_files.c $(EXP_DIR)/expansion_helpers2.c \
	$(EXC_DIR)/execute.c $(EXC_DIR)/execute2.c $(EXC_DIR)/execute_pipe.c $(EXC_DIR)/execute_helpers.c $(EXC_DIR)/builtin_helpers.c $(EXC_DIR)/builtin.c $(EXC_DIR)/builtin2.c \
	$(EXC_DIR)/dup_a_list.c $(EXC_DIR)/dup_b_env.c $(EXC_DIR)/subshell_memory.c $(EXC_DIR)/fd_closer.c $(EXC_DIR)/builtin3.c $(EXC_DIR)/builtin_echo.c $(EXC_DIR)/path_ok.c \
	$(EXC_DIR)/execute_rec.c $(EXC_DIR)/execute_helpers2.c \
	$(RED_DIR)/check_for_red.c $(RED_DIR)/reset_fd.c $(RED_DIR)/check_red_type.c $(RED_DIR)/hd_helpers.c \
	$(EXC_DIR)/builtin_helpers2.c $(EXC_DIR)/builtin_helpers3.c $(EXC_DIR)/execute_pipe_helper.c \
	$(EXC_DIR)/builtin4.c $(PRS_DIR)/parse_ass_helper3.c $(MAIN_DIR)/update_shlvl.c  $(PRS_DIR)/heredoc.c \
	
OBJ = $(SRC:.c=.o)

INCLUDES = -I $(INC_DIR) -I $(LIBFT_DIR)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS)
	
%.o: %.c 
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	
re: fclean all


valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes --suppressions=readline_surpress.sup ./$(NAME)

.PHONY: all clean fclean re
