SRC =	./main.c \
./utils.c \
./ft_aircraft.c \
./ft_airline.c \
./ft_passenger.c \
./ft_airport.c \
./ft_flight.c \
./ft_reservation.c \

NAME = airport_management
CC = gcc
CFLAGS =  -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
GET_NEXT_LINE = ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c 
OBJS = $(SRC:.c=.o)

all: ${NAME}

$(NAME): $(OBJS) $(LIBFT) $(GET_NEXT_LINE)
	@gcc $(CFLAGS) $(OBJS) $(LIBFT) $(GET_NEXT_LINE) -o $(NAME)

$(LIBFT):
	@make -C ./libft

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJSB)
	@make clean -C ./libft

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re 