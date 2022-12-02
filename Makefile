all:
	g++ main.cpp -o bird -L/usr/lib -lSDL2 -O0 -Wall -lSDL2_ttf -lSDL2_image -lm
windows-cross:
	x86_64-w64-mingw32-g++ main.cpp -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2_image -lSDL2 -o bird
windows:
	g++ main.cpp -lmingw32 -lSDL2main -lSDL2_ttf -lSDL2_image -lSDL2 -o bird
clean:
	rm bird
	rm bird.exe
get_assets:
	echo "Comming soon™"
run:
	./bird
run-wine:
	wine bird.exe
run-windows:
	bird.exe
help:
	echo "to compile for linux in linux: 'make'"
	echo "to compile for windows in windows: 'make windows'"
	echo "to compile for windows in linux: 'make windows-cross'"
	echo "to clean: 'make clean'"
	echo "to run the linux binary in linux: 'make run'"
	echo "to run the windows binary in linux using wine: 'make run-wine'"
	echo "to run the windows binary in winows: 'make run-windows'"
