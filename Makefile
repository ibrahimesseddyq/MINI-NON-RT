NAME = minirt
CC = cc
CFLAGS = -std=c23 #-Wall -Wextra -Werror  # Uncommented this for standard warning flags

SRC = minirt.c \
	./src/parsing/parce_rgb.c ./src/parsing/parse_crd.c ./src/parsing/parsing.c \
	./src/utils/ft_atof.c ./src/utils/ft_split.c ./src/utils/Rgb_cnv.c \
	./src/tmputils/cy_utils.c ./src/tmputils/pl_utils.c ./src/tmputils/sp_utils.c \
	./src/memory/arena_alloc.c ./src/memory/arena_create.c ./src/memory/arena_manage.c \
	./src/math/math.c ./src/rendering/render.c ./src/coloring/coloring.c\
	./src/utils/ft_atoi.c ./src/utils/ft_strcmp.c ./src/rendering/ray_sphere.c ./src/rendering/ray_plane.c \
	./src/rendering/ray_cylinder.c
	
OBJ = $(SRC:.c=.o)

RM = rm -rf

MLX = ./MLX/libmlx_Linux.a
MLXFLAGS = -lX11 -lXext -lm  # You may need these flags for linking with minilibx
DEBUG = #-g -fsanitize=address  # Keep optional, uncomment when debugging
GPROF = # -pg  # Uncomment for profiling with gprof, optional

all: $(NAME)

%.o: %.c
	$(CC) $(DEBUG) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(DEBUG) $(CFLAGS) $(OBJ) $(MLX) $(MLXFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
