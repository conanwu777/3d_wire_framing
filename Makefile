NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c setup.c draw.c
OBJ = $(SRC:.c=.o)

MLX_LNK = -L ./minilibx_macos -lmlx
GRAPHICS = -framework OpenGL -framework AppKit
FT_LNK = -L ./libft -lft

$(NAME):
	make -C libft/
	$(CC) $(CFLAGS) $(MLX_LNK) $(GRAPHICS) $(FT_LNK) $(SRC) -o $(NAME)

all: $(NAME)

clean:
	/bin/rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean

re:	fclean all
