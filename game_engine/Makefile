LIBS=-lsfml-graphics -lsfml-window -lsfml-system

all: thegame

Draw.o: engine/Draw.cpp
		g++ -c "engine/Draw.cpp" -o Draw.o

Engine.o: engine/Engine.cpp
		g++ -c "engine/Engine.cpp" -o Engine.o

Input.o: control/Input.cpp
		g++ -c "control/Input.cpp" -o Input.o

Update.o: engine/Update.cpp
		g++ -c "engine/Update.cpp" -o Update.o

Player.o: player/Player.cpp
		g++ -c "player/Player.cpp" -o Player.o
main.o:	main.cpp
		g++ -c "main.cpp" -o main.o
thegame: control/Input.o engine/Draw.o engine/Engine.o engine/Update.o player/Player.o main.o
		@echo "** Building the game"
		g++ -o thegame control/Input.o engine/Draw.o engine/Engine.o main.o player/Player.o engine/Update.o $(LIBS)

clean:
		@echo "** Removing object files and executable..."
		rm -f thegame *.o

install:
		@echo '** Installing...'
		cp thegame /usr/bin

uninstall:
		@echo '** Uninstalling...'
		rm -f /usr/bin/thegame
 