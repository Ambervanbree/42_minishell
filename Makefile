# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 15:32:57 by avan-bre          #+#    #+#              #
#    Updated: 2022/01/18 11:54:23 by avan-bre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                 COMPILATION                                  #
################################################################################

NAME	=	minishell
B_NAME	=	
LIBFT	=	libft/libft.a
RM		=	@rm -rf
CC		=	@clang
IFLAGS	=	-I. -Ilibft
RLFLAGS	=	-lreadline
SFLAGS	=	-fsanitize=address -g3 
CFLAGS	:=	-Wall -Werror -Wextra $(IFLAGS) 
LFLAGS	:=	-Llibft -lft

################################################################################
#                                    FILES                                     #
################################################################################

SRCS	=	minishell.c $(addprefix $(E_DIR), $(E_SRCS))
E_SRCS	=	redirection.c builtins.c BI_cd.c BI_env_echo_pwd.c BI_export.c \
			BI_unset.c
B_SRCS	=	
S_DIR	=	sources/
B_DIR	=	bonus_sources/
E_DIR	=	execution/
OBJS	=	$(addprefix $(S_DIR), $(SRCS:.c=.o))
E_OBJS	=	$(addprefix $(E_DIR), $(B_SRCS:.c=.o))
B_OBJS	=	$(addprefix $(B_DIR), $(B_SRCS:.c=.o))

################################################################################
#                                 RULES                                        #
################################################################################

.c.o:
	$(CC) $(CFLAGS) $(SFLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS) $(E_OBJS) $(LIBFT)
	@echo "Compiling sources.."
	$(CC) $(SFLAGS) $(OBJS) $(E_OBJS) $(LFLAGS) -o $@ $(RLFLAGS)
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
	$(RM) $(OBJS) $(E_OBJS) ${B_OBJS}
	@make $@ -s -C libft
	@echo "Removed objects"

fclean:		clean
	$(RM) $(NAME) ${B_NAME}
	@make $@ -s -C libft
	@echo "Removed executable files"

re:			clean all

.PHONY:		re, all, clean, fclean