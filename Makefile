NAME	=	euler_methods

CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror

SRC	= main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf results.csv

re: fclean all

%.o : %.c inc/lab_01.h
	$(CC) $(CFLAGS) -c $< -o $@ 
