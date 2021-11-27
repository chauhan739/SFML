#target: dependencies
#	command(s)

CXX = g++
CXXFLAGS = -Wall -std=c++14
LDLIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

main: main.o
	$(CXX) -o main main.o $(LDLIBS)

main.o: main.cpp
	$(CXX) -c main.cpp

clean:
	$(RM) *.o *~
