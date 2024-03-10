run:
	g++ KonaneBoard.cpp -Wall -o KonaneBoard.o -c
	g++ main.cpp -Wall -o main.o -c
	g++ MiniMaxPlayer.cpp -Wall -o MiniMaxPlayer.o -c
	g++ MiniMaxPlayer2.cpp -Wall -o MiniMaxPlayer2.o -c
	g++ -o prog main.o KonaneBoard.o MiniMaxPlayer.o MiniMaxPlayer2.o 
	./prog
	rm *.o

test:
	g++ KonaneBoard.cpp -Wall -o KonaneBoard.o -c
	g++ testKonaneBoard.cpp -Wall -o testKonaneBoard.o -c
	g++ -o prog testKonaneBoard.o KonaneBoard.o
	./prog
	rm *.o
clean:
	rm *.o
