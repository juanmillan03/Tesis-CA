all: run

run:
	g++ -O3 main.cpp Modulacion/Matrix_conect.cpp Modulacion/NeuralNetwork.cpp -o main
	./main input.txt > data.dat
	python3 ButterWorth.py 
	rm -f main

Matrix:
	python3 matrix.py 

clean:
	rm -f main
