all: shell

clean:
	rm shell main.o parse.o buildin_command.o FSM.o history.o

shell: main.o parse.o buildin_command.o FSM.o history.o
	g++ -o shell main.o parse.o buildin_command.o FSM.o history.o

main.o: main.cpp
	g++ -c main.cpp

parse.o: parse.cpp
	g++ -c parse.cpp

buildin_command.o: buildin_command.cpp
	g++ -c buildin_command.cpp

FSM.o: FSM.cpp
	g++ -c FSM.cpp

history.o: history.cpp
	g++ -c history.cpp