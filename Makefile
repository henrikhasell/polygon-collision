SRC = src/application.c  src/game.c  src/glyph.c  src/image.c  src/list.c  src/main.c  src/object.c  src/polygon.c

build: $(SRC)
	gcc -o polygon-collision -I include $(SRC) -lSDL2 -lGL -lm

clean:
	rm $(OUT)

rebuild: clean build

