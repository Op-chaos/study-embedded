param = safe_distance.o EEBL_distance.o AVW_distance.o EVW_distance.o\
	FCW_distance.o common_algorithm.o ICW_distance.o
edit:$(param)
	gcc -o edit $(param)

safe_distance.o:safe_distance.c TA_in.h 
	gcc -c safe_distance.c

EEBL_distance.o:EEBL_distance.c common_algorithm.h
	gcc -c  EEBL_distance.c

FCW_distance.o:common_algorithm.h   #简化方法 

ICW_distance.o:ICW_distance.c common_algorithm.h
	gcc -c ICW_distance.c 

common_algorithm.o:common_algorithm.c 
	gcc -c common_algorithm.c 

%.o:common_algorithm.c

clean:
	rm $(param)
