All : main1 main2 main3 main4

permutation.o : permutation.c permutation.h
	gcc -c permutation.c

main1.o : main1.c
	gcc -c main1.c

main2.o : main2.c
	gcc -c main2.c

main3.o : main3.c
	gcc -c main3.c

main4.o : main4.c
	gcc -c main4.c

main1 : main1.o permutation.o
	gcc -o main1 main1.o permutation.o

main2 : main2.o permutation.o
	gcc -o main2 main2.o permutation.o

main3 : main3.o permutation.o
	gcc -o main3 main3.o permutation.o

main4 : main4.o permutation.o
	gcc -o main4 main4.o permutation.o
