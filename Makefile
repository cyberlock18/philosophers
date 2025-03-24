
# Colores
GREEN	= \033[0;32m
RED		= \033[0;31m
RESET	= \033[0m

# Nombre y configuración
NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread
RM		= rm -f

# Archivos fuente
SRC		= main.c \
		  init.c \
		  parsing.c \
		  process.c \
		  utils.c

# Objetos
OBJ		= $(SRC:.c=.o)

# Reglas
all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(GREEN)Compilando $@...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "$(GREEN)¡Philosophers compilado con éxito!$(RESET)\n"

%.o: %.c
	@printf "$(GREEN)Compilando $<...$(RESET)\n"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@printf "$(RED)Objetos eliminados$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(RED)Ejecutable eliminado$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
