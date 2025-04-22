NAME = minishell

COLOR_ESC			= \033
COLOR_WHITE			= $(COLOR_ESC)[97m
COLOR_CYAN			= $(COLOR_ESC)[96m
COLOR_GREEN			= $(COLOR_ESC)[32m
COLOR_BLUE			= $(COLOR_ESC)[34m
COLOR_YELLOW		= $(COLOR_ESC)[33m
COLOR_MAGENTA 		= $(COLOR_ESC)[35m
COLOR_BOLD			= $(COLOR_ESC)[1m
COLOR_RESET			= $(COLOR_ESC)[0m
COLOR_RESET_BOLD	= $(COLOR_ESC)[21m

PATH_HEADER			= includes/
PATH_PARSER			= src_parser/
PATH_ROUTINE		= src_routine/
PATH_GARBAGE		= src_garbage/
PATH_UTIL			= src_util/
PATH_OBJ			= objs/

HEADER				= 	minishell.h utils.h garbage.h data.h parser.h includers.h
SRC_PARSER			= 	parser.c type_util.c quote_manager.c quote_parser.c
SRC_ROUTINE			= 	routine.c env.c builtins.c minishell.c \
						exec_command.c exec_command_utils.c \
						exec_command_utils2.c exec_command_utils3.c \
						export.c heredoc.c builtins_cmd.c exec_this.c \
						env_utils.c
SRC_GARBAGE			= 	garbage.c malloc.c free.c
SRC_UTIL			= 	ft_mem.c ft_str1.c ft_str2.c ft_str3.c \
						get_data.c ft_split.c link_list.c github.c \
						quicksort.c ft_str4.c ft_itoa.c

SRC_PARSERS			= $(addprefix $(PATH_PARSER),$(SRC_PARSER))
SRC_ROUTINES		= $(addprefix $(PATH_ROUTINE),$(SRC_ROUTINE))
SRC_GARBAGES		= $(addprefix $(PATH_GARBAGE),$(SRC_GARBAGE))
SRC_UTILS			= $(addprefix $(PATH_UTIL),$(SRC_UTIL))

SRCS 				= $(SRC_PARSERS) $(SRC_ROUTINES) $(SRC_GARBAGES) $(SRC_UTILS)

OBJ					= $(SRCS:.c=.o)
OBJS				= $(addprefix $(PATH_OBJ),$(OBJ))
HEADERS				= $(addprefix $(PATH_HEADER),$(HEADER))

DEBUG				= 0
DEBUGING			=  -g3 -fsanitize=address
CFLAGS 				= -Wall -Wextra -Werror -O3 -I$(PATH_HEADER)


ifeq ($(DEBUG), 1)
	CFLAGS += $(DEBUGING)
endif

READLINE_PATH := $(shell brew --prefix readline)

OPTIONS = -I$(READLINE_PATH)/include
LIBS    = -L$(READLINE_PATH)/lib -lreadline
CC					= gcc
RM					= rm -rf

$(PATH_OBJ)$(PATH_PARSER)%.o	: $(PATH_PARSER)%.c $(HEADERS)
	@mkdir -p $(PATH_OBJ)$(PATH_PARSER)
	@$(CC) $(CFLAGS) $(OPTIONS) -o $(@) -c $(<)
	@printf "$(COLOR_GREEN)[$(COLOR_WHITE)INFO$(COLOR_GREEN)] COMPILATION $(COLOR_CYAN)DEBUG => [%s] $(COLOR_BOLD)PARSER\t=>\t$(COLOR_WHITE)%s$(COLOR_RESET)\n" $(DEBUG) $<

$(PATH_OBJ)$(PATH_ROUTINE)%.o	: $(PATH_ROUTINE)%.c $(HEADERS)
	@mkdir -p $(PATH_OBJ)$(PATH_ROUTINE)
	@$(CC) $(CFLAGS) $(OPTIONS) -o $(@) -c $(<)
	@printf "$(COLOR_GREEN)[$(COLOR_WHITE)INFO$(COLOR_GREEN)] COMPILATION $(COLOR_BLUE)DEBUG => [%s] $(COLOR_BOLD)ROUTINE\t=>\t$(COLOR_WHITE)%s$(COLOR_RESET)\n" $(DEBUG) $<

$(PATH_OBJ)$(PATH_GARBAGE)%.o	: $(PATH_GARBAGE)%.c $(HEADERS)
	@mkdir -p $(PATH_OBJ)$(PATH_GARBAGE)
	@$(CC) $(CFLAGS) $(OPTIONS) -o $(@) -c $(<)
	@printf "$(COLOR_GREEN)[$(COLOR_WHITE)INFO$(COLOR_GREEN)] COMPILATION $(COLOR_YELLOW)DEBUG => [%s] $(COLOR_BOLD)GARBAGE\t=>\t$(COLOR_WHITE)%s$(COLOR_RESET)\n" $(DEBUG) $<

$(PATH_OBJ)$(PATH_UTIL)%.o		: $(PATH_UTIL)%.c $(HEADERS)
	@mkdir -p $(PATH_OBJ)$(PATH_UTIL)
	@$(CC) $(CFLAGS) $(LIB) $(OPTIONS) -o $(@) -c $(<)
	@printf "$(COLOR_GREEN)[$(COLOR_WHITE)INFO$(COLOR_GREEN)] COMPILATION $(COLOR_MAGENTA)DEBUG => [%s] $(COLOR_BOLD)UTIL\t=>\t$(COLOR_WHITE)%s$(COLOR_RESET)\n" $(DEBUG) $<

all			: $(NAME)

$(NAME)		: $(OBJS)
	@$(CC) $(CFLAGS) $(OPTIONS) -o $(@) $(^) $(LIBS)
	@echo "$(COLOR_GREEN)[$(COLOR_WHITE)INFO$(COLOR_GREEN)] LINKAGE $(COLOR_BOLD)ALL OBJS FILE =>\n\t $(COLOR_WHITE)$(^:.o=.o\n\t)"
	@echo "$(COLOR_GREEN)[$(COLOR_WHITE)INFO$(COLOR_GREEN)] COMPILATION FINISH !$(COLOR_WHITE)$(COLOR_RESET_BOLD)"

clean		:
	@$(RM) $(OBJS)
	@$(RM) $(PATH_OBJ)
	@echo "$(COLOR_GREEN)[$(COLOR_WHITE)INFO$(COLOR_GREEN)] DELETE $(COLOR_BOLD)ALL OBJS FILE =>\n\t $(COLOR_WHITE)$(OBJS:.o=.o\n\t)"
	@echo "$(COLOR_GREEN)[$(COLOR_WHITE)INFO$(COLOR_GREEN)] CLEAN FINISH !$(COLOR_RESET)"

fclean		: clean
	@$(RM) $(NAME)
	@echo "$(COLOR_GREEN)[$(COLOR_WHITE)INFO$(COLOR_GREEN)] DELETE $(COLOR_BOLD)PROGRAMME =>\n\t $(COLOR_WHITE)$(NAME)"
	@echo "$(COLOR_GREEN)[$(COLOR_WHITE)INFO$(COLOR_GREEN)] FCLEAN FINISH !$(COLOR_RESET)"


re			: fclean all

.PHONY: all fclean clean re