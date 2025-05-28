# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 13:49:29 by achantra          #+#    #+#              #
#    Updated: 2025/05/27 15:43:53 by md-harco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = webserv

SRCS = main.cpp \
	srcs/socket/Socket.cpp \
	srcs/socket/BindingSocket.cpp \
	srcs/socket/ListeningSocket.cpp \
	srcs/server/Server.cpp \
	srcs/server/RealServer.cpp \
	srcs/server/RealServer_routine.cpp \
	srcs/server/RealServer_utils.cpp \
	srcs/server/RealServer_utils2.cpp \
	srcs/utils/utils.cpp \
	srcs/parse_config/parse_config.cpp \
	srcs/parse_config/parse_server.cpp \
	srcs/parse_config/parse_location.cpp \
	srcs/request/Request.cpp \
	srcs/request/ReqLine.cpp \
	srcs/request/ReqValidator.cpp \
	srcs/signal/signal.cpp

BUILD_DIR = build
OBJ = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEP = $(OBJ:.o=.d)

CC = c++
CFLAGS = -g3 -Wall -Wextra -Werror -std=c++98 -MMD -MP

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

-include $(DEP)

clean:
	rm -f $(OBJ)
	rm -f $(DEP)

fclean: clean
	rm -f $(NAME)

re: fclean all