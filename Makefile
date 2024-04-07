# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkoca <dkoca@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 01:06:15 by dkoca             #+#    #+#              #
#    Updated: 2024/04/07 12:40:08 by dkoca            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := aicu

SRCDIR := src
_SRC := main.c parse.c utils.c gameplay.c
SRC := $(addprefix $(SRCDIR)/, $(_SRC))

OBJDIR := obj
_OBJ := $(_SRC:.c=.o)
OBJ := $(addprefix $(OBJDIR)/, $(_OBJ))

LIBFTDIR := libft
LIBFT := $(LIBFTDIR)/libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror -g3 -I$(SRCDIR) -I$(LIBFTDIR)
LDFLAGS :=  -L$(LIBFTDIR) -lft
RM := /bin/rm -f

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

$(LIBFT):
	@make -C $(LIBFTDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(SRCDIR)/aicu.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJ)
	$(RM) -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY:
	all clean fclean re
