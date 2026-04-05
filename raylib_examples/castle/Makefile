

obj/castle.o: castle.cpp
	mkdir -p obj
	g++ -c castle.cpp -o obj/castle.o

bin/castle: obj/castle.o
	mkdir -p bin
	g++ obj/castle.o /usr/lib/raylib/libraylib.a -lGL -lm -lzip -lpthread -ldl -lrt -lX11 -o bin/castle

run: bin/castle
	bin/castle

clean:
	mkdir -p obj
	rm -r obj/*
	mkdir -p bin
	rm -r bin/*
