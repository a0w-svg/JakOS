LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all: thegame

Draw.o: Draw.cpp
		g++ -c "Draw.cpp" -o Draw.o

Engine.o: Engine.cpp
		g++ -c "Engine.cpp" -o Engine.o

Input.o: Input.cpp
		g++ -c "Input.cpp" -o Input.o

Update.o: Update.cpp
		g++ -c "Update.cpp" -o Update.o

Player.o: Player.cpp
		g++ -c "Player.cpp" -o Player.o
main.o:	main.cpp
		g++ -c "main.cpp" -o main.o
thegame: Input.o Draw.o Engine.o Update.o Player.o main.o
		@echo "** Building the game"
		g++ -o thegame Input.o Draw.o Engine.o main.o Player.o Update.o $(LIBS)

clean:
		@echo "** Removing object files and executable..."
		rm -f thegame *.o

install:
		@echo '** Installing...'
		cp thegame /usr/bin

uninstall:
		@echo '** Uninstalling...'
		rm -f /usr/bin/thegame
 