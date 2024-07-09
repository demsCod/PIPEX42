NAME = pipex

#	colors	#

BLACK=	$(shell tput -Txterm setaf 0)
RED= 	$(shell tput -Txterm setaf 1)
GREEN= 	$(shell tput -Txterm setaf 2)
WHITE= 	$(shell tput -Txterm setaf 7)
YELLOW=	$(shell tput -Txterm setaf 3)
BLUE=	$(shell tput -Txterm setaf 6)
END= 	$(shell tput -Txterm sgr0)

#			#


CC = 	cc

FLAGS = -Wall -Werror -Wextra -g3

LIBFT_PATH = ./libft_srcs

Libft = libft.a

FILES = 	./my_srcs/main.c	\
			./my_srcs/here_doc.c	\
			./my_srcs/pathwork.c	\
			./my_srcs/freework.c	\
			./my_srcs/directionwork.c	\
			$(LIBFT_PATH)/libft.a	\

OBJ =	$(FILES:.c=.o)

all : 	$(NAME)

$(NAME) : $(Libft) $(FILES)
			@$(CC) $(FLAGS) $(FILES) -o $(NAME)
			@printf "$(GREEN)$(NAME) done !$(END)"

$(Libft) : $(LIBFT_PATH)
			@make -C $(LIBFT_PATH)

clean :
			@make clean -C $(LIBFT_PATH)

fclean :
			@make fclean -C $(LIBFT_PATH)
			@rm -rf $(NAME)
			@echo "$(BLUE)remove $(NAME)$(END)"

re : 	fclean all
