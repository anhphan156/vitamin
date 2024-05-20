app: main.o shader.o
	cc build/main.o build/shader.o -o build/app -ldl -lGLEW -lglfw -lGL -lEGL -lwayland-client -lwayland-cursor -lwayland-egl -lxkbcommon -lm -lpthread

main.o:
	cc -c src/main.c -o build/main.o

shader.o:
	cc -c src/shader.c  -o build/shader.o

run:
	./build/app

check:
	#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=leak.txt ./build/app
	valgrind --leak-check=yes --log-file=leak.txt ./build/app

clean:
	rm build/*
	touch build/tmp
