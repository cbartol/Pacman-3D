##FOR WINDOWS:
#CFLAGS = -lglut32 -lglu32 -lopengl32

##RESTO:
CFLAGS = -lglut -lGLU -lGL -gdb -O3
OBJECTS = *.o camera/*.o light/*.o entity/*.o extralib/*.o
DEFS = -DDEV_MODE=false -DSHOW_BOARD=true -DSHOW_PACMAN=true -DSHOW_GHOST=true -DSHOW_BALLS=true -DMULTI_PLAYER=true
#a linha de cima define constantes para saber que partes do jogo desenha (meter true ou false), se a linha de cima ficar em comentário (#DEFS = ...) existe uma predefinição no ficheiro main.cpp

all:
	make -s all -C extralib
	make -s all -C light
	make -s all -C camera
	make -s all -C entity
	g++ $(DEFS) -c -O3 *.cpp
	g++ -o pacman $(OBJECTS) $(CFLAGS)

clean:
	make -s clean -C extralib
	make -s clean -C entity
	make -s clean -C camera
	make -s clean -C light
	rm -f *.o pacman
#	del *.o pacman.exe
