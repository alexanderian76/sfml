all:
	g++ *.cpp ./Enemy/*.cpp -std=c++20 -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window -lsfml-audio

	#g++ -c PlayerController.cpp -std=c++17 -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window -lsfml-audio
	#g++ -c ObjectController.cpp -std=c++17 -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window -lsfml-audio
	#g++ *.o
	./a.out
static:
	g++ *.cpp ./Enemy/*.cpp -DSFML_STATIC \
	/usr/lib/libsfml-audio.so \
	-lopenal -lvorbisenc -lvorbisfile -lvorbis -logg \
  /usr/lib/libsfml-graphics.so \
  /usr/lib/libsfml-window.so \
  /usr/lib/libsfml-system.so \
  -lGL -lX11 -lXrandr -lXcursor -ludev -lfreetype

clear:
	rm *.o