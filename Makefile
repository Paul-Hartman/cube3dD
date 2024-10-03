NAME := cub3D

CC := cc

CFLAGS := -Wall -Wextra -Werror -g

SRCS := raytracing.c events.c read_map.c cleanup.c cub3d.c read_map_utils.c read_map_content.c render.c textures.c utils.c validate_map.c get_next_line/get_next_line.c \
movement.c

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx  cub3d.h
else
	INCLUDES = -I/opt/X11/include -Imlx cub3d.h
endif

MLX_LIB = ./mlx/libmlx.a
LIBFT = ./ft_printf/libftprintf.a

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

OBJS := $(SRCS:.c=.o)


$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS)  $(OBJS) $(LIBFT) $(MLX_PATH) $(MLX_FLAGS) -o $(NAME) -lm

all: $(NAME) $(MLX_LIB) $(LIBFT)

$(MLX_LIB):
	@make -C ./mlx

$(LIBFT):
	@make -C ./ft_printf

clean:
	@rm -f $(OBJS)
	@make clean -C ./ft_printf
	@make clean -C ./mlx

fclean: clean
	@make fclean -C ./ft_printf
	@make clean -C ./mlx
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
