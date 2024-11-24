NAME=minirt
CC=cc
CFLAGS=-Wall -Wextra -Werror
SRC =
OBJ = $(SRC:.c=.o)+
RM=rm -rf

MLX = -I ./MLX/build/libmlx42.a
MLXFLAGS =
DEBUG = 
GPROF = 

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)  -I 
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re