SRCS:=tunel.c
OBJS := $(SRCS:.c=.o)
RM = rm -f
CC = gcc
LD  = gcc
.PHONY:  all
all: dudu
dudu : $(OBJS)
	$(LD) -o $@ $(OBJS) -lm
%.o : %.c
	$(CC) -c -o $@ $(CFLAGS) $(INCLUDES)  $<
clean:
	$(RM) $(OBJS) dudu.exe
