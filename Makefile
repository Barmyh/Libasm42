NAME	= libasm.a

AS	= nasm
ASFLAGS	= -f elf64

CC	= cc
CFLAGS	= -Wall -Wextra -Werror

SRCS	= srcs/ft_strlen.s \
	  srcs/ft_strcpy.s \
	  srcs/ft_strcmp.s \
	  srcs/ft_write.s

OBJS	= $(SRCS:.s=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

test: $(NAME)
	$(CC) $(CCFLAGS) main.c $(NAME) -o test

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(OBJS)

re: fclean all

.PHONY: all clean fclean re test
