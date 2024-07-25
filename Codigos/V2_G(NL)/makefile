all: run

run:
	g++ -O3 main.cpp Modulacion/Matrix_conect.cpp Modulacion/NeuralNetwork.cpp -o main
	./main input.txt > data.dat
	python3 ButterWorth.py 
	rm -f main

Matrix:
	g++ -O3 main_matrix.cpp Modulacion/Matrix_conect.cpp Modulacion/NeuralNetwork.cpp -o matrix
	./matrix input.txt > matriz.dat
	rm -f main

clean:
	rm -f main
