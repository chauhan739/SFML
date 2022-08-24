# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -g

# Linking Flags
LDFLAGS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

# Executable File
BIN = main

# Header File
HDR = header.h

SRCS := $(wildcard *.cpp)

OBJS := $(SRCS:.cpp=.o)

all: $(BIN) $(OBJS)

$(BIN): $(OBJS)
	@$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@
	@echo Executable file generated successfully

$(OBJS): $(SRCS) $(HDR)
	@echo Generating Binaries...
	@$(CXX) -c $(SRCS)
	@echo Binary files generated successfully

.PHONY: run clean

run:
	@echo Running Executable...
	@./$(BIN)
clean:
	$(RM) *.o *~
