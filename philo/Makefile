# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 13:22:45 by bgolding          #+#    #+#              #
#    Updated: 2024/06/18 13:12:41 by bgolding         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

INC_DIR	=	inc/
SRC_DIR	=	src/
OBJ_DIR = 	obj/

SRC_F	=	main \
			input_check \
			init \
			run \
			monitor \
			philo_actions \
			philo_utils \
			forks \
			utils \
			terminate

OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_F)))

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g
RM		=	rm -f

ifeq ($(shell uname), Linux)
	CFLAGS += -pthread
endif


all:		$(NAME)
		@echo "Successfully compiled executable: $(NAME)"

$(NAME):	$(OBJ_DIR) $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR):
			@mkdir -p $@

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
			$(RM) -r $(OBJ_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
