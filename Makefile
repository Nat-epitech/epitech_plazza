##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Nathan DP Makefile (v2.0)
##

NAME	= plazza

CC = g++

SRC	=	$(wildcard src/*.cpp)

OBJ	=	$(addprefix $(OBJDIR)/,$(notdir $(SRC:.cpp=.o)))

OBJDIR	=	Objects

CFLAGS += -Wall -Wextra -Iincludes -pthread

DEBUG := debug

$(DEBUG): CFLAGS	+= -g3 -ggdb

END         =   \033[0m
BOLD        =   \033[1m
RED         =   \033[31m
GREEN       =   \033[32m
YELLOW      =   \033[33m
PURPLE      =   \033[35m
CYAN        =   \033[36m
WHITE       =   \033[37m

all: $(NAME)

$(DEBUG):	fclean $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) --pedantic $(CFLAGS) && echo -e "\n$(CYAN)[$(GREEN)$(BOLD)Success$(END)$(CYAN)$(BOLD)] Moving Objects file(s) in folder : $(YELLOW)$(OBJDIR)$(END)"\
	&& echo -e "$(CYAN)[$(GREEN)$(BOLD)Success$(END)$(CYAN)$(BOLD)] Binary $(YELLOW)$(NAME)$(END)$(CYAN)$(BOLD) Successfully created with flags : $(YELLOW)$(CFLAGS)$(END)"

$(OBJ): | $(OBJDIR)

$(OBJ): $(OBJDIR)/%.o : src/%.cpp
	@$(CC) $(LDFLAGS) -c $< -o $@ $(CFLAGS) $(LDLIBS) && echo -e "$(CYAN)[$(GREEN)$(BOLD)Success$(END)$(CYAN)$(BOLD)]$(CYAN) $<$(END)"\
|| echo -e "$(RED)[ERROR] $(BOLD)Failed to compile : $<$(END)"

$(OBJDIR):
	@mkdir Objects

clean:
	@$(RM) -rf $(OBJDIR)
	@echo -e "$(CYAN)[$(GREEN)$(BOLD)Success$(END)$(CYAN)$(BOLD)] Objects file(s) removed$(END)"

fclean: clean
	@$(RM) $(NAME)
	@echo -e "$(CYAN)[$(GREEN)$(BOLD)Success$(END)$(CYAN)$(BOLD)] Workspace cleaned$(END)"

re: fclean all

.PHONY: all clean fclean re

