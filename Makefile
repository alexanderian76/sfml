all:
	g++ *.cpp ./Enemy/*.cpp -std=c++17 -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window -lsfml-audio

	#g++ -c PlayerController.cpp -std=c++17 -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window -lsfml-audio
	#g++ -c ObjectController.cpp -std=c++17 -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window -lsfml-audio
	#g++ *.o
	./a.out

clear:
	rm *.o