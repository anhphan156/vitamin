app: main.o shader.o
	gcc build/main.o build/shader.o -o build/app -ldl -lGLEW -lglfw -lGL -lEGL -lwayland-client -lwayland-cursor -lwayland-egl -lxkbcommon -lm -lpthread

main.o:
	gcc -c src/main.c -o build/main.o -g

shader.o:
	gcc -c src/shader.c  -o build/shader.o -g

run:
	./build/app

debug:
	gdb ./build/app

leak-check:
	#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=leak.txt ./build/app
	valgrind --leak-check=yes --log-file=leak.txt ./build/app

clean:
	rm build/*
	touch build/tmp
