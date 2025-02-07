NAME = minirt
BONUS_NAME = minirt_bonus
CC = cc -g
CFLAGS = #-Wall -Wextra -Werror  # Uncomment this for standard warning flags
MND = ./mand/src/
BNS = ./bonus/src/
HDR = ./mand/includes/color.h  ./mand/includes/defined.h  ./mand/includes/includes.h  ./mand/includes/math.h  ./mand/includes/memory.h\
	./mand/includes/objects.h  ./mand/includes/tmpobjects.h minirt.h

SUBMODULE = ./MLX
MLX = $(SUBMODULE)/libmlx_Linux.a
MLXFLAGS = -lX11 -lXext -lm  # You may need these flags for linking with minilibx

SRC = minirt.c $(MND)parsing/parce_rgb.c $(MND)parsing/parse_crd.c $(MND)parsing/parsing.c $(MND)utils/ft_atof.c \
	$(MND)utils/ft_split.c  $(MND)utils/Rgb_cnv.c $(MND)tmputils/cy_utils.c  $(MND)tmputils/pl_utils.c \
	$(MND)tmputils/sp_utils.c $(MND)memory/arena_alloc.c $(MND)memory/arena_create.c $(MND)memory/arena_manage.c \
	$(MND)math/math.c $(MND)rendering/render.c $(MND)coloring/coloring.c $(MND)utils/ft_atoi.c $(MND)utils/ft_strcmp.c \
	$(MND)rendering/ray_sphere.c $(MND)rendering/ray_plane.c $(MND)rendering/ray_cylinder.c $(MND)parsing/env_obj.c \
	$(MND)parsing/scene_obj.c $(MND)parsing/read_line.c $(MND)parsing/copy_scene_data.c $(MND)math/math1.c\
	$(MND)parsing/err_cleanup.c $(MND)memory/arena_manage1.c $(MND)rendering/cy_loop.c $(MND)rendering/lightning.c\
	$(MND)rendering/rotation.c $(MND)rendering/rotation_utils.c $(MND)rendering/transformation.c $(MND)rendering/move.c\
	$(MND)rendering/move_utils.c $(MND)rendering/render_utils.c $(MND)rendering/hooks.c\

BONUS_SRC = minirt_bonus.c  $(BNS)parsing/parce_rgb.c $(BNS)parsing/parse_crd.c $(BNS)parsing/parsing.c \
	$(BNS)utils/ft_atof.c $(BNS)utils/ft_memcpy.c $(BNS)utils/ft_split.c $(BNS)utils/Rgb_cnv.c $(BNS)tmputils/cy_utils.c \
	$(BNS)tmputils/co_utils.c $(BNS)tmputils/pl_utils.c $(BNS)tmputils/sp_utils.c $(BNS)memory/arena_alloc.c \
	$(BNS)memory/arena_create.c $(BNS)memory/arena_manage.c $(BNS)memory/arena_utils.c $(BNS)math/math.c $(BNS)math/advanced_vector.c $(BNS)rendering/render.c\
	$(BNS)coloring/coloring.c $(BNS)utils/ft_atoi.c $(BNS)utils/ft_strcmp.c $(BNS)rendering/ray_sphere.c\
	$(BNS)rendering/ray_plane.c $(BNS)rendering/transformation_utils.c $(BNS)rendering/load_textures.c $(BNS)rendering/sphere_textures.c $(BNS)rendering/plane_textures.c $(BNS)rendering/cylinder_textures.c $(BNS)rendering/render_utils.c $(BNS)rendering/rotation.c $(BNS)rendering/rotation_utils.c $(BNS)rendering/textures.c $(BNS)rendering/textures_utils.c $(BNS)rendering/transformation.c $(BNS)rendering/ray_cylinder.c $(BNS)rendering/ray_cylinder_utils.c $(BNS)rendering/pixel.c $(BNS)rendering/pixel_utils.c $(BNS)rendering/move.c $(BNS)rendering/move_utils.c $(BNS)rendering/hooks.c $(BNS)rendering/draw.c $(BNS)rendering/calculate_surface.c $(BNS)parsing/env_obj.c $(BNS)parsing/scene_obj_utils.c $(BNS)parsing/scene_obj.c\
	$(BNS)parsing/read_line.c $(BNS)parsing/copy_scene_data.c $(BNS)parsing/err_cleanup.c $(BNS)tmputils/light_utils.c\

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

RM = rm -rf

all: check_submodule $(NAME) 

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(MLXFLAGS) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(MLX)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(MLX) $(MLXFLAGS) -o $(BONUS_NAME)

bonus: check_submodule $(BONUS_NAME)

clean:
	$(RM) $(OBJ)
	$(RM) $(BONUS_OBJ)
	$(MAKE) -C $(SUBMODULE) clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)
	$(RM) $(MLX)

re: fclean all


check_submodule:
	@if [ ! -d "$(SUBMODULE)/.git" ]; then \
		echo "Submodule missing. Cloning..."; \
		git submodule update --init --recursive; \
	fi
	@$(MAKE) -C $(SUBMODULE)

.PHONY: all clean fclean re check_submodule bonus

