# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/26 10:49:58 by avan-bre          #+#    #+#              #
#    Updated: 2022/01/13 17:43:47 by avan-bre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

CC		=	gcc -c -o 

AR 		=	ar rcs

RM		=	rm -rf

#INC		=	libft.h printf/ft_printf.h

SRCS	=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
			ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
			ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
			ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_lstnew.c ft_lstadd_front.c in_set.c get_next_line.c \
			get_next_line_utils.c \

PSRCS	=	ft_printf.c print_char.c print_hex.c print_int.c \
			print_hex_cap.c print_ptr.c print_string.c print_uns_int.c
	
BONUS	=	ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
			ft_lstclear.c ft_lstiter.c ft_lstmap.c \

P_DIR	=	printf/

OBJS =		$(SRCS:.c=.o) 

P_OBJS	=	$(addprefix $(P_DIR), $(PSRCS:.c=.o))

OBJS_B =	$(BONUS:.c=.o)

CFLAGS =	-Wall -Werror -Wextra $(IFLAGS)

IFLAGS	=	-Ift_printf

$(NAME):	$(OBJS) $(P_OBJS)
	$(AR) $(NAME) $(OBJS) $(P_OBJS)

all:	$(NAME)

bonus:	$(OBJS) $(P_OBJS) $(OBJS_B) $(INC)
	$(AR) $(NAME) $(OBJS) $(OBJS_B)

clean:
	$(RM) $(OBJS) $(P_OBJS) $(OBJS_B)

fclean:	clean
	$(RM) $(NAME)

re:		clean all

.PHONY:	re, all, clean, fclean, bonus
	
