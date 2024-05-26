# Compiler settings - Can change on the basis of the OS
ifeq ($(OS),Windows_NT)
    CC=x86_64-w64-mingw32-g++
    BIN_EXT=.exe
    CXXFLAGS=-Wall -std=c++20 -Ofast -DSFML_STATIC
    LIBS=-L/usr/lib/x86_64-linux-gnu -lsfml-graphics -lsfml-window -lsfml-system
    INCLUDES=-I/usr/include/
else
    CC=g++
    BIN_EXT=
    CXXFLAGS=-Wall -std=c++20 -Ofast
    LIBS=-lsfml-graphics -lsfml-window -lsfml-system
    INCLUDES=
endif

LDFLAGS=

# Source files
SRC=src/main.cpp src/game.cpp src/gametime.cpp src/randomGen.cpp src/player.cpp src/graph.cpp src/portfolio.cpp src/list.cpp src/listItem.cpp

# Header files
DEPS=include/game.h include/randomGet.h include/gametime.h include/player.h include/graph.h include/portfolio.h include/asset.h include/crypto.h include/forex.h include/stock.h include/list.h include/listItem.h

# Convert source filenames from .cpp to .o
OBJ=$(SRC:.cpp=.o)

# Game name
TARGET=StockSim$(BIN_EXT)

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS) $(LDFLAGS) $(LIBS)

# Compile each source file to an object file
%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS) $(LDFLAGS) $(LIBS) $(INCLUDES)

# Clean rule to delete object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)

# Usage:
# To compile for Linux, just run `make`
# To compile for Windows, run `make OS=Windows_NT`