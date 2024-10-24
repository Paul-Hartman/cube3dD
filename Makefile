NAME := cub3D
NAME_BONUS := cub3D_bonus
OBJDIR := objs
OBJDIR_BONUS := objs_bonus
GNLDIR = get_next_line

CC := cc

CFLAGS := -Wall -Wextra -Werror -g

SRCS := raytracing.c events.c cleanup.c cub3d.c doors.c inits.c inits2.c inits3.c gun.c\
		movement.c read_map.c read_map_utils.c read_map_content.c render.c load_textures.c\
		unload_textures.c trig_utils.c utils.c utils2.c utils3.c utils4.c raytrace_utils.c\
		validate_map.c get_next_line.c get_next_line_utils.c enemy.c sprites.c minimap.c\
		events2.c environment.c render_utils.c game_logic.c bonus_textures.c

OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)
OBJS_BONUS := $(SRCS:%.c=$(OBJDIR_BONUS)/%.o)

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx  cub3d.h
else
	INCLUDES = -I/opt/X11/include -Imlx cub3d.h
endif

MLX_LIB = ./mlx/libmlx.a
LIBFT = ./ft_printf/libftprintf.a
BONUS_FLAGS = -D BONUS=true

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -lm -framework OpenGL -framework AppKit
endif

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR_BONUS)/%.o: %.c
	mkdir -p $(OBJDIR_BONUS)
	$(CC) $(CFLAGS) $(BONUS_FLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_PATH) $(MLX_FLAGS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(BONUS_FLAGS) $(OBJS_BONUS) $(LIBFT) $(MLX_PATH) $(MLX_FLAGS) -o $(NAME_BONUS)

all: $(NAME)

bonus: $(NAME_BONUS)

$(MLX_LIB):
	@make -C ./mlx

$(LIBFT):
	@make -C ./ft_printf

clean:
	@rm -f $(OBJS)
	@rm -f $(OBJS_BONUS)
	@make clean -C ./ft_printf
	@make clean -C ./mlx

fclean: clean
	@make fclean -C ./ft_printf
	@make clean -C ./mlx
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

re: fclean all

.PHONY: bonus all clean fclean re
