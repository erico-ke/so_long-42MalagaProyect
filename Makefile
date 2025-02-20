NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

MLX42_PATH = libs/MLX42
MLX42 = $(MLX42_PATH)/build/libmlx42.a

LIBFT_PATH = libs/libft
LIBFT = $(LIBFT_PATH)/libft.a

HEADERS = -I ./libs -I $(MLX42_PATH)/include/MLX42 -I $(LIBFT_PATH)

SRCS =	src/main.c src/utils.c src/error.c src/map_check.c

OBJS = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)
SRCDIR = src/
OBJDIR = obj/

all : $(MLX42) $(LIBFT) $(OBJDIR) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX42) $(LIBFT) $(HEADERS) -lglfw -o $(NAME) -lm

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

$(LIBFT):
	make -C $(LIBFT_PATH)

$(MLX42):
	cmake $(MLX42_PATH) -B $(MLX42_PATH)/build && make -C $(MLX42_PATH)/build -j4

clean:
	$(RM) obj
	make -C $(LIBFT_PATH) clean
	make -C $(MLX42_PATH)/build clean

fclean:
	$(RM) obj $(NAME)
	make -C $(LIBFT_PATH) fclean
	$(RM) $(MLX42_PATH)/build

re: fclean all
