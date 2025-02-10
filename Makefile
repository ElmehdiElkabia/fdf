NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror 
MFLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm -lbsd
LIBFT_DIR = ./libft
LIB = $(LIBFT_DIR)/libft.a

SRC =  src/main.c src/parser.c src/render.c src/events.c src/utils.c get_next_line/get_next_line.c

OBJ = $(SRC:.c=.o)

all: $(NAME) 

$(LIB):
	make all -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a $(MFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all