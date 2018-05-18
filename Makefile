all: main clear
.PHONY: all main clear

main: main.cpp
	g++ -o 21 main.cpp

clear:
	clear
	clear

clean:
	rm -f *.exe *.o
	clear
	clear
