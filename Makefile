all:
	g++ main.cpp -o bird -L/usr/lib -lSDL2 -ggdb3 -O0 -Wall -lSDL2_ttf -lSDL2_image -lm
clean:
	rm bird
get_assets:
	echo "Comming soon™"
run:
	./bird