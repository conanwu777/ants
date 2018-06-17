NAME = ants
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = ants.c path_finding.c path_finding_extra.c paths.c read.c read_support.c setup.c output.c\
display_ants.c display.c display_roads.c display_graph.c
OBJ = $(SRC:.c=.o)

FT_LNK = -L ./libft -lft

all:
	$(CC) $(CFLAGS) $(FT_LNK) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
