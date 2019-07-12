CC=g++
CFLAGS=-std=c++11 -Wall -O3
LINK=
DEPS=Model.h Vertex.h Face.h Matrix.h MatrixRotate.h MatrixTranslate.h MatrixScale.h Camera.h Intersection.h ImagePixel.h Image.h Ray.h Light.h Material.h
OBJS=main.o Model.o Vertex.o Face.o Matrix.o MatrixRotate.o MatrixTranslate.o MatrixScale.o Camera.o Intersection.o ImagePixel.o Image.o Ray.o Light.o Material.o

all: | raytracer

clean:
	-rm -f raytracer *.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LINK)

raytracer: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LINK)

.PHONY: all clean
