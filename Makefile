app: main.o
	g++ main.o -o app -ldl -lGLEW -lglfw -lGL

main.o:
	g++ -c src/main.cpp

run:
	./app

clean:
	rm main.o  app
