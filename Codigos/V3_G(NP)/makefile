all: run

run:
	g++ -O3 main.cpp Modulacion/Matrix_conect.cpp Modulacion/NeuralNetwork.cpp -o main
	./main input.txt > data.dat
	python3 ButterWorth.py 
	rm -f main

Matrix:
	python3 matrix.py 
todo:
	g++ -O3 main.cpp Modulacion/Matrix_conect.cpp Modulacion/NeuralNetwork.cpp -o main
	./main input.txt > data.dat
	python3 ButterWorth.py 
	python3 matrix.py 
	rm -f main


clean:
	rm -f main
