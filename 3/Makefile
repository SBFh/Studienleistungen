#Studienleistung 3

CC = gcc

main: libCalc.so logConsole.so logFile.so
	$(CC) -o $@ -ldl main.c -Wl,-rpath,$(CURDIR) -fno-builtin-log

libCalc.so: calcAreas.o calcNewton.o
	$(CC) -shared -o libCalc.so calcAreas.o calcNewton.o

calcAreas.o:
	$(CC) -fpic -o calcAreas.o -c calcAreas.c

calcNewton.o:
	$(CC) -fpic -o calcNewton.o -c calcNewton.c -std=c99

logConsole.so: logConsole.o
	$(CC) -shared -o logConsole.so logConsole.o

logConsole.o:
	$(CC) -fpic -o logConsole.o -c logConsole.c -fno-builtin-log

logFile.so: logFile.o
	$(CC) -shared -o logFile.so logFile.o

logFile.o:
	$(CC) -fpic -o logFile.o -c logFile.c -fno-builtin-log

install:
	install main log.config /usr/local/bin
	install libCalc.so logConsole.so logFile.so /usr/lib

clean:
	rm main libCalc.so logConsole.so logFile.so *.o log.txt -f