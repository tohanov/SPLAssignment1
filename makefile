all: clean compile link check


clean:
	echo "Cleaning..."
	rm -f bin/*


compile: src/main.cpp src/Action.cpp src/Customer.cpp src/Studio.cpp src/Trainer.cpp src/Workout.cpp
	echo "Compiling..."
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Action.o src/Action.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Customer.o src/Customer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Studio.o src/Studio.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Trainer.o src/Trainer.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -Iinclude -c -o bin/Workout.o src/Workout.cpp


link: bin/main.o bin/Action.o bin/Customer.o bin/Studio.o bin/Trainer.o bin/Workout.o
	echo "Linking..."
	g++ -o bin/studio bin/main.o bin/Action.o bin/Customer.o bin/Studio.o bin/Trainer.o bin/Workout.o


check: bin/studio
	echo "Checking..."
	valgrind --leak-check=full --show-reachable=yes bin/studio ExampleInput.txt

#suppressing printing of the commands that are running
ifndef VERBOSE
.SILENT:
endif
