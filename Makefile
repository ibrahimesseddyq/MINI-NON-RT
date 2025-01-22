NAME = minirt
CC = cc
CFLAGS =  -g #-Wall -Wextra -Werror  # Uncommented this for standard warning flags

SRC = minirt.c \
	./mand/src/parsing/parce_rgb.c ./mand/src/parsing/parse_crd.c ./mand/src/parsing/parsing.c \
	./mand/src/utils/ft_atof.c ./mand/src/utils/ft_split.c ./mand/src/utils/Rgb_cnv.c \
	./mand/src/tmputils/cy_utils.c ./mand/src/tmputils/co_utils.c ./mand/src/tmputils/pl_utils.c ./mand/src/tmputils/sp_utils.c \
	./mand/src/memory/arena_alloc.c ./mand/src/memory/arena_create.c ./mand/src/memory/arena_manage.c \
	./mand/src/math/math.c ./mand/src/rendering/render.c ./mand/src/coloring/coloring.c\
	./mand/src/utils/ft_atoi.c ./mand/src/utils/ft_strcmp.c ./mand/src/rendering/ray_sphere.c ./mand/src/rendering/ray_plane.c \
	./mand/src/rendering/ray_cylinder.c ./mand/src/parsing/env_obj.c ./mand/src/parsing/scene_obj.c\
	./mand/src/parsing/read_line.c ./mand/src/parsing/copy_scene_data.c\

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
