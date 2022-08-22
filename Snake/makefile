CXX = g++
CXXFLAGS = -Wall -g
LDLIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

main: main.o
	$(CXX) -o main main.o $(LDLIBS)

main.o: main.cpp
	$(CXX) -c main.cpp

.PHONY: run clean

run:
	./main

clean:
	$(RM) *.o *~ main
