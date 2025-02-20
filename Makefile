NAME =miniRT
BONUS_NAME = miniRT_bonus
CC = cc -o3 #-g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror 
MND = ./mand/src/
BNS = ./bonus/src/
SUBMODULE = ./MLX
URL = https://github.com/42Paris/minilibx-linux.git
MLX = $(SUBMODULE)/libmlx_Linux.a
MLXFLAGS = -lX11 -lXext -lm 
RM = rm -rf

HDR = ./mand/includes/color.h  ./mand/includes/defined.h  ./mand/includes/includes.h  ./mand/includes/math.h  ./mand/includes/memory.h\
	./mand/includes/objects.h  ./mand/includes/tmpobjects.h minirt.h

BHDR = ./bonus/includes/color_bonus.h  ./bonus/includes/defined_bonus.h  ./bonus/includes/includes_bonus.h  ./bonus/includes/math_bonus.h  ./bonus/includes/memory_bonus.h\
	./bonus/includes/objects_bonus.h  minirt_bonus.h


SRC = minirt.c $(MND)parsing/parce_rgb.c $(MND)parsing/parse_crd.c $(MND)parsing/parsing.c $(MND)utils/ft_atof.c \
	$(MND)utils/ft_split.c  $(MND)utils/Rgb_cnv.c $(MND)tmputils/cy_utils.c  $(MND)tmputils/pl_utils.c \
	$(MND)tmputils/sp_utils.c $(MND)memory/arena_alloc.c $(MND)memory/arena_create.c $(MND)memory/arena_manage.c \
	$(MND)math/math.c $(MND)rendering/render.c $(MND)coloring/coloring.c $(MND)utils/ft_atoi.c $(MND)utils/ft_strcmp.c \
	$(MND)rendering/ray_sphere.c $(MND)rendering/ray_plane.c $(MND)rendering/ray_cylinder.c $(MND)parsing/env_obj.c \
	$(MND)parsing/scene_obj.c $(MND)parsing/read_line.c $(MND)parsing/copy_scene_data.c $(MND)math/math1.c\
	$(MND)parsing/err_cleanup.c $(MND)memory/arena_manage1.c $(MND)rendering/cy_loop.c $(MND)rendering/lightning.c\
	$(MND)rendering/rotation.c $(MND)rendering/rotation_utils.c $(MND)rendering/transformation.c $(MND)rendering/move.c\
	$(MND)rendering/move_utils.c $(MND)rendering/render_utils.c $(MND)rendering/hooks.c

BONUS_SRC = minirt_bonus.c		 $(BNS)parsing/parce_rgb_bonus.c	 	$(BNS)parsing/parse_crd_bonus.c 		$(BNS)parsing/parsing_bonus.c \
	$(BNS)utils/ft_atof_bonus.c $(BNS)utils/ft_memcpy_bonus.c $(BNS)utils/ft_split_bonus.c $(BNS)utils/Rgb_cnv_bonus.c $(BNS)tmputils/cy_utils_bonus.c \
	$(BNS)tmputils/co_utils_bonus.c $(BNS)tmputils/pl_utils_bonus.c $(BNS)tmputils/sp_utils_bonus.c $(BNS)memory/arena_alloc_bonus.c \
	$(BNS)memory/arena_create_bonus.c $(BNS)memory/arena_manage_bonus.c $(BNS)memory/arena_utils_bonus.c $(BNS)math/math_bonus.c $(BNS)math/advanced_vector_bonus.c\
	$(BNS)coloring/coloring_bonus.c $(BNS)utils/ft_atoi_bonus.c $(BNS)utils/ft_strcmp_bonus.c $(BNS)rendering/ray_sphere_bonus.c\
	$(BNS)rendering/ray_plane_bonus.c $(BNS)rendering/transformation_utils_bonus.c $(BNS)rendering/load_textures_bonus.c $(BNS)rendering/sphere_textures_bonus.c \
	$(BNS)rendering/plane_textures_bonus.c $(BNS)rendering/cone_textures_bonus.c $(BNS)rendering/cylinder_textures_bonus.c $(BNS)rendering/render_utils_bonus.c\
	$(BNS)rendering/rotation_bonus.c $(BNS)rendering/rotation_utils_bonus.c $(BNS)rendering/textures_bonus.c $(BNS)rendering/textures_utils_bonus.c \
	$(BNS)rendering/textures_setup_bonus.c $(BNS)rendering/transformation_bonus.c $(BNS)rendering/ray_cylinder_bonus.c $(BNS)rendering/ray_cone_bonus.c \
	$(BNS)rendering/ray_cone_utils_bonus.c $(BNS)rendering/ray_cylinder_utils_bonus.c $(BNS)rendering/pixel_bonus.c $(BNS)rendering/pixel_utils_bonus.c $(BNS)rendering/move_bonus.c \
	$(BNS)rendering/move_utils_bonus.c $(BNS)rendering/hooks_bonus.c $(BNS)rendering/draw_bonus.c $(BNS)rendering/calculate_surface_bonus.c $(BNS)parsing/env_obj_bonus.c \
	$(BNS)parsing/scene_obj_utils_bonus.c $(BNS)parsing/scene_obj_bonus.c $(BNS)utils/ft_strdup_bonus.c $(BNS)rendering/render_bonus.c\
	$(BNS)parsing/read_line_bonus.c $(BNS)parsing/copy_scene_data_bonus.c $(BNS)parsing/copy_scene_utils_bonus.c $(BNS)parsing/err_cleanup_bonus.c $(BNS)tmputils/light_utils_bonus.c\
	$(BNS)rendering/ray_cone_utils1_bonus.c  $(BNS)rendering/ray_cone_utils2_bonus.c\

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)

all: check_submodule $(NAME) 

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c $(BHDR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(MLXFLAGS) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ) $(MLX)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(MLX) $(MLXFLAGS) -o $(BONUS_NAME)

bonus: check_submodule $(BONUS_NAME)

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)
	$(MAKE) -C $(SUBMODULE) clean

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME) $(MLX)

re: fclean all

check_submodule:
	@if [ ! -d "$(SUBMODULE)" ] || [ -z "$$(ls -A $(SUBMODULE) 2>/dev/null)" ]; then \
		echo "MLX folder is missing or empty. Cloning..."; \
		rm -rf $(SUBMODULE); \
		git clone $(URL) $(SUBMODULE); \
	fi
	@if [ ! -d "$(SUBMODULE)/.git" ]; then \
		echo "Initializing submodule..."; \
		git submodule update --init --recursive; \
	fi
	@$(MAKE) -C $(SUBMODULE)

.PHONY: all clean fclean re check_submodule bonus
