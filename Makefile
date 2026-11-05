# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juskola- <juskola-@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/15 14:05:39 by juskola-          #+#    #+#              #
#    Updated: 2026/11/04 13:02:17 by juskola-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion

CC = cc

#I have to remove the '-g3' from the cflags
CFLAGS = -g3 -Wall -Werror -Wextra -pthread

SRCS =	codexion.c	\
	utils/additional_funcs.c	\
	utils/ft_itoa.c	\
	utils/garbage_collector.c	\
	parsing/parsing.c	\
	parsing/parsing_utils.c	\
	prints/prints.c	\
	simulation/init_simulation.c	\
	simulation/run_simulation.c	\
	simulation/simulation_util_funcs.c	\
	monitor/monitor.c	\
	coders/coders.c		\
	coders/coder_routine.c	\
	coders/init_coders.c	\
	scheduler/coder_choose.c	\
	scheduler/request_research.c	\
	scheduler/request_verify.c	\
	dongles/dongles.c	\
	dongles/init_dongles.c	\
	heap/heap_funcs.c	\
	heap/heap_requests.c	\
	heap/init_heap.c	\
	heap/heap_util_funcs.c	\
	heap/heap_thread.c
	

OBJS = $(SRCS:.c=.o)

HEADERS = codexion.h

all: $(NAME)
	make clean

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)


%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS)


fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
