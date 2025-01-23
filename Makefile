NAME = minirt
BONUS_NAME = minirt_bonus
CC = cc
CFLAGS =  #-Wall -Wextra -Werror  # Uncommented this for standard warning flags
MND=./mand/src/
BNS=./bonus/src/
SRC = minirt.c $(MND)parsing/parce_rgb.c $(MND)parsing/parse_crd.c $(MND)parsing/parsing.c $(MND)utils/ft_atof.c \
	$(MND)utils/ft_split.c $(MND)utils/Rgb_cnv.c $(MND)tmputils/cy_utils.c $(MND)tmputils/co_utils.c $(MND)tmputils/pl_utils.c \
	$(MND)tmputils/sp_utils.c $(MND)memory/arena_alloc.c $(MND)memory/arena_create.c $(MND)memory/arena_manage.c \
	$(MND)math/math.c $(MND)rendering/render.c $(MND)coloring/coloring.c $(MND)utils/ft_atoi.c $(MND)utils/ft_strcmp.c \
	$(MND)rendering/ray_sphere.c $(MND)rendering/ray_plane.c $(MND)rendering/ray_cylinder.c $(MND)parsing/env_obj.c \
	$(MND)parsing/scene_obj.c $(MND)parsing/read_line.c $(MND)parsing/copy_scene_data.c\

BONUS_SRC = minirt_bonus.c  $(BNS)parsing/parce_rgb.c $(BNS)parsing/parse_crd.c $(BNS)parsing/parsing.c \
	$(BNS)utils/ft_atof.c $(BNS)utils/ft_split.c $(BNS)utils/Rgb_cnv.c $(BNS)tmputils/cy_utils.c \
	$(BNS)tmputils/co_utils.c $(BNS)tmputils/pl_utils.c $(BNS)tmputils/sp_utils.c $(BNS)memory/arena_alloc.c \
	$(BNS)memory/arena_create.c $(BNS)memory/arena_manage.c $(BNS)math/math.c $(BNS)rendering/render.c\
	 $(BNS)coloring/coloring.c $(BNS)utils/ft_atoi.c $(BNS)utils/ft_strcmp.c $(BNS)rendering/ray_sphere.c\
	 $(BNS)rendering/ray_plane.c $(BNS)rendering/ray_cylinder.c $(BNS)parsing/env_obj.c $(BNS)parsing/scene_obj.c\
	$(BNS)parsing/read_line.c $(BNS)parsing/copy_scene_data.c $(BNS)parsing/err_cleanup.c\

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

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

$(BONUS_NAME): $(BONUS_OBJ)
	$(CC) $(DEBUG) $(CFLAGS) $(BONUS_OBJ) $(MLX) $(MLXFLAGS) -o $(BONUS_NAME)

bonus: $(BONUS_NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re
