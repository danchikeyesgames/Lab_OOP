result1: main1.o ldynamic
	gcc main1.o -L. -l1 -o main1.exe

result2: ldynamic
	gcc main2.c -o main2.exe -ldl

ldynamic: lib1.c lib2.c
	gcc -fPIC -c lib1.c
	gcc -fPIC -c lib2.c
	gcc -shared lib1.o -o lib1.so -lm
	gcc -shared lib2.o -o lib2.so

main1.o: main1.c
	gcc -c main1.c

clean:
	rm -f main1.o lib1.so lib2.so main2.o lib1.o lib2.o main1.exe main2.exe