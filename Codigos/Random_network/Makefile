CFLAGS = -fsanitize=address -fsanitize=undefined -fsanitize=leak -O3
CXXFLAGS = $(CFLAGS)

# Manually list source files
SOURCES = Random.cpp NeuralNetwork.cpp 

# Manually list object files corresponding to source files
OBJS = $(SOURCES:.cpp=.o)

all: main.x

# Pattern rule for compiling .cpp files into .o files
%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -o $@

main.x: $(OBJS)
	g++ $(CXXFLAGS) $^ -o $@ 
	./main.x >resultados.dat

clean:
	rm -f *.x *.o
