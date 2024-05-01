all: run

run: 
	g++ -O3 main.cpp Modulacion/Matrix_conect.cpp Modulacion/NeuralNetwork.cpp -o main
	./main input.txt > data.dat
	python3 ButterWorth.py 
	rm -f $(OBJS)
Matrix:
	g++ -O3  main.cpp Modulacion/Matrix_conect.cpp Modulacion/NeuralNetwork.cpp -o main
	./main input.txt > matriz.dat
	
clean:
	rm -f $(OBJS) main
