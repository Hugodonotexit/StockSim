# Compiler
CC=g++
# Compiler-specific flags
CXXFLAGS=-Wall -std=c++20 -Ofast

# Add the sanitizer library to linkage if using sanitizers
LDFLAGS=-fsanitize=address -fsanitize=undefined

# Library 
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRC=main.cpp game.cpp function/gametime.cpp function/randomGen.cpp function/player.cpp function/graph.cpp function/portfolio.cpp layout/list.cpp layout/listItem.cpp

# Headers files (used only for dependency tracking, not for compiling or cleaning)
DEPS=game.h \
	 function/randomGen.h function/gametime.h function/player.h function/graph.h function/portfolio.h\
     asset/asset.h asset/crypto.h asset/forex.h asset/stock.h \
     layout/list.h layout/listItem.h

# Convert source filenames from .cpp to .o
OBJ=$(SRC:.cpp=.o)  

# Game name
TARGET=StockSim

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS) $(LDFLAGS) $(LIBS)

# Compile each source file to an object file
%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS) $(LDFLAGS) $(LIBS)

# Clean rule to delete object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)