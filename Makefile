# Compiler
CC=g++
# Compiler-specific flags
CXXFLAGS=-Wall -fsanitize=address

# Add the sanitizer library to linkage if using sanitizers
LDFLAGS=-fsanitize=address

# Library 
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRC=main.cpp game.cpp layout/list.cpp layout/listItem.cpp layout/tab.cpp layout/error.cpp

# Headers files (used only for dependency tracking, not for compiling or cleaning)
DEPS=game.h randomGen.h \
     asset/asset.h asset/crypto.h asset/forex.h asset/stock.h \
     layout/list.h layout/listItem.h layout/tab.h layout/error.h

# Convert source filenames from .cpp to .o
OBJ=$(SRC:.cpp=.o)  

# Game name
TARGET=StockSim

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

# Compile each source file to an object file
%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

# Clean rule to delete object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)