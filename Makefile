# Compiler
CC=g++
# Compiler-specific flags
CXXFLAGS=-Wall  

# Library 
LIBS=-lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRC=main.cpp game.cpp randomGen.cpp \
	asset/asset.h asset/crypto.h asset/forex.h asset/stock.h \
	layout/list.cpp layout/listItem.cpp layout/tab.cpp
    
# Headers files
DEPS=game.h randomGen.h \
	asset/asset.h asset/crypto.h asset/forex.h asset/stock.h \
	layout/list.h layout/listItem.h layout/tab.h

# Convert source filenames from .cpp to .o
OBJ=$(SRC:.cpp=.o)  

# Game name
TARGET=StockSim

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

# Compile each source file to an object file
%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

# Clean rule to delete object files and the executable
clean:
	rm -f $(OBJ) $(TARGET)