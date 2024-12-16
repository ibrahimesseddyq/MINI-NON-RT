NAME=minirt
CC=cc
CFLAGS=-Wall -Wextra -Werror

SRC =minirt.c ./src/parsing/parce_rgb.c ./src/parsing/parse_crd.c ./src/parsing/parsing.c\
	./src/utils/ft_atof.c ./src/utils/ft_split.c ./src/utils/Rgb_cnv.c

OBJ = $(SRC:.c=.o)

RM=rm -rf

MLX = ./minilibx-linux/libmlx_Linux.a
MLXFLAGS = 
DEBUG = #-g -fsanitize=address
GPROF = 

all: $(NAME)


%.o: %.c
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJ)
	$(CC) $(DEBUG) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)   
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re