##
## Makefile for Makefile in /home/querat_g/colles/colle3
##
## Made by gwendal querat
## Login   <querat_g@epitech.net>
##
## Started on  Sun Oct 26 00:43:12 2014 gwendal querat
## Last update Sun Feb 28 16:52:30 2016 querat_g
##

RM		=	rm -f

CC		=	gcc

INCFLAGS	=	-I./include \
			-I./include/nm \
			-I./include/lib \
			-I./include/objdump \

CFLAGS		+=	-Wextra -Wall -D_GNU_SOURCE
CFLAGS		+=	$(LDFLAGS)
CFLAGS		+=	$(INCFLAGS)

LIBSRCS		= 	src/lib/list_init.c \
			src/lib/list_append.c \
			src/lib/list_prepend.c \
			src/lib/list_print.c \
			src/lib/list_destruct.c \
			src/lib/list_rm.c \
			src/lib/list_len.c \
			src/lib/list_insert.c \
			src/lib/list_cmp.c \
			src/file.c \
			src/util.c \
			src/get_tables.c \
			src/destructors.c \
			src/constructors.c \

NMSRCS		=	src/nm/main.c \
			src/nm/flags/tab.c \
			src/nm/flags/tab_functions1.c \
			src/nm/flags/tab_functions2.c \
			src/nm/t_sym.c \
			src/nm/t_sym_utils.c \
			src/nm/nm_utils.c \

OBJDSRCS	=	src/objdump/main.c \
			src/objdump/dump/dump.c \
			src/objdump/dump/dump_f.c \
			src/objdump/dump/dump_line.c \
			src/objdump/dump/get_arch.c \
			src/objdump/dump/dump_flags.c \

NM	 	=	my_nm

OBJDUMP		=	my_objdump

NMOBJS		=	$(NMSRCS:.c=.o)

LIBOBJS		=	$(LIBSRCS:.c=.o)

OBJDOBJS	=	$(OBJDSRCS:.c=.o)

all:			$(LIBOBJS) $(OBJDUMP) $(NM)

nm:			$(NM)

objdump:		$(OBJDUMP)

$(NM):			$(LIBOBJS) $(NMOBJS)
			$(CC) -o $(NM) $(NMOBJS) $(LIBOBJS) $(CFLAGS)

$(OBJDUMP):		$(LIBOBJS) $(OBJDOBJS)
			$(CC) -o $(OBJDUMP) $(OBJDOBJS) $(LIBOBJS) $(CFLAGS)

clean:
			$(RM) $(LIBOBJS) $(NMOBJS) $(OBJDOBJS)

fclean:			clean
			$(RM) $(NM) $(OBJDUMP)

re:			fclean all

tags:

