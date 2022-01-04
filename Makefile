# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 15:32:57 by avan-bre          #+#    #+#              #
#    Updated: 2021/12/29 17:56:00 by avan-bre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                 INFO                                         #
################################################################################

NAME	=	minishell
B_NAME	=	
LIBFT	=	libft/libft.a
RM		=	@rm -rf
CC		=	@clang
IFLAGS	=	-I. -Ilibft
RLFLAGS	=	-lreadline
CFLAGS	:=	-Wall -Werror -Wextra $(IFLAGS)
LFLAGS	:=	-Llibft -lft
SRCS	=	minishell.c \
			execution/exec.c execution/builtins.c execution/nonbuiltins.c \
			execution/builtins_env.c execution/exec_utils.c \
			execution/builtins_dir.c execution/builtins_cd.c
B_SRCS	=	
S_DIR	=	sources/
B_DIR	=	bonus_sources/
OBJS	=	$(addprefix $(S_DIR), $(SRCS:.c=.o))
B_OBJS	=	$(addprefix $(B_DIR), $(B_SRCS:.c=.o))

################################################################################
#                                 RULES                                        #
################################################################################

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
	@echo "Compiling sources.."
	$(CC) $(OBJS) $(LFLAGS) -o $@ $(RLFLAGS)
	@echo "Ready!"

$(LIBFT):
	@echo "Compiling libft.."
	@make -s -C libft
	@echo "Libft ready!"

bonus:	${B_OBJS} ${LIBFT}
	@echo "Compiling bonus sources.."
	${CC} ${B_OBJS} ${LFLAGS} -o ${B_NAME}
	@echo "Ready!"

clean:
	$(RM) $(OBJS) ${B_OBJS}
	@make $@ -s -C libft
	@echo "Removed objects"

fclean:		clean
	$(RM) $(NAME) ${B_NAME}
	@make $@ -s -C libft
	@echo "Removed executable files"

re:			clean all

.PHONY:		re, all, clean, fclean