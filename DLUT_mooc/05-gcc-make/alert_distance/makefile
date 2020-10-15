param = safe_distance.o EEBL_distance.o \
	FCW_distance.o common_algorithm.o ICW_distance.o
vpath %.c src
vpath %.h include
edit:$(param)
	gcc -o edit $(param)

safe_distance.o:safe_distance.c TA_in.h 
	gcc -c safe_distance.c -I include

EEBL_distance.o:EEBL_distance.c common_algorithm.h
	gcc -c  EEBL_distance.c -I ../include

FCW_distance.o:common_algorithm.h

ICW_distance.o:ICW_distance.c common_algorithm.h
	gcc -c ICW_distance.c -I ../include

common_algorithm.o:common_algorithm.c 
	gcc -c common_algorithm.c -I ../include

clean:
	rm $(param)
