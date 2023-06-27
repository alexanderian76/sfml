all:
	g++ *.cpp -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window -lsfml-audio
	#g++ -c PlayerController.cpp -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window -lsfml-audio
	#g++ -c ObjectController.cpp -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window -lsfml-audio
	#g++ *.o
	./a.out

clear:
	rm *.o