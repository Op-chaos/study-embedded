param = safe_distance.o EEBL_distance.o AVW_distance.o EVW_distance.o\
	FCW_distance.o common_algorithm.o ICW_distance.o

# vpath %.c ./src
# vpath %.h ./include
VPATH = ./src:./include

edit:$(param)
	gcc -o edit $(param)

safe_distance.o:safe_distance.c TA_in.h 
	gcc -c $< -I include

EEBL_distance.o:EEBL_distance.c common_algorithm.h
	gcc -c $< -I include

FCW_distance.o:FCW_distance.c common_algorithm.h
	gcc -c $< -I include

ICW_distance.o:ICW_distance.c common_algorithm.h
	gcc -c $< -I include

EVW_distance.o:EVW_distance.c common_algorithm.h
	gcc -c $< -I include

AVW_distance.o:AVW_distance.c common_algorithm.h
	gcc -c $< -I include

common_algorithm.o:common_algorithm.c common_algorithm.h 
	gcc -c $<  -I include

clean:
	rm $(param)
