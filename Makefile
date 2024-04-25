CC=g++
CXXFLAGS=-Wall  # Add any compiler-specific flags
LDFLAGS= 
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
SRC=main.cpp game.h game.cpp # List all source files here
OBJ=$(SRC:.cpp=.o)  # Convert source filenames from .cpp to .o
DEPS=  
TARGET=StockSim

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

# Compile each source file to an object file
%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CXXFLAGS)

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)