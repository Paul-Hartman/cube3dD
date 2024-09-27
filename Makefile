
CC := cc

CFLAGS := -Wall -Wextra -Werror

SRCS := raytracing.c

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx  game.h
else
	INCLUDES = -I/opt/X11/include -Imlx game.h
endif

MLX_LIB = ./mlx/libmlx.a
LIBFT = ./ft_printf/libftprintf.a

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

OBJS := $(SRCS:.c=.o)

NAME := so_long

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