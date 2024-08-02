NAME = libftprintf.a

CFILES =	ft_printf.c prt_hexa.c prt_int.c prt_pointer.c prt_str.c prt_unsigned.c

OFILES = $(CFILES:.c=.o)
CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -f
AR = ar -rcs

all: $(NAME)

$(NAME) : $(OFILES)

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@
	$(AR) $(NAME) $@

re: fclean all

clean : 
	$(RM) $(OFILES)
	 
fclean : clean
	$(RM) $(NAME)

.PHONY : clean fclean re all
