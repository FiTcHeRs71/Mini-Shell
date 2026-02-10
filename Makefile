# Program name
NAME = minishell

# Directories
SRCDIR = srcs
INCDIR = includes
OBJDIR = objs
LIBFTDIR = libft

# Source files (structure pour expansion future)
SRCS_MAIN = $(addprefix $(SRCDIR)/, \
	main.c)

SRCS_LEXER = $(addprefix $(SRCDIR)/lexer/, \
	tokenize.c tokenize_utils.c tokenize_redirection.c tokenize_segments.c \
	tokenize_no_quotes.c)

SRCS_PARSER = $(addprefix $(SRCDIR)/parser/, \
	parse.c parse_command.c parse_pipe.c parse_redir.c parse_utils.c \
	parse_logic.c parse_paren.c parse_utils2.c parse_utils3.c)

SRCS_EXPANDER = $(addprefix $(SRCDIR)/expander/, \
	expand.c expand_utils.c expand_heredoc.c wildcards.c wildcards_utils.c \
	wildcards_patterns.c )

SRCS_EXECUTOR = $(addprefix $(SRCDIR)/executor/, \
	exec.c exec_utils.c exec_pipe.c exec_heredoc.c exec_cmd_builtin.c \
	exec_cmd.c exec_cmd_utils.c exec_redir.c exec_error.c)

SRCS_BUILTINS = $(addprefix $(SRCDIR)/builtins/, \
	built_in_env.c built_in_exit.c built_in_cd.c built_in_echo.c built_in_export.c \
	built_in_pwd.c built_in_unset.c built_in_utils.c)

SRCS_SIGNALS = $(addprefix $(SRCDIR)/signal/, \
	signal.c heredoc_signal.c)

SRCS_ENV = $(addprefix $(SRCDIR)/env/, \
	env_init.c)

SRCS_UTILS = $(addprefix $(SRCDIR)/utils/, \
	clear.c clear_2.c error.c exit.c)

# Combine all sources
SRCS = $(SRCS_MAIN) $(SRCS_LEXER) $(SRCS_PARSER) $(SRCS_EXPANDER) \
		$(SRCS_EXECUTOR) $(SRCS_BUILTINS) $(SRCS_SIGNALS) $(SRCS_ENV) \
		$(SRCS_UTILS)

# Object files
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I$(INCDIR) -I$(LIBFTDIR)/include
LDFLAGS = -L$(LIBFTDIR) -lft -lreadline

# Colors
GREEN = \033[0;32m
CYAN = \033[0;36m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

# Rules
all: $(LIBFTDIR)/libft.a $(NAME)
	@echo "$(GREEN)🎉 $(NAME) ready! 🎉$(RESET)"

$(LIBFTDIR)/libft.a:
	@echo "$(CYAN)📚 Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFTDIR) --no-print-directory
	@echo "$(GREEN)✓ libft compiled$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@printf "$(CYAN)Compiling $(notdir $<)...$(RESET)\r"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "$(GREEN)✓ Compiled $(notdir $<)   $(RESET)\n"

$(NAME): $(OBJS)
	@echo "$(YELLOW)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created successfully!$(RESET)"

clean:
	@$(MAKE) -C $(LIBFTDIR) clean --no-print-directory
	@rm -rf $(OBJDIR)
	@echo "$(CYAN)✓ Object files removed$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFTDIR) fclean --no-print-directory
	@rm -f $(NAME)
	@echo "$(CYAN)✓ $(NAME) removed$(RESET)"

re: fclean all

# Utilities
run: all
	@echo "$(GREEN)🚀 Running $(NAME)...$(RESET)"
	@./$(NAME)

valgrind: all
	@echo "$(YELLOW)🔍 Running valgrind...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
		--suppressions=readline.supp --log-fd=2 ./$(NAME)

norm:
	@echo "$(YELLOW)📋 Checking norminette...$(RESET)"
	@norminette $(SRCDIR) $(INCDIR) $(LIBFTDIR) 2>&1 | grep -v "OK!" || \
		echo "$(GREEN)✓ All files conform to norminette$(RESET)"
help:
	@echo "$(CYAN)═══════════════════════════════════════════════════════$(RESET)"
	@echo "$(GREEN)  Minishell Makefile - Available targets$(RESET)"
	@echo "$(CYAN)═══════════════════════════════════════════════════════$(RESET)"
	@echo "  $(YELLOW)all$(RESET)       - Build minishell"
	@echo "  $(YELLOW)clean$(RESET)     - Remove object files"
	@echo "  $(YELLOW)fclean$(RESET)    - Remove object files and executable"
	@echo "  $(YELLOW)re$(RESET)        - Rebuild everything from scratch"
	@echo "  $(YELLOW)run$(RESET)       - Build and run minishell"
	@echo "  $(YELLOW)valgrind$(RESET)  - Run with valgrind memory checker"
	@echo "  $(YELLOW)norm$(RESET)      - Check norminette compliance"
	@echo "  $(YELLOW)help$(RESET)      - Show this help message"
	@echo "$(CYAN)═══════════════════════════════════════════════════════$(RESET)"

.PHONY: all clean fclean re run valgrind norm debug help
