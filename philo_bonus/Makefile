# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgolding <bgolding@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 14:16:03 by bgolding          #+#    #+#              #
#    Updated: 2024/02/22 11:02:07 by bgolding         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo_bonus

INC_DIR	=	inc/
SRC_DIR	=	src/
OBJ_DIR = 	obj/

SRC_F	=	main \
			input_check \
			init \
			run	\
			philo_routine \
			philo_actions \
			philo_utils \
			sem_name \
			monitor_routine \
			utils \
			end_simulation

OBJS	=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_F)))

CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -g
RM		=	rm -f

all:		$(NAME)

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