NAME=minirt
CC=cc
CFLAGS=-Wall -Wextra -Werror

SRC =minirt.c

OBJ = $(SRC:.c=.o)

RM=rm -rf

MLX = ./minilibx-linux/libmlx_Linux.a
MLXFLAGS = 
DEBUG = 
GPROF = 

all: $(NAME)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)   
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re