CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror

SRCS = helper.c ft_printf.c

HEADERS = ft_printf.h

OBJS = $(SRCS:.c=.o)

NAME = libftprintf.a

all: $(NAME)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft 
	@$(MAKE) bonus -C ./libft
	cp libft/libft.a $(NAME)
	ar rc $(NAME) $(OBJS)
clean:
	@$(MAKE) clean -C ./libft
	@$(RM) $(OBJS)
fclean: clean
	@$(MAKE) fclean -C ./libft
	@$(RM) $(NAME)

.PHONY: all fclean clean re

re: fclean all

