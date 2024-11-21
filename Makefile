all:app

app:main.o Wordlist.o
	g++ main.o Wordlist.o -o app

Wordlist.o:Wordlist.cpp Wordlist.h
	g++ -c Wordlist.cpp Wordlist.h

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -f *.exe *.o *.h.gch