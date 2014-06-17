COMPILER=g++
CFLAGS=-c -Wall -O3
LDFLAGS=
SOURCES=Col_Major_Order_Matrix.cpp Matrix.cpp Matrix_Utils.cpp Row_Major_Order_Matrix.cpp Sparse_Matrix.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(COMPILER) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(COMPILER) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)